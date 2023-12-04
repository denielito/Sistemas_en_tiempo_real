#include "NTC.h"

QueueHandle_t temp_queue;

void thermistor_setup() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(NtcPIN, ADC_ATTEN_DB_11);

    // Otras configuraciones según sea necesario

    static uint8_t ucparameterToPass;
    TaskHandle_t xHandle = NULL;

    temp_queue = xQueueCreate(5, sizeof(float));

    xTaskCreate(thermistor_task, "thermistor_task", 2048, &ucparameterToPass, 2, &xHandle);
}

float thermistor_get_temperature() {
    int adc_val = adc1_get_raw(NtcPIN);
    float adc_value = (float)adc_val;

    float VNtc = (RefVol * adc_value) / 4095;
    float Rntc = RDv / ((RefVol / VNtc) - 1);

    float Temperatura_Kelvin = calculate_temperature_kelvin(Rntc);
    float Temperatura_Celsius = convert_kelvin_to_celsius(Temperatura_Kelvin);

    return Temperatura_Celsius;
}

float calculate_temperature_kelvin(float Rntc) {
    return Beta / (log(Rntc / RNtc) + (Beta / Temp0));
}

float convert_kelvin_to_celsius(float Temperatura_Kelvin) {
    return Temperatura_Kelvin - 273.15;
}

void thermistor_task(void *pvParameters) {
    while (1) {
        float temperature = thermistor_get_temperature();
        xQueueSend(temp_queue, &temperature, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
    }
}
