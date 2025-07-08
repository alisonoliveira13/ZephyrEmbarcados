// src/shell_sensor.c - Comandos shell para a tarefa de sensor
#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <zephyr/logging/log.h>
#include <stdlib.h>  // Added for atoi function

LOG_MODULE_REGISTER(shell_sensor, LOG_LEVEL_INF);

/* --- REFERÊNCIAS EXTERNAS --- */
extern void get_sensor_stats(uint32_t *total, uint32_t *missed, uint32_t *max_time_us);
extern struct sensor_reading* get_last_reading(void);
extern int get_recent_readings(struct sensor_reading *buffer, int max_count);

struct sensor_reading {
    uint32_t timestamp;
    float temperature;
    float humidity;
    uint32_t sequence;
};

/* --- COMANDO: ESTATÍSTICAS DA TAREFA --- */
static int cmd_sensor_stats(const struct shell *sh, size_t argc, char **argv)
{
    uint32_t total, missed, max_time_us;
    get_sensor_stats(&total, &missed, &max_time_us);
    
    shell_print(sh, "=== ESTATISTICAS DA TAREFA SOFT REAL-TIME ===");
    shell_print(sh, "Total de leituras: %u", total);
    shell_print(sh, "Deadlines perdidos: %u", missed);
    shell_print(sh, "Tempo max processamento: %u us", max_time_us);
    
    if (total > 0) {
        float miss_rate = (float)missed / total * 100.0f;
        shell_print(sh, "Taxa de perda: %.2f%%", (double)miss_rate);  // Fixed: cast to double
        
        if (miss_rate < 5.0f) {
            shell_print(sh, "Status: EXCELENTE (< 5%% perdas)");
        } else if (miss_rate < 15.0f) {
            shell_print(sh, "Status: BOM (< 15%% perdas)");
        } else {
            shell_print(sh, "Status: ATENCAO (> 15%% perdas)");
        }
    }
    
    return 0;
}

/* --- COMANDO: ÚLTIMA LEITURA --- */
static int cmd_sensor_last(const struct shell *sh, size_t argc, char **argv)
{
    struct sensor_reading *reading = get_last_reading();
    
    if (reading == NULL) {
        shell_print(sh, "Nenhuma leitura disponivel ainda");
        return 0;
    }
    
    shell_print(sh, "=== ULTIMA LEITURA ===");
    shell_print(sh, "Sequencia: %u", reading->sequence);
    shell_print(sh, "Timestamp: %u ms", reading->timestamp);
    shell_print(sh, "Temperatura: %.1f °C", (double)reading->temperature);  // Fixed: cast to double
    shell_print(sh, "Umidade: %.1f %%", (double)reading->humidity);  // Fixed: cast to double
    shell_print(sh, "Idade: %u ms", k_uptime_get_32() - reading->timestamp);
    
    return 0;
}

/* --- COMANDO: MÚLTIPLAS LEITURAS --- */
static int cmd_sensor_history(const struct shell *sh, size_t argc, char **argv)
{
    int count = 5; // padrão: 5 leituras
    
    if (argc > 1) {
        count = atoi(argv[1]);
        if (count < 1 || count > 20) {
            shell_error(sh, "Numero de leituras deve estar entre 1 e 20");
            return -EINVAL;
        }
    }
    
    struct sensor_reading buffer[20];
    int readings_count = get_recent_readings(buffer, count);
    
    if (readings_count == 0) {
        shell_print(sh, "Nenhuma leitura disponivel");
        return 0;
    }
    
    shell_print(sh, "=== HISTORICO DE LEITURAS (ultimas %d) ===", readings_count);
    shell_print(sh, "Seq   | Timestamp | Temp(°C) | Umid(%%) | Idade(ms)");
    shell_print(sh, "------|-----------|----------|---------|----------");
    
    uint32_t current_time = k_uptime_get_32();
    for (int i = 0; i < readings_count; i++) {
        shell_print(sh, "%5u | %9u | %7.1f  | %6.1f  | %8u",
                    buffer[i].sequence, buffer[i].timestamp,
                    (double)buffer[i].temperature, (double)buffer[i].humidity,  // Fixed: cast to double
                    current_time - buffer[i].timestamp);
    }
    
    return 0;
}

/* --- COMANDO: INFORMAÇÕES DA TAREFA --- */
static int cmd_sensor_info(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "=== INFORMACOES DA TAREFA SOFT REAL-TIME ===");
    shell_print(sh, "Tipo: Leitura periodica de sensores");
    shell_print(sh, "Periodo: 200 ms (5 Hz)");
    shell_print(sh, "Deadline: 150 ms (soft real-time)");
    shell_print(sh, "Prioridade: 4 (alta)");
    shell_print(sh, "Buffer: 50 leituras");
    shell_print(sh, "Sensores simulados:");
    shell_print(sh, "  - Temperatura: 20-30°C");
    shell_print(sh, "  - Umidade: 40-80%%");
    shell_print(sh, "Caracteristicas soft real-time:");
    shell_print(sh, "  - Pode ocasionalmente perder deadlines");
    shell_print(sh, "  - Degrada graciosamente sob carga");
    shell_print(sh, "  - Mantem precisao temporal media");
    
    return 0;
}

/* --- COMANDO: MONITORAMENTO EM TEMPO REAL --- */
static int cmd_sensor_monitor(const struct shell *sh, size_t argc, char **argv)
{
    int duration = 15; // segundos
    
    if (argc > 1) {
        duration = atoi(argv[1]);
        if (duration < 5 || duration > 60) {
            shell_error(sh, "Duracao deve estar entre 5 e 60 segundos");
            return -EINVAL;
        }
    }
    
    shell_print(sh, "=== MONITORAMENTO EM TEMPO REAL (%d segundos) ===", duration);
    shell_print(sh, "Monitoramento automatico - atualizacao a cada 3 segundos");
    
    uint32_t start_time = k_uptime_get_32();
    uint32_t last_check = start_time;
    uint32_t last_total = 0;
    
    while ((k_uptime_get_32() - start_time) < (duration * 1000)) {
        // Atualiza estatísticas a cada 3 segundos
        if ((k_uptime_get_32() - last_check) >= 3000) {
            uint32_t total, missed, max_time_us;
            get_sensor_stats(&total, &missed, &max_time_us);
            
            struct sensor_reading *last = get_last_reading();
            
            shell_print(sh, "T+%02d: Total=%u (+%u), Perdas=%u, Max=%uus, Ultima=%.1f°C",
                       (k_uptime_get_32() - start_time) / 1000,
                       total, total - last_total, missed, max_time_us,
                       last ? (double)last->temperature : 0.0);  // Fixed: cast to double
            
            last_check = k_uptime_get_32();
            last_total = total;
        }
        
        k_msleep(100);
    }
    
    shell_print(sh, "Monitoramento finalizado");
    return 0;
}

/* --- DEFINIÇÃO DOS SUBCOMANDOS --- */
SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensor,
    SHELL_CMD(stats, NULL, "Estatisticas da tarefa", cmd_sensor_stats),
    SHELL_CMD(last, NULL, "Ultima leitura", cmd_sensor_last),
    SHELL_CMD(history, NULL, "Historico [num_leituras]", cmd_sensor_history),
    SHELL_CMD(info, NULL, "Informacoes da tarefa", cmd_sensor_info),
    SHELL_CMD(monitor, NULL, "Monitor em tempo real [duracao_seg]", cmd_sensor_monitor),
    SHELL_SUBCMD_SET_END
);

/* --- REGISTRO DO COMANDO PRINCIPAL --- */
SHELL_CMD_REGISTER(sensor, &sub_sensor, "Comandos da tarefa de sensor", NULL);