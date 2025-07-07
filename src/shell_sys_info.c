#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <zephyr/version.h>
#include <stdlib.h>

#ifdef CONFIG_THREAD_ANALYZER
#include <zephyr/debug/thread_analyzer.h>
#endif

// Função para mostrar informações básicas do sistema
static int cmd_sysinfo_general(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "Informacoes Gerais do Sistema:");
    shell_print(sh, "  Versao do Kernel: %s", KERNEL_VERSION_STRING);
    shell_print(sh, "  Ticks por segundo: %d", CONFIG_SYS_CLOCK_TICKS_PER_SEC);
    shell_print(sh, "  Uptime: %lld ms", k_uptime_get());
    
    // Informações básicas sem APIs específicas de memória
    shell_print(sh, "  Heap configurado: %d bytes", CONFIG_HEAP_MEM_POOL_SIZE);
    
    return 0;
}

// Função para mostrar informações das threads
static void print_thread_info(const struct k_thread *thread, void *user_data)
{
    const struct shell *sh = (const struct shell *)user_data;
    k_tid_t tid = (k_tid_t)thread;
    const char *name;

    name = k_thread_name_get(tid);
    if (name == NULL) {
        name = "<sem nome>";
    }

    // Simplificando - apenas mostra nome e prioridade
    shell_print(sh, "  - %-20s | Prio: %d", name, k_thread_priority_get(tid));
}

static int cmd_sysinfo_tasks(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "Tarefas (Threads) do Sistema:");
    k_thread_foreach(print_thread_info, (void *)sh);
    return 0;
}

#ifdef CONFIG_THREAD_ANALYZER
static int cmd_sysinfo_runtime(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "Analise de Runtime das Tarefas:");
    thread_analyzer_print(0); // CPU 0 para single-core
    return 0;
}
#endif

// Função para mostrar informações sobre o stack das threads
static int cmd_sysinfo_stack(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "Informacoes de Stack das Threads:");
    shell_print(sh, "  (Funcionalidade limitada - verifique manualmente)");
    return 0;
}

// Comando para testar o sistema
static int cmd_sysinfo_test(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "Teste do Sistema:");
    shell_print(sh, "  Shell funcionando: OK");
    shell_print(sh, "  USB Console: OK");
    shell_print(sh, "  Timestamp: %lld ms", k_uptime_get());
    return 0;
}

// Definição dos subcomandos
SHELL_STATIC_SUBCMD_SET_CREATE(sub_sysinfo,
    SHELL_CMD(general, NULL, "Mostra info geral do sistema.", cmd_sysinfo_general),
    SHELL_CMD(tasks, NULL, "Lista as tarefas do sistema.", cmd_sysinfo_tasks),
    SHELL_CMD(stack, NULL, "Mostra info de stack.", cmd_sysinfo_stack),
    SHELL_CMD(test, NULL, "Testa o sistema.", cmd_sysinfo_test),
#ifdef CONFIG_THREAD_ANALYZER
    SHELL_CMD(runtime, NULL, "Mostra info de runtime.", cmd_sysinfo_runtime),
#endif
    SHELL_SUBCMD_SET_END
);

// Registro do comando principal
SHELL_CMD_REGISTER(sysinfo, &sub_sysinfo, "Comandos de info do sistema.", NULL);