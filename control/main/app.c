#include "app.h"
#include "led_control.h"
#include "boton.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void task_boton(void *pvParameters) {
    int counter = 1;

    while(1) {
        uint32_t debounce_time = button_debounce_time();
        if (debounce_time > 0) {
            switch (counter) {
                case 1:
                    set_color(1,0,0);
                    break;
                case 2:
                    set_color(0,1,0);
                    break;
                case 3:
                    set_color(0,0,1);
                    break;
            }
            counter = (counter % 3) + 1;
            vTaskDelay(500);
        }
        vTaskDelay(500);
    }
}