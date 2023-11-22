#include <stdio.h>
#include "driver/gpio.h"
#include "led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

esp_err_t init_led(void) {

    gpio_config_t pGPIOConfig;
    pGPIOConfig.pin_bit_mask = (1ULL << LEDR_PIN) | (1ULL << LEDG_PIN) | (1ULL << LEDB_PIN);
    pGPIOConfig.mode = GPIO_MODE_DEF_OUTPUT;
    pGPIOConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    pGPIOConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
    pGPIOConfig.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&pGPIOConfig);

    return ESP_OK;
}

esp_err_t set_color(uint32_t red, uint32_t green, uint32_t blue) {

    gpio_set_level(LEDR_PIN, red);
    gpio_set_level(LEDG_PIN, green);
    gpio_set_level(LEDB_PIN, blue);

    return ESP_OK;
}

// Variables globales para el estado de los LEDs
bool led_r_state = false;
bool led_g_state = false;
bool led_b_state = false;

void toggle_led(led_t color) {
    switch (color) {
        case LEDR:
            led_r_state = !led_r_state;
            set_color(led_r_state, led_g_state, led_b_state);
            break;
        case LEDG:
            led_g_state = !led_g_state;
            set_color(led_r_state, led_g_state, led_b_state);
            break;
        case LEDB:
            led_b_state = !led_b_state;
            set_color(led_r_state, led_g_state, led_b_state);
            break;
        default:
            // Manejar error o ignorar
            break;
    }
}