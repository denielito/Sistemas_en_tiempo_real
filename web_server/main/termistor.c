#include "termistor.h"
#include "led.h"
#include <stdio.h>
#include <math.h>
#include "driver/adc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define NtcPIN     ADC1_CHANNEL_6  // Cambia el canal del ADC según tu configuración
#define RefVol     3.3             // Tensión de referencia del ADC
#define RDv        100         // Resistencia de referencia
#define RNtc       47         // Resistencia nominal del termistor a una temperatura de referencia
#define Beta       3950.0          // Coeficiente Beta del termistor
#define Temp0      298.15          // Temperatura de referencia en Kelvin


esp_err_t thermistor_setup() {
    adc1_config_channel_atten(NtcPIN, ADC_ATTEN_DB_11);
    adc1_config_width(ADC_WIDTH_BIT_12);
    return ESP_OK;
}

float thermistor_get_temperature() {
    int adc_val = adc1_get_raw(NtcPIN);
    float adc_value = (float)adc_val;
    float VNtc = (RefVol * adc_value) / 4095;
    float Rntc = RDv / ((RefVol / VNtc) - 1);
    float Temperatura_Kelvin = Beta / (log(Rntc / RNtc) + (Beta / Temp0));
    float Temperatura_Celsius = Temperatura_Kelvin - 273.15;
    return Temperatura_Celsius;
}

void thermistor_task(void *pvParameters) {
        float temperature = thermistor_get_temperature();

        if (temperature < 15) {
            set_color(0,0,1);
            vTaskDelay(100);
        } else if (temperature >= 15 && temperature < 30) {
            set_color(0,1,0);
            vTaskDelay(100);
        } else {
            set_color(1,0,0);
            vTaskDelay(100);
        }
        vTaskDelay(500);
    /* printf("temperatura: %f", temperature); */
}