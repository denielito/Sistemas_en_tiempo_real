#include "motor.h"

/* QueueHandle_t sensor5_queue; */


void servo_init()
{
    ledc_timer_config_t timer_conf = {
        .duty_resolution = LEDC_TIMER_10_BIT, // Resolución de 10 bits para mayor precisión
        .freq_hz = SERVO_PWM_FREQ,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = SERVO_PWM_TIMER,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ledc_timer_config(&timer_conf);

    ledc_channel_config_t channel_conf = {
        .gpio_num = SERVO_GPIO_PIN,
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = SERVO_PWM_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = SERVO_PWM_TIMER,
        .duty = 0,
    };
    ledc_channel_config(&channel_conf);

    static uint8_t ucparameterToPass;
    TaskHandle_t xHandle = NULL;

    xTaskCreate(servo_task, "servo", 2048, &ucparameterToPass, 2, &xHandle);

}

void set_servo_position(int position)
{
    // Convierte el ángulo de 0-180 grados a un valor de duty cycle para el servo
    int duty = (int)(position / 180.0 * 1023);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, SERVO_PWM_CHANNEL, duty);
    ledc_update_duty(LEDC_HIGH_SPEED_MODE, SERVO_PWM_CHANNEL);
}


void servo_task(void *pvParameters)
{
    int state_s5;


    while (1)
    {

        xQueueReceive(sensor5_queue, &state_s5, portMAX_DELAY);
        if (state_s5 == 0)
        {
            // Gira el servo desde 0 a 90 grados
            for (int pos = 0; pos <= 90; pos += 10)
            {
                set_servo_position(pos);
                vTaskDelay(pdMS_TO_TICKS(50));
            }
        }
        else
        {
            // vTaskDelay(pdMS_TO_TICKS(1000));

            // Gira el servo desde 90 a 0 grados
            for (int pos = 90; pos >= 0; pos -= 10)
            {
                set_servo_position(pos);
                vTaskDelay(pdMS_TO_TICKS(400));
            }
        }

    }
}

/* 
void app_main()
{
    servo_init();
    init_sensor();

    static uint8_t ucparameterToPass;
    TaskHandle_t xHandle = NULL;

    sensor5_queue = xQueueCreate(5, sizeof(int));

    xTaskCreate(state_in_task, "abrir", 2048, &ucparameterToPass, 2, &xHandle);
    
} */