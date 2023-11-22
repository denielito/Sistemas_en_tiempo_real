#ifndef LED_H
#define LED_H

#include "esp_err.h"

typedef enum {
    LEDR,
    LEDG,
    LEDB
} led_t;

#define LEDR_PIN 27
#define LEDG_PIN 26
#define LEDB_PIN 25

esp_err_t init_led(void);
esp_err_t set_color(uint32_t red, uint32_t green, uint32_t blue);
void toggle_led(led_t color);

#endif