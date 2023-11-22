#ifndef BOTON_H
#define BOTON_H

#include "esp_err.h"
#include "driver/gpio.h"

esp_err_t init_boton(void);
void read_boton(void *pvParameters);

#endif