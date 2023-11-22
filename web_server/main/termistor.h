#ifndef TERMISTOR_H
#define TERMISTOR_H

#include "esp_err.h"

esp_err_t thermistor_setup();
float thermistor_get_temperature();
void thermistor_task(void *pvParameters);

#endif
