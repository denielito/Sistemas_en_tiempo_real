#include "driver/gpio.h"
#include "led.h"
#include "boton.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BOTON_PIN 34
#define DEBOUNCE_DELAY 50

uint32_t counter = 0;

esp_err_t init_boton(void) {
    gpio_config_t boton_config;
    boton_config.pin_bit_mask = (1ULL << BOTON_PIN);
    boton_config.mode = GPIO_MODE_INPUT;
    boton_config.pull_up_en = GPIO_PULLUP_DISABLE;
    boton_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
    boton_config.intr_type = GPIO_INTR_ANYEDGE;  // Cambiado a cualquier flanco
    gpio_config(&boton_config);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BOTON_PIN, read_boton, NULL);

    return ESP_OK;
}

void read_boton(void *args) {
    int state = gpio_get_level(BOTON_PIN);
    uint32_t color = 0;
    uint32_t red, green, blue;

    while (1) {
        int current_state = gpio_get_level(BOTON_PIN);

        if (current_state != state) {
            vTaskDelay(DEBOUNCE_DELAY);

            int new_state = gpio_get_level(BOTON_PIN);

            if (current_state == new_state) {
                color = (color + 1) % 3;
            }

            switch (color) {
                case 0: red = 1; green = 0; blue = 0; break;
                case 1: red = 0; green = 1; blue = 0; break;
                case 2: red = 0; green = 0; blue = 1; break;
                default: red = 0; green = 0; blue = 0; break;
            }

            set_color(red, green, blue);
            printf("Button state changed: %d\n", current_state);
            state = current_state;
        }

        vTaskDelay(100);  // Cambiado a portTICK_RATE_MS para mayor portabilidad
    }
}
