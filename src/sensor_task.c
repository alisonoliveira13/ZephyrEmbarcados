// src/sensor_task.c - Uma tarefa de tempo real soft (com correções de warnings)
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/random/random.h>

LOG_MODULE_REGISTER(sensor_task, LOG_LEVEL_INF);

/* --- ESTRUTURA DE DADOS DO SENSOR --- */
struct sensor_reading {
    uint32_t timestamp;
    float temperature;
    float humidity;
    uint32_t sequence;
};

/* --- CONFIGURAÇÕES DA TAREFA TEMPO REAL SOFT --- */
#define SENSOR_PERIOD_MS 200        // 5Hz - leitura a cada 200ms
#define SENSOR_DEADLINE_MS 150      // Deadline de 150ms (soft real-time)
#define MAX_READINGS 50             // Buffer para últimas 50 leituras

/* --- VARIÁVEIS GLOBAIS --- */
static struct sensor_reading readings[MAX_READINGS];
static uint32_t reading_index = 0;
static uint32_t total_readings = 0;
static uint32_t missed_deadlines = 0;
static uint32_t max_processing_time_us = 0;

/* --- TAREFA DE LEITURA PERIÓDICA DE SENSORES (SOFT REAL-TIME) --- */
void sensor_reading_task(void)
{
    uint32_t start_time, processing_time;
    uint32_t next_period = k_uptime_get_32();
    
    LOG_INF("=== TAREFA SOFT REAL-TIME INICIADA ===");
    LOG_INF("Periodo: %d ms, Deadline: %d ms", SENSOR_PERIOD_MS, SENSOR_DEADLINE_MS);
    
    while (1) {
        start_time = k_cycle_get_32();
        
        // Simula leitura de sensores de temperatura e umidade
        struct sensor_reading *current = &readings[reading_index];
        
        current->timestamp = k_uptime_get_32();
        current->sequence = total_readings++;
        
        // Simula sensor de temperatura (20-30°C)
        current->temperature = 25.0f + (float)(sys_rand32_get() % 1000) / 100.0f - 5.0f;
        
        // Simula sensor de umidade (40-80%)
        current->humidity = 60.0f + (float)(sys_rand32_get() % 4000) / 100.0f - 20.0f;
        
        // Simula tempo de processamento variável (leitura I2C, ADC, etc.)
        // Tempo real soft: pode ocasionalmente perder deadline
        uint32_t processing_delay = sys_rand32_get() % 100000; // 0-100ms
        k_busy_wait(processing_delay);
        
        // Calcula tempo de processamento
        processing_time = k_cycle_get_32() - start_time;
        uint32_t processing_time_us = k_cyc_to_us_floor32(processing_time);
        
        // Atualiza estatísticas
        if (processing_time_us > max_processing_time_us) {
            max_processing_time_us = processing_time_us;
        }
        
        // Verifica se perdeu o deadline (característica soft real-time)
        if (processing_time_us > (SENSOR_DEADLINE_MS * 1000)) {
            missed_deadlines++;
            LOG_WRN("Deadline perdido! Seq=%u, Tempo=%u us (limite=%u us)",
                    current->sequence, processing_time_us, SENSOR_DEADLINE_MS * 1000);
        }
        
        // Log periódico dos dados - CORREÇÃO: cast explícito para double
        if ((total_readings % 10) == 0) {
            LOG_INF("Leitura #%u: T=%.1f°C, H=%.1f%%, tempo=%u us",
                    current->sequence, (double)current->temperature, (double)current->humidity, processing_time_us);
        }
        
        // Avança índice circular
        reading_index = (reading_index + 1) % MAX_READINGS;
        
        // Aguarda próximo período (característica periódica)
        next_period += SENSOR_PERIOD_MS;
        k_sleep(K_TIMEOUT_ABS_MS(next_period));
    }
}

/* --- FUNÇÃO PARA OBTER ESTATÍSTICAS (PARA O SHELL) --- */
void get_sensor_stats(uint32_t *total, uint32_t *missed, uint32_t *max_time_us)
{
    *total = total_readings;
    *missed = missed_deadlines;
    *max_time_us = max_processing_time_us;
}

/* --- FUNÇÃO PARA OBTER ÚLTIMA LEITURA --- */
struct sensor_reading* get_last_reading(void)
{
    if (total_readings == 0) {
        return NULL;
    }
    
    uint32_t last_index = (reading_index + MAX_READINGS - 1) % MAX_READINGS;
    return &readings[last_index];
}

/* --- FUNÇÃO PARA OBTER MÚLTIPLAS LEITURAS --- */
int get_recent_readings(struct sensor_reading *buffer, int max_count)
{
    int count = 0;
    int available = (total_readings < MAX_READINGS) ? total_readings : MAX_READINGS;
    
    if (available == 0) {
        return 0;
    }
    
    // Copia as leituras mais recentes
    for (int i = 0; i < available && count < max_count; i++) {
        int index = (reading_index + MAX_READINGS - 1 - i) % MAX_READINGS;
        buffer[count++] = readings[index];
    }
    
    return count;
}

/* --- DEFINIÇÃO DA THREAD COM PRIORIDADE ALTA (TEMPO REAL) --- */
K_THREAD_DEFINE(sensor_tid, 1024, sensor_reading_task, NULL, NULL, NULL, 4, 0, 0);