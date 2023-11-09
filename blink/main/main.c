#include <stdio.h>
#include "app.h"
#include "led_control.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main() {
    led_init();

    xTaskCreate(&task_led_blink, "task_led_blink", 2048, NULL, 5, NULL);
}
