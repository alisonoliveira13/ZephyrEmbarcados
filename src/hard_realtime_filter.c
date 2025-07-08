#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/dac.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/ring_buffer.h>
#include <math.h>
#include <string.h>

LOG_MODULE_REGISTER(hard_filter, LOG_LEVEL_INF);

/* --- CONFIGURAÇÕES DO FILTRO HARD REAL-TIME --- */
#define SAMPLE_RATE_HZ 8000         // 8 kHz de amostragem
#define SAMPLE_PERIOD_US (1000000 / SAMPLE_RATE_HZ)  // 125 µs
#define HARD_DEADLINE_US 100        // Deadline rígido de 100µs
#define FILTER_ORDER 4              // Filtro IIR de 4ª ordem
#define CUTOFF_FREQ_HZ 1000         // Frequência de corte 1kHz

/* --- ESTRUTURAS DE DADOS --- */
struct filter_coeffs {
    float a[FILTER_ORDER + 1];      // Coeficientes do denominador
    float b[FILTER_ORDER + 1];      // Coeficientes do numerador
};

struct filter_state {
    float x[FILTER_ORDER + 1];      // Histórico de entradas
    float y[FILTER_ORDER + 1];      // Histórico de saídas
    uint32_t index;                 // Índice circular
};

/* --- CONFIGURAÇÃO DO HARDWARE --- */
#define ADC_NODE DT_ALIAS(adc)
#define DAC_NODE DT_ALIAS(dac)

#if DT_NODE_EXISTS(ADC_NODE)
static const struct device *adc_dev = DEVICE_DT_GET(ADC_NODE);
#endif

#if DT_NODE_EXISTS(DAC_NODE)
static const struct device *dac_dev = DEVICE_DT_GET(DAC_NODE);
#endif



/* --- VARIÁVEIS GLOBAIS --- */
static struct filter_coeffs coeffs;
static struct filter_state filter_state;
static struct k_timer sample_timer;
static K_SEM_DEFINE(sample_sem, 0, 1);
K_MSGQ_DEFINE(sample_msgq, sizeof(uint16_t), 32, 4);

/* --- ESTATÍSTICAS TEMPO REAL --- */
static uint32_t total_samples = 0;
static uint32_t missed_deadlines = 0;
static uint32_t max_processing_time_us = 0;
static uint32_t min_processing_time_us = UINT32_MAX;

/* --- INICIALIZAÇÃO DO FILTRO BUTTERWORTH PASSA-BAIXA --- */
static void init_butterworth_filter(void)
{
    // Coeficientes aproximados para filtro Butterworth 4ª ordem
    // Frequência de corte normalizada: fc/fs = 1000/8000 = 0.125
    // Estes são coeficientes aproximados para demonstração
    
    // Coeficientes do numerador (b)
    coeffs.b[0] = 0.0067f;
    coeffs.b[1] = 0.0268f;
    coeffs.b[2] = 0.0402f;
    coeffs.b[3] = 0.0268f;
    coeffs.b[4] = 0.0067f;
    
    // Coeficientes do denominador (a)
    coeffs.a[0] = 1.0000f;
    coeffs.a[1] = -2.3695f;
    coeffs.a[2] = 2.3140f;
    coeffs.a[3] = -1.0547f;
    coeffs.a[4] = 0.1874f;
    
    // Inicializa estado do filtro
    memset(&filter_state, 0, sizeof(filter_state));
    
    LOG_INF("Filtro Butterworth inicializado (fc=%d Hz, fs=%d Hz)", 
            CUTOFF_FREQ_HZ, SAMPLE_RATE_HZ);
}

/* --- APLICAÇÃO DO FILTRO IIR --- */
static float apply_filter(float input)
{
    uint32_t i = filter_state.index;
    
    // Armazena nova entrada
    filter_state.x[i] = input;
    
    // Calcula saída usando equação diferencial
    float output = 0.0f;
    
    // Parte do numerador (FIR)
    for (int n = 0; n <= FILTER_ORDER; n++) {
        uint32_t idx = (i + FILTER_ORDER - n) % (FILTER_ORDER + 1);
        output += coeffs.b[n] * filter_state.x[idx];
    }
    
    // Parte do denominador (IIR)
    for (int n = 1; n <= FILTER_ORDER; n++) {
        uint32_t idx = (i + FILTER_ORDER - n + 1) % (FILTER_ORDER + 1);
        output -= coeffs.a[n] * filter_state.y[idx];
    }
    
    // Armazena saída
    filter_state.y[i] = output;
    
    // Avança índice circular
    filter_state.index = (i + 1) % (FILTER_ORDER + 1);
    
    return output;
}

/* --- CALLBACK DO TIMER (INTERRUPT CONTEXT) --- */
static void sample_timer_handler(struct k_timer *timer)
{
    ARG_UNUSED(timer);
    // Sinaliza thread de processamento (não bloqueia)
    k_sem_give(&sample_sem);
}

/* --- TAREFA DE AMOSTRAGEM ADC (ALTA PRIORIDADE) --- */
static void adc_sampling_task(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);
    
#if DT_NODE_EXISTS(ADC_NODE)
    uint16_t sample_buffer[1];
    struct adc_sequence sequence = {
        .channels = BIT(0),
        .buffer = sample_buffer,
        .buffer_size = sizeof(sample_buffer),
        .resolution = 12,
        .oversampling = 0,
        .calibrate = false,
    };
    
    LOG_INF("Tarefa de amostragem ADC iniciada");
    
    while (1) {
        // Aguarda sinal do timer
        k_sem_take(&sample_sem, K_FOREVER);
        
        // Lê ADC (operação determinística)
        int ret = adc_read(adc_dev, &sequence);
        if (ret == 0) {
            // Envia amostra para processamento
            k_msgq_put(&sample_msgq, &sample_buffer[0], K_NO_WAIT);
        }
    }
#else
    while (1) {
        k_sem_take(&sample_sem, K_FOREVER);
        // Simula dados para teste
        uint16_t dummy_sample = 2048 + (total_samples % 100);
        k_msgq_put(&sample_msgq, &dummy_sample, K_NO_WAIT);
    }
#endif
}

/* --- TAREFA DE PROCESSAMENTO HARD REAL-TIME --- */
static void hard_realtime_filter_task(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);
    
    uint16_t raw_sample;
    uint32_t start_time, end_time, processing_time_us;
    
    LOG_INF("=== TAREFA HARD REAL-TIME INICIADA ===");
    LOG_INF("Deadline: %d us, Período: %d us", HARD_DEADLINE_US, SAMPLE_PERIOD_US);
    
    while (1) {
        // Aguarda nova amostra
        k_msgq_get(&sample_msgq, &raw_sample, K_FOREVER);
        
        start_time = k_cycle_get_32();
        
        // Converte ADC para float (-1.0 a 1.0)
        float input = (float)(raw_sample - 2048) / 2048.0f;
        
        // Aplica filtro digital
        float filtered = apply_filter(input);
        
        // Converte para DAC (0-4095)
        uint16_t dac_value = (uint16_t)((filtered + 1.0f) * 2048.0f);
        if (dac_value > 4095) dac_value = 4095;
        
        // Envia para DAC se disponível
#if DT_NODE_EXISTS(DAC_NODE)
        dac_write_value(dac_dev, 0, dac_value);
#endif
        
        end_time = k_cycle_get_32();
        processing_time_us = k_cyc_to_us_floor32(end_time - start_time);
        
        // Atualiza estatísticas
        total_samples++;
        if (processing_time_us > max_processing_time_us) {
            max_processing_time_us = processing_time_us;
        }
        if (processing_time_us < min_processing_time_us) {
            min_processing_time_us = processing_time_us;
        }
        
        // Verifica deadline HARD
        if (processing_time_us > HARD_DEADLINE_US) {
            missed_deadlines++;
            LOG_ERR("HARD DEADLINE PERDIDO! Amostra=%u, Tempo=%u us (limite=%u us)",
                    total_samples, processing_time_us, HARD_DEADLINE_US);
            
            // Em sistema real, seria necessário ação corretiva imediata
            // Por exemplo: reset do sistema, modo seguro, etc.
        }
        
        // Log periódico (sem afetar tempo real)
        //if ((total_samples % 1000) == 0) {
        //    LOG_INF("Amostras processadas: %u, Perdas: %u, Último tempo: %u us",
        //            total_samples, missed_deadlines, processing_time_us);
        //}
    }
}

/* --- FUNÇÕES DE INTERFACE PARA SHELL --- */
void get_filter_stats(uint32_t *total, uint32_t *missed, uint32_t *max_time, uint32_t *min_time)
{
    *total = total_samples;
    *missed = missed_deadlines;
    *max_time = max_processing_time_us;
    *min_time = (min_processing_time_us == UINT32_MAX) ? 0 : min_processing_time_us;
}

void get_filter_info(uint32_t *sample_rate, uint32_t *cutoff_freq, uint32_t *deadline_us)
{
    *sample_rate = SAMPLE_RATE_HZ;
    *cutoff_freq = CUTOFF_FREQ_HZ;
    *deadline_us = HARD_DEADLINE_US;
}

/* --- INICIALIZAÇÃO DO SISTEMA --- */
int init_hard_realtime_filter(void)
{
#if DT_NODE_EXISTS(ADC_NODE)
    /* --- E cole aqui, dentro do bloco #if --- */
    static const struct adc_channel_cfg adc_cfg = {
        .gain = ADC_GAIN_1,
        .reference = ADC_REF_INTERNAL,
        .acquisition_time = ADC_ACQ_TIME_DEFAULT,
        .channel_id = 0,
        .differential = 0,
    };

    if (!device_is_ready(adc_dev)) { ... }

    int ret = adc_channel_setup(adc_dev, &adc_cfg); // <-- Onde ela é usada
#else
    LOG_WRN("ADC não disponível - modo simulação");
#endif

#if DT_NODE_EXISTS(DAC_NODE)
    if (!device_is_ready(dac_dev)) {
        LOG_ERR("DAC não está pronto");
        return -ENODEV;
    }
    
    // Configura DAC
    struct dac_channel_cfg dac_cfg = {
        .channel_id = 0,
        .resolution = 12,
        .buffered = false,
    };
    
    ret = dac_channel_setup(dac_dev, &dac_cfg);
    if (ret < 0) {
        LOG_ERR("Erro ao configurar DAC: %d", ret);
        return ret;
    }
#else
    LOG_WRN("DAC não disponível - modo simulação");
#endif
    
    // Inicializa filtro
    init_butterworth_filter();
    
    // Inicializa timer
    k_timer_init(&sample_timer, sample_timer_handler, NULL);
    
    // Inicia timer periódico
    k_timer_start(&sample_timer, K_USEC(SAMPLE_PERIOD_US), K_USEC(SAMPLE_PERIOD_US));
    
    
    return 0;
}

/* --- DEFINIÇÃO DAS THREADS COM PRIORIDADES CRÍTICAS --- */
// Prioridade 2: Processamento hard real-time (mais alta)
// Prioridade 3: Amostragem ADC (alta)
K_THREAD_DEFINE(adc_sampling_tid, 1024, adc_sampling_task, NULL, NULL, NULL, 3, 0, 0);
K_THREAD_DEFINE(hard_filter_tid, 2048, hard_realtime_filter_task, NULL, NULL, NULL, 2, 0, 0);