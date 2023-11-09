#include "led_control.h"
#include "driver/gpio.h"

#define LED1_GPIO_PIN 25 // AZUL
#define LED2_GPIO_PIN 26 // VERDE
#define LED3_GPIO_PIN 27 // ROJO

void led_init() {
    gpio_set_direction(LED1_GPIO_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2_GPIO_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED3_GPIO_PIN, GPIO_MODE_OUTPUT);
}

void turn_on_leds() {
    gpio_set_level(LED1_GPIO_PIN, 1);
    gpio_set_level(LED2_GPIO_PIN, 1);
    gpio_set_level(LED3_GPIO_PIN, 1);
}

void turn_off_leds() {
    gpio_set_level(LED1_GPIO_PIN, 0);
    gpio_set_level(LED2_GPIO_PIN, 0);
    gpio_set_level(LED3_GPIO_PIN, 0);
}