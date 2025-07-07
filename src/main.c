#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/usb/usb_device.h> // Importante para a função usb_enable()

/* --- TAREFA 1: PISCAR O LED --- */
#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void blink_led_task(void)
{
    if (!gpio_is_ready_dt(&led)) {
        printk("Erro: dispositivo LED não está pronto.\n");
        return;
    }
    gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    while (1) {
        gpio_pin_toggle_dt(&led);
        k_msleep(1000); // Pisca mais devagar
    }
}

/* --- TAREFA 4: ACIONAMENTO PELO BOTÃO --- */
#define BUTTON0_NODE DT_ALIAS(sw0)
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(BUTTON0_NODE, gpios);
static struct gpio_callback button_cb_data;
K_SEM_DEFINE(button_sem, 0, 1);

// Callback da interrupção: apenas sinaliza o semáforo
void button_pressed_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    k_sem_give(&button_sem);
}

// Tarefa que espera pelo semáforo e executa a ação
void button_action_task(void)
{
    while (1) {
        k_sem_take(&button_sem, K_FOREVER);
        printk("Botao azul pressionado!\n");
    }
}

/* --- FUNÇÃO PRINCIPAL (PONTO DE ENTRADA DO PROGRAMA) --- */
int main(void)
{
    // 1. Inicializa o hardware do botão
    if (!gpio_is_ready_dt(&button)) {
        printk("Erro: dispositivo Botao nao esta pronto.\n");
        return 0;
    }
    gpio_pin_configure_dt(&button, GPIO_INPUT);
    gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
    gpio_init_callback(&button_cb_data, button_pressed_callback, BIT(button.pin));
    gpio_add_callback(button.port, &button_cb_data);

    // 2. ATIVA O HARDWARE USB (A LINHA QUE FALTAVA!)
    // Esta chamada faz com que a placa se anuncie como um dispositivo USB para o PC
    if (usb_enable(NULL) != 0) {
        printk("Falha ao habilitar o USB.\n");
        return 0;
    }

    // A partir daqui, as tarefas (threads) definidas abaixo começarão a rodar.
    // O printk abaixo só aparecerá depois que o USB estiver ativo e você se conectar.
    printk("Sistema iniciado! LED piscando e botao pronto.\n");
    return 0;
}


// Cria e inicia as tarefas em paralelo
K_THREAD_DEFINE(blink_led_tid, 512, blink_led_task, NULL, NULL, NULL, 7, 0, 0);
K_THREAD_DEFINE(button_action_tid, 512, button_action_task, NULL, NULL, NULL, 7, 0, 0);