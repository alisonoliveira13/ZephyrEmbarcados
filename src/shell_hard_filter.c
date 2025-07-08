// src/shell_hard_filter.c - Comandos shell para filtro hard real-time
#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <zephyr/logging/log.h>
#include <stdlib.h>

LOG_MODULE_REGISTER(shell_hard_filter, LOG_LEVEL_INF);

/* --- REFERÊNCIAS EXTERNAS --- */
extern void get_filter_stats(uint32_t *total, uint32_t *missed, uint32_t *max_time, uint32_t *min_time);
extern void get_filter_info(uint32_t *sample_rate, uint32_t *cutoff_freq, uint32_t *deadline_us);

/* --- COMANDO: ESTATÍSTICAS DO FILTRO HARD REAL-TIME --- */
static int cmd_filter_stats(const struct shell *sh, size_t argc, char **argv)
{
    uint32_t total, missed, max_time, min_time;
    get_filter_stats(&total, &missed, &max_time, &min_time);
    
    shell_print(sh, "=== ESTATISTICAS FILTRO HARD REAL-TIME ===");
    shell_print(sh, "Total de amostras: %u", total);
    shell_print(sh, "Deadlines perdidos: %u", missed);
    shell_print(sh, "Tempo processamento:");
    shell_print(sh, "  Minimo: %u us", min_time);
    shell_print(sh, "  Maximo: %u us", max_time);
    
    if (total > 0) {
        float miss_rate = (float)missed / total * 100.0f;
        shell_print(sh, "Taxa de perda: %.4f%%", (double)miss_rate);
        
        // Para hard real-time, QUALQUER perda é crítica
        if (missed == 0) {
            shell_print(sh, "Status: PERFEITO (0 perdas) - Hard Real-Time OK");
        } else {
            shell_print(sh, "Status: FALHA CRITICA (%u perdas) - Hard Real-Time VIOLADO", missed);
            shell_print(sh, "ACAO NECESSARIA: Sistema nao atende requisitos hard real-time");
        }
        
        // Análise do jitter
        if (max_time > 0 && min_time > 0) {
            uint32_t jitter = max_time - min_time;
            shell_print(sh, "Jitter: %u us", jitter);
            if (jitter > 20) {
                shell_print(sh, "AVISO: Jitter alto pode indicar problemas de determinismo");
            }
        }
    }
    
    return 0;
}

/* --- COMANDO: INFORMAÇÕES DO FILTRO --- */
static int cmd_filter_info(const struct shell *sh, size_t argc, char **argv)
{
    uint32_t sample_rate, cutoff_freq, deadline_us;
    get_filter_info(&sample_rate, &cutoff_freq, &deadline_us);
    
    shell_print(sh, "=== INFORMACOES DO FILTRO HARD REAL-TIME ===");
    shell_print(sh, "Tipo: Filtro IIR Butterworth passa-baixa");
    shell_print(sh, "Ordem: 4");
    shell_print(sh, "Frequencia de amostragem: %u Hz", sample_rate);
    shell_print(sh, "Frequencia de corte: %u Hz", cutoff_freq);
    shell_print(sh, "Periodo de amostragem: %u us", 1000000 / sample_rate);
    shell_print(sh, "Deadline HARD: %u us", deadline_us);
    shell_print(sh, "Prioridade: 2 (maxima)");
    
    shell_print(sh, "");
    shell_print(sh, "Caracteristicas Hard Real-Time:");
    shell_print(sh, "  - Deadline rigido de %u us", deadline_us);
    shell_print(sh, "  - Processamento deterministico");
    shell_print(sh, "  - Nenhuma perda de deadline tolerada");
    shell_print(sh, "  - Tempo de resposta garantido");
    shell_print(sh, "  - Preempcao de todas as outras tarefas");
    
    shell_print(sh, "");
    shell_print(sh, "Fluxo de dados:");
    shell_print(sh, "  ADC -> Filtro Digital -> DAC");
    shell_print(sh, "  Timer -> Amostragem -> Processamento -> Saida");
    
    return 0;
}

/* --- COMANDO: MONITORAMENTO EM TEMPO REAL --- */
static int cmd_filter_monitor(const struct shell *sh, size_t argc, char **argv)
{
    int duration = 10; // segundos
    
    if (argc > 1) {
        duration = atoi(argv[1]);
        if (duration < 5 || duration > 60) {
            shell_error(sh, "Duracao deve estar entre 5 e 60 segundos");
            return -EINVAL;
        }
    }
    
    shell_print(sh, "=== MONITORAMENTO HARD REAL-TIME (%d segundos) ===", duration);
    shell_print(sh, "Monitorando violacoes de deadline...");
    
    uint32_t start_time = k_uptime_get_32();
    uint32_t last_check = start_time;
    uint32_t last_total = 0;
    uint32_t last_missed = 0;
    
    while ((k_uptime_get_32() - start_time) < (duration * 1000)) {
        // Verifica estatísticas a cada segundo
        if ((k_uptime_get_32() - last_check) >= 1000) {
            uint32_t total, missed, max_time, min_time;
            get_filter_stats(&total, &missed, &max_time, &min_time);
            
            uint32_t new_samples = total - last_total;
            uint32_t new_missed = missed - last_missed;
            
            shell_print(sh, "T+%02d: Amostras=%u (+%u/s), Perdas=%u (+%u), Max=%uus, Min=%uus",
                       (k_uptime_get_32() - start_time) / 1000,
                       total, new_samples, missed, new_missed, max_time, min_time);
            
            if (new_missed > 0) {
                shell_print(sh, "     !!! VIOLACAO HARD REAL-TIME DETECTADA !!!");
            }
            
            last_check = k_uptime_get_32();
            last_total = total;
            last_missed = missed;
        }
        
        k_msleep(100);
    }
    
    shell_print(sh, "Monitoramento finalizado");
    
    // Relatório final
    uint32_t total, missed, max_time, min_time;
    get_filter_stats(&total, &missed, &max_time, &min_time);
    
    shell_print(sh, "");
    shell_print(sh, "=== RELATORIO FINAL ===");
    shell_print(sh, "Amostras processadas: %u", total);
    shell_print(sh, "Deadlines perdidos: %u", missed);
    shell_print(sh, "Taxa de amostragem media: %.1f Hz", (double)total / duration);
    
    if (missed == 0) {
        shell_print(sh, "RESULTADO: Sistema atende requisitos hard real-time");
    } else {
        shell_print(sh, "RESULTADO: Sistema FALHOU nos requisitos hard real-time");
    }
    
    return 0;
}

/* --- COMANDO: TESTE DE STRESS --- */
static int cmd_filter_stress(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "=== TESTE DE STRESS HARD REAL-TIME ===");
    shell_print(sh, "Iniciando teste de stress por 30 segundos...");
    shell_print(sh, "Este teste adiciona carga ao sistema para verificar determinismo");
    
    // Cria carga adicional no sistema
    uint32_t start_time = k_uptime_get_32();
    uint32_t stress_count = 0;
    
    while ((k_uptime_get_32() - start_time) < 30000) {
        // Adiciona trabalho computacional
        volatile float dummy = 0.0f;
        for (int i = 0; i < 1000; i++) {
            dummy += sin(i * 0.1f);
        }
        stress_count++;
        
        // Verifica estatísticas periodicamente
        if ((stress_count % 100) == 0) {
            uint32_t total, missed, max_time, min_time;
            get_filter_stats(&total, &missed, &max_time, &min_time);
            
            shell_print(sh, "Stress %u: Amostras=%u, Perdas=%u, Max=%uus",
                       stress_count, total, missed, max_time);
        }
        
        k_msleep(10);
    }
    
    shell_print(sh, "Teste de stress finalizado");
    
    uint32_t total, missed, max_time, min_time;
    get_filter_stats(&total, &missed, &max_time, &min_time);
    
    shell_print(sh, "");
    shell_print(sh, "=== RESULTADO DO TESTE DE STRESS ===");
    shell_print(sh, "Iteracoes de stress: %u", stress_count);
    shell_print(sh, "Amostras processadas: %u", total);
    shell_print(sh, "Deadlines perdidos: %u", missed);
    
    if (missed == 0) {
        shell_print(sh, "RESULTADO: Sistema mantem hard real-time sob stress");
    } else {
        shell_print(sh, "RESULTADO: Sistema perde hard real-time sob stress");
        shell_print(sh, "Necessario otimizar prioridades ou reduzir carga");
    }
    
    return 0;
}

/* --- COMANDO: ANÁLISE DE LATÊNCIA --- */
static int cmd_filter_latency(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "=== ANALISE DE LATENCIA HARD REAL-TIME ===");
    
    uint32_t sample_rate, cutoff_freq, deadline_us;
    get_filter_info(&sample_rate, &cutoff_freq, &deadline_us);
    
    uint32_t total, missed, max_time, min_time;
    get_filter_stats(&total, &missed, &max_time, &min_time);
    
    shell_print(sh, "Deadline configurado: %u us", deadline_us);
    shell_print(sh, "Latencia minima: %u us", min_time);
    shell_print(sh, "Latencia maxima: %u us", max_time);
    
    if (total > 0) {
        uint32_t jitter = max_time - min_time;
        shell_print(sh, "Jitter: %u us", jitter);
        
        float deadline_margin = ((float)(deadline_us - max_time) / deadline_us) * 100.0f;
        shell_print(sh, "Margem de deadline: %.1f%%", (double)deadline_margin);
        
        shell_print(sh, "");
        shell_print(sh, "Analise de determinismo:");
        if (jitter < 10) {
            shell_print(sh, "  Jitter: EXCELENTE (< 10us)");
        } else if (jitter < 30) {
            shell_print(sh, "  Jitter: BOM (< 30us)");
        } else {
            shell_print(sh, "  Jitter: RUIM (> 30us) - Verificar sistema");
        }
        
        if (deadline_margin > 20.0f) {
            shell_print(sh, "  Margem: SEGURA (> 20%%)");
        } else if (deadline_margin > 10.0f) {
            shell_print(sh, "  Margem: ACEITAVEL (> 10%%)");
        } else {
            shell_print(sh, "  Margem: CRITICA (< 10%%) - Risco de violacao");
        }
    }
    
    return 0;
}

/* --- DEFINIÇÃO DOS SUBCOMANDOS --- */
SHELL_STATIC_SUBCMD_SET_CREATE(sub_filter,
    SHELL_CMD(stats, NULL, "Estatisticas do filtro hard real-time", cmd_filter_stats),
    SHELL_CMD(info, NULL, "Informacoes do filtro", cmd_filter_info),
    SHELL_CMD(monitor, NULL, "Monitor em tempo real [duracao_seg]", cmd_filter_monitor),
    SHELL_CMD(stress, NULL, "Teste de stress do sistema", cmd_filter_stress),
    SHELL_CMD(latency, NULL, "Analise de latencia e jitter", cmd_filter_latency),
    SHELL_SUBCMD_SET_END
);

/* --- REGISTRO DO COMANDO PRINCIPAL --- */
SHELL_CMD_REGISTER(filter, &sub_filter, "Comandos do filtro hard real-time", NULL);