#ifndef MOTOR_H
#define MOTOR_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "esp_err.h"
#include "sensor.h"

// Configuración del pin del servo
#define SERVO_GPIO_PIN GPIO_NUM_18


// Configuración del canal PWM para el servo
#define SERVO_PWM_CHANNEL LEDC_CHANNEL_0
#define SERVO_PWM_TIMER LEDC_TIMER_0
#define SERVO_PWM_FREQ 50 // Frecuencia del PWM en Hz, típicamente 50 Hz para servos



void servo_init();
void set_servo_position(int position);
void servo_task(void *pvParameters);


#endif