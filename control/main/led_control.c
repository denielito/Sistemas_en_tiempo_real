#include "led_control.h"
#include "driver/gpio.h"

#define LED_AZUL 13 // AZUL
#define LED_VERDE 12 // VERDE
#define LED_ROJO 14 // ROJO

void led_init() {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED_ROJO) | (1ULL << LED_VERDE) | (1ULL << LED_AZUL),
        .mode = GPIO_MODE_OUTPUT,
        .intr_type = GPIO_INTR_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
    };
    gpio_config(&io_conf);
}

void set_color (int red, int green, int blue) {
    gpio_set_level(LED_ROJO, red);
    gpio_set_level(LED_VERDE, green);
    gpio_set_level(LED_AZUL, blue);
}