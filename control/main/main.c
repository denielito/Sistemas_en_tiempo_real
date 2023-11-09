#include "led_control.h"
#include "boton.h"
#include "app.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void app_main() {
    led_init();
    init_boton();

    set_color(1,0,1);

    xTaskCreate(task_boton,"task_boton", 4096, NULL, 5, NULL);
}
