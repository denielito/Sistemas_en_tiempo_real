#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "driver/uart.h"
#include "freertos/queue.h"

#define TXD_PIN 17
#define RXD_PIN 16




extern QueueHandle_t uart_queue;

void uart_task_init(void);


#endif