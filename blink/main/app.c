#include "app.h"
#include "led_control.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void task_led_blink(void *pvParameters) {
    turn_on_leds();
    vTaskDelay(100);

    turn_off_leds();
    vTaskDelay(100);
}