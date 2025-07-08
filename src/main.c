// src/main.c - Versão com Tempo Real Soft
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/* --- SEM REFERÊNCIAS EXTERNAS DESNECESSÁRIAS --- */

/* --- TAREFA 1: PISCAR O LED (BAIXA PRIORIDADE) --- */
#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void blink_led_task(void)
{
    if (!gpio_is_ready_dt(&led)) {
        LOG_ERR("LED0 não está pronto");
        return;
    }
    
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    LOG_INF("LED de status iniciado");
    
    while (1) {
        gpio_pin_toggle_dt(&led);
        k_msleep(2000); // Pisca mais devagar para não interferir
    }
}

/* --- TAREFA 2: ACIONAMENTO PELO BOTÃO --- */
#define BUTTON0_NODE DT_ALIAS(sw0)
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(BUTTON0_NODE, gpios);
static struct gpio_callback button_cb_data;
K_SEM_DEFINE(button_sem, 0, 1);

void button_pressed_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    k_sem_give(&button_sem);
}

void button_action_task(void)
{
    uint32_t press_count = 0;
    
    while (1) {
        k_sem_take(&button_sem, K_FOREVER);
        press_count++;
        
        LOG_INF("Botao pressionado! Contagem: %u", press_count);
        
        // Indica pressionamento com LED por 100ms
        gpio_pin_set_dt(&led, 1);
        k_msleep(100);
        gpio_pin_set_dt(&led, 0);
    }
}

/* --- FUNÇÃO PRINCIPAL --- */
int main(void)
{
    LOG_INF("=== SISTEMA TEMPO REAL SOFT INICIANDO ===");
    
    
    
    // 2. Inicializa hardware do botão
    if (!gpio_is_ready_dt(&button)) {
        LOG_ERR("Botão não está pronto");
        return 0;
    }
    
    gpio_pin_configure_dt(&button, GPIO_INPUT);
    gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
    gpio_init_callback(&button_cb_data, button_pressed_callback, BIT(button.pin));
    gpio_add_callback(button.port, &button_cb_data);
    
    // 3. Sistema pronto!
    
    LOG_INF("Sistema iniciado com sucesso!");
    LOG_INF("Funcionalidades disponiveis:");
    LOG_INF("  - LED de status piscando");
    LOG_INF("  - Botao interativo");
    LOG_INF("  - Tarefa soft real-time: leitura de sensores (5Hz)");
    LOG_INF("  - Shell com comandos 'sensor' e 'sysinfo'");
    LOG_INF("Use 'sensor info' para detalhes da tarefa tempo real");
    
    return 0;
}

/* --- DEFINIÇÃO DAS THREADS COM PRIORIDADES AJUSTADAS --- */
// Prioridade 4: Sensor (soft real-time - mais alta)
// Prioridade 7: Botão (responsividade)
// Prioridade 10: LED (menor prioridade)

K_THREAD_DEFINE(blink_led_tid, 512, blink_led_task, NULL, NULL, NULL, 10, 0, 0);
K_THREAD_DEFINE(button_action_tid, 512, button_action_task, NULL, NULL, NULL, 7, 0, 0);