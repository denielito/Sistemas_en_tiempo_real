#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include "motor.h"

#define STACK_SIZE 1024 * 2

// Definición de funciones
esp_err_t sensor_init(void);
esp_err_t create_task(void);
void state_a1(void *pvParameters);
void state_a3(void *pvParameters);
void state_b2(void *pvParameters);
void state_b4(void *pvParameters);
void state_IN(void *pvParameters);
void state_OUT(void *pvParameters);

typedef struct {
    int sensor_1;
    int sensor_2;
    int sensor_3;
    int sensor_4;
} SensorData;

// Colas para almacenar valores de sensores
extern QueueHandle_t sensor1_queue;
extern QueueHandle_t sensor2_queue;
extern QueueHandle_t sensor3_queue;
extern QueueHandle_t sensor4_queue;
extern QueueHandle_t sensor5_queue;
extern QueueHandle_t sensor6_queue;

// Definición de pines de sensores
#define IR_SENSOR1_PIN GPIO_NUM_4
#define IR_SENSOR2_PIN GPIO_NUM_16
#define IR_SENSOR3_PIN GPIO_NUM_17
#define IR_SENSOR4_PIN GPIO_NUM_5
#define IR_SENSOR5_PIN 27
#define IR_SENSOR6_PIN 26

#endif /* SENSOR_H */
