#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

/* --- REFERÊNCIAS EXTERNAS --- */
extern int init_hard_realtime_filter(void);

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
        k_msleep(50);
        k_sem_reset(&button_sem);


    }
}

/* --- FUNÇÃO PRINCIPAL --- */
int main(void)
{
    // 1. Inicializa filtro hard real-time
    int ret = init_hard_realtime_filter();
    if (ret < 0) {
        LOG_ERR("Falha ao inicializar filtro hard real-time: %d", ret);
        LOG_ERR("Sistema continuara sem filtro hard real-time");
    } 
    
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
    
   
    LOG_INF("Comandos shell disponiveis:");
    LOG_INF("  - 'sensor' - Comandos da tarefa soft real-time");
    LOG_INF("  - 'filter' - Comandos da tarefa hard real-time");
    LOG_INF("  - 'sysinfo' - Informacoes do sistema");
    
    return 0;
}

/* --- DEFINIÇÃO DAS THREADS COM PRIORIDADES HIERARQUICAS --- */
// Prioridade 2: Filtro hard real-time (definido em hard_realtime_filter.c)
// Prioridade 3: Amostragem ADC (definido em hard_realtime_filter.c)
// Prioridade 4: Sensor soft real-time (definido em sensor_task.c)
// Prioridade 7: Botão (responsividade)
// Prioridade 10: LED (menor prioridade)

K_THREAD_DEFINE(blink_led_tid, 512, blink_led_task, NULL, NULL, NULL, 10, 0, 0);
K_THREAD_DEFINE(button_action_tid, 512, button_action_task, NULL, NULL, NULL, 7, 0, 0);