#ifndef NTC_H
#define NTC_H

#include <stdio.h>
#include <math.h>
#include "driver/adc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define NtcPIN     ADC1_CHANNEL_6
#define RefVol     3.3
#define RDv        200
#define RNtc       50
#define Beta       4190
#define Temp0      298.15

#define ADC_WIDTH  ADC_WIDTH_BIT_12
#define ADC_ATTEN  ADC_ATTEN_DB_11
#define DELAY_MS   1000

extern QueueHandle_t temp_queue;

// Prototipos de funciones
void thermistor_setup();
float thermistor_get_temperature();
float calculate_temperature_kelvin(float Rntc);
float convert_kelvin_to_celsius(float Temperatura_Kelvin);
void thermistor_task(void *pvParameters);


#endif