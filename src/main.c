#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/dac.h>
#include <zephyr/shell/shell.h>
#include <zephyr/debug/thread_analyzer.h>
#include <zephyr/shell/shell_uart.h>

/* ========================================================================= */
/* --- REQUISITO 3: TAREFA PARA PISCAR UM LED --- */
/* ========================================================================= */
#define LED_PISCA_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led_pisca = GPIO_DT_SPEC_GET(LED_PISCA_NODE, gpios);

void tarefa_pisca_led(void) {
    gpio_pin_configure_dt(&led_pisca, GPIO_OUTPUT_ACTIVE);
    while (1) {
        gpio_pin_toggle_dt(&led_pisca);
        k_msleep(1000);
    }
}

/* ========================================================================= */
/* --- REQUISITO 4: TAREFA ACIONADA POR BOTÃO --- */
/* ========================================================================= */
#define BOTAO_NODE DT_ALIAS(sw0)
static const struct gpio_dt_spec botao = GPIO_DT_SPEC_GET(BOTAO_NODE, gpios);
static struct gpio_callback button_cb_data;
K_SEM_DEFINE(sem_botao, 0, 1);

void callback_do_botao(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    k_sem_give(&sem_botao);
}

void tarefa_do_botao(void) {
    while (1) {
        k_sem_take(&sem_botao, K_FOREVER);
        shell_print(shell_backend_uart_get_ptr(), "INFO: Botao Pressionado!");
    }
}

/* ========================================================================= */
/* --- REQUISITO 1: TAREFAS DE TEMPO REAL --- */
/* ========================================================================= */
// Variáveis para simular ADC/DAC se não estiverem disponíveis
static uint16_t simulated_adc_value = 0;
static bool adc_available = false;
static bool dac_available = false;

// Tentar encontrar dispositivos ADC/DAC
static const struct device *adc_dev = NULL;
static const struct device *dac_dev = NULL;

#define ADC_RESOLUTION 12
#define ADC_CHANNEL 0
#define DAC_CHANNEL 1

// Estrutura para sequência ADC (será inicializada em runtime se disponível)
struct adc_sequence sequence;

void tarefa_hard_realtime(void) {
    // Tentar inicializar ADC/DAC se disponíveis
    adc_dev = device_get_binding("ADC_1");
    if (adc_dev == NULL) {
        adc_dev = device_get_binding("ADC_0");
    }
    
    dac_dev = device_get_binding("DAC_1");
    if (dac_dev == NULL) {
        dac_dev = device_get_binding("DAC_0");
    }
    
    if (adc_dev && device_is_ready(adc_dev)) {
        // Tentar configurar ADC
        struct adc_channel_cfg adc_cfg = {
            .channel_id = ADC_CHANNEL,
            .gain = ADC_GAIN_1,
            .reference = ADC_REF_INTERNAL,
            .acquisition_time = ADC_ACQ_TIME_DEFAULT
        };
        
        if (adc_channel_setup(adc_dev, &adc_cfg) == 0) {
            adc_available = true;
            sequence.channels = BIT(ADC_CHANNEL);
            sequence.resolution = ADC_RESOLUTION;
            shell_print(shell_backend_uart_get_ptr(), "INFO: ADC configurado com sucesso");
        }
    }
    
    if (dac_dev && device_is_ready(dac_dev)) {
        // Tentar configurar DAC
        struct dac_channel_cfg dac_cfg = {
            .channel_id = DAC_CHANNEL,
            .resolution = 12
        };
        
        if (dac_channel_setup(dac_dev, &dac_cfg) == 0) {
            dac_available = true;
            shell_print(shell_backend_uart_get_ptr(), "INFO: DAC configurado com sucesso");
        }
    }
    
    if (!adc_available && !dac_available) {
        shell_print(shell_backend_uart_get_ptr(), "INFO: Modo simulação - ADC/DAC não disponíveis");
    }
    
    uint16_t adc_buffer;
    sequence.buffer = &adc_buffer;
    sequence.buffer_size = sizeof(adc_buffer);
    
    shell_print(shell_backend_uart_get_ptr(), "INFO: Tarefa Hard Real-time iniciada");
    
    while(1) {
        if (adc_available) {
            // Usar ADC real
            if (adc_read(adc_dev, &sequence) == 0) {
                simulated_adc_value = adc_buffer;
                if (dac_available) {
                    dac_write_value(dac_dev, DAC_CHANNEL, adc_buffer);
                }
            }
        } else {
            // Simular leitura ADC
            simulated_adc_value = (simulated_adc_value + 1) % 4096;
        }
        
        k_msleep(1);
    }
}

void tarefa_soft_realtime(void) {
    while(1) {
        shell_print(shell_backend_uart_get_ptr(), "SENSOR: Lendo sensor...");
        k_sleep(K_SECONDS(10));
    }
}

/* ========================================================================= */
/* --- REQUISITO 2: COMANDOS DO SHELL --- */
/* ========================================================================= */
static int cmd_sysinfo(const struct shell *sh, size_t argc, char **argv) {
    shell_print(sh, "--- Informacoes do Sistema ---");
    shell_print(sh, "\n--- Tarefas em Execucao ---");
    thread_analyzer_print(); // Corrigido: adicionar parâmetro CPU
    return 0;
}

static int cmd_rt_info(const struct shell *sh, size_t argc, char **argv) {
    shell_print(sh, "--- Informacoes de Tempo Real ---");
    
    if (adc_available) {
        uint16_t val;
        int ret = adc_read(adc_dev, &sequence);
        if (ret == 0) {
            val = *((uint16_t*)sequence.buffer);
            shell_print(sh, "ADC (Canal %d): %u", ADC_CHANNEL, val);
        } else {
            shell_print(sh, "ERRO: Falha na leitura do ADC (%d)", ret);
        }
    } else {
        shell_print(sh, "ADC Simulado: %u", simulated_adc_value);
    }
    
    shell_print(sh, "DAC disponível: %s", dac_available ? "SIM" : "NÃO");
    shell_print(sh, "Modo: %s", (adc_available || dac_available) ? "Hardware" : "Simulação");
    
    return 0;
}

SHELL_CMD_REGISTER(sysinfo, NULL, "Mostra info do sistema (tarefas).", cmd_sysinfo);
SHELL_CMD_REGISTER(rt_info, NULL, "Mostra ultima leitura do ADC.", cmd_rt_info);

/* ========================================================================= */
/* --- FUNÇÃO PRINCIPAL E CRIAÇÃO DAS TAREFAS --- */
/* ========================================================================= */
int main(void) {
    // Configurar botão
    if (device_is_ready(botao.port)) {
        gpio_pin_configure_dt(&botao, GPIO_INPUT);
        gpio_pin_interrupt_configure_dt(&botao, GPIO_INT_EDGE_TO_ACTIVE);
        gpio_init_callback(&button_cb_data, callback_do_botao, BIT(botao.pin));
        gpio_add_callback(botao.port, &button_cb_data);
        printk("INFO: Botão configurado\n");
    } else {
        printk("ERRO: Botão não disponível\n");
    }
    
    // Configurar LED
    if (device_is_ready(led_pisca.port)) {
        printk("INFO: LED configurado\n");
    } else {
        printk("ERRO: LED não disponível\n");
    }
    
    printk("=== Sistema Inicializado ===\n");
    printk("Use os comandos 'sysinfo' e 'rt_info' no shell\n");
    
    return 0;
}

K_THREAD_DEFINE(tid_hard_rt, 1024, tarefa_hard_realtime, NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(tid_soft_rt, 1024, tarefa_soft_realtime, NULL, NULL, NULL, 10, 0, 0);
K_THREAD_DEFINE(tid_botao, 512, tarefa_do_botao, NULL, NULL, NULL, 7, 0, 0);
K_THREAD_DEFINE(tid_led, 512, tarefa_pisca_led, NULL, NULL, NULL, 12, 0, 0);