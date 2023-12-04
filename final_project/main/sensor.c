#include "sensor.h"

SensorData data;
QueueHandle_t sensor1_queue;
QueueHandle_t sensor2_queue;
QueueHandle_t sensor3_queue;
QueueHandle_t sensor4_queue;
QueueHandle_t sensor5_queue;
QueueHandle_t sensor6_queue;

esp_err_t sensor_init(void)
{
    gpio_config_t io_conf_sensor1 = {
        .pin_bit_mask = (1ULL << IR_SENSOR1_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_ANYEDGE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };
    gpio_config(&io_conf_sensor1);

    gpio_config_t io_conf_sensor2 = {
        .pin_bit_mask = (1ULL << IR_SENSOR2_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_ANYEDGE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };
    gpio_config(&io_conf_sensor2);

    gpio_config_t io_conf_sensor3 = {
        .pin_bit_mask = (1ULL << IR_SENSOR3_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_ANYEDGE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };
    gpio_config(&io_conf_sensor3);

    gpio_config_t io_conf_sensor4 = {
        .pin_bit_mask = (1ULL << IR_SENSOR4_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_ANYEDGE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };
    gpio_config(&io_conf_sensor4);

    gpio_config_t io_conf_sensor5 = {
        .pin_bit_mask = (1ULL << IR_SENSOR5_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_ANYEDGE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };
    gpio_config(&io_conf_sensor5);

    gpio_config_t io_conf_sensor6 = {
        .pin_bit_mask = (1ULL << IR_SENSOR6_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_ANYEDGE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
    };
    gpio_config(&io_conf_sensor6);

    sensor1_queue = xQueueCreate(3, sizeof(int));
    sensor2_queue = xQueueCreate(3, sizeof(int));
    sensor3_queue = xQueueCreate(3, sizeof(int));
    sensor4_queue = xQueueCreate(3, sizeof(int));
    sensor5_queue = xQueueCreate(3, sizeof(int));
    sensor6_queue = xQueueCreate(3, sizeof(int));

    return ESP_OK;
}

esp_err_t create_task(void)
{

    static uint8_t ucparameterToPass;
    TaskHandle_t xHandle = NULL;

    xTaskCreate(state_a1, "state_a1", STACK_SIZE, &ucparameterToPass, 1, &xHandle);
    xTaskCreate(state_a3, "state_a3", STACK_SIZE, &ucparameterToPass, 1, &xHandle);
    xTaskCreate(state_b2, "state_b2", STACK_SIZE, &ucparameterToPass, 1, &xHandle);
    xTaskCreate(state_b4, "state_b4", STACK_SIZE, &ucparameterToPass, 1, &xHandle);
    xTaskCreate(state_IN, "state_IN", STACK_SIZE, &ucparameterToPass, 1, &xHandle);
    xTaskCreate(state_OUT, "state_OUT", STACK_SIZE, &ucparameterToPass, 1, &xHandle);

    return ESP_OK;
}

void state_a1(void *pvParameters)
{
    // int sensor1_current_state = 1;
    while (1)
    {
        int sensor_1 = gpio_get_level(IR_SENSOR1_PIN);
        /* if (sensor_1 != sensor1_current_state)
        { */
        xQueueSend(sensor1_queue, &sensor_1, portMAX_DELAY); // Enviar valor a la cola
        // sensor1_current_state = sensor_1;
        vTaskDelay(100 / portTICK_PERIOD_MS); // Espera 1 segundo
        // }
    }
}

void state_a3(void *pvParameters)
{
    // int sensor2_current_state = 1;
    while (1)
    {
        int sensor_2 = gpio_get_level(IR_SENSOR2_PIN);
        /* if (sensor_2 != sensor2_current_state)
        { */
        xQueueSend(sensor2_queue, &sensor_2, portMAX_DELAY); // Enviar valor a la cola
        // sensor2_current_state = sensor_2;
        vTaskDelay(100 / portTICK_PERIOD_MS); // Espera 1 segundo
        // }
    }
}

void state_b2(void *pvParameters)
{
    // int sensor3_current_state = 1;
    while (1)
    {
        int sensor_3 = gpio_get_level(IR_SENSOR3_PIN);
        /* if (sensor_3 != sensor3_current_state)
        { */
        xQueueSend(sensor3_queue, &sensor_3, portMAX_DELAY); // Enviar valor a la cola
        // sensor3_current_state = sensor_3;
        vTaskDelay(100 / portTICK_PERIOD_MS); // Espera 1 segundo
        // }
    }
}

void state_b4(void *pvParameters)
{
    // int sensor4_current_state = 1;
    while (1)
    {
        int sensor_4 = gpio_get_level(IR_SENSOR4_PIN);
        /* if (sensor_4 != sensor4_current_state)
        { */
        xQueueSend(sensor4_queue, &sensor_4, portMAX_DELAY); // Enviar valor a la cola
        // sensor4_current_state = sensor_4;
        vTaskDelay(100 / portTICK_PERIOD_MS); // Espera 1 segundo
        // }
    }
}

void state_IN(void *pvParameters)
{
    // int sensor5_current_state = 1;
    while (1)
    {
        int sensor_value5 = gpio_get_level(IR_SENSOR5_PIN);
        /* if (sensor_value5 != sensor5_current_state)
        { */
        xQueueSend(sensor5_queue, &sensor_value5, portMAX_DELAY); // Enviar valor a la cola
        // sensor5_current_state = sensor_value5;
        vTaskDelay(10 / portTICK_PERIOD_MS); // Espera 1 segundo
        // }
    }
}

void state_OUT(void *pvParameters)
{
    // int sensor6_current_state = 1;
    while (1)
    {
        int sensor_value6 = gpio_get_level(IR_SENSOR6_PIN);
        /* if (sensor_value6 != sensor6_current_state)
        { */
        xQueueSend(sensor6_queue, &sensor_value6, portMAX_DELAY); // Enviar valor a la cola
        // sensor6_current_state = sensor_value6;
        vTaskDelay(10 / portTICK_PERIOD_MS); // Espera 1 segundo
        //}
    }
}