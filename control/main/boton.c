#include "boton.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdint.h>
#include "esp_system.h"
#include <stdio.h>

#define BOTON_PIN 34

void init_boton(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BOTON_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_ANYEDGE,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    };
    gpio_config(&io_conf);
}

uint32_t button_debounce_time(void) {
    uint32_t time = 0;
    while (gpio_get_level(BOTON_PIN) == 0) {
        vTaskDelay(1000);
        time++;
        if (time > 100){
            return time;
        }
    }
    return 0;
}

/* 

int boton_read() {
    return gpio_get_level(BOTON_PIN);
}
 */
/* 
int boton_read() {
    int state = gpio_get_level(BOTON_PIN);
    
    return state;
} */