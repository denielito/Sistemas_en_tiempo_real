// uart_task.c

#include "uart.h"
#include "driver/uart.h"

#define BUF_SIZE (1024)

QueueHandle_t uart_queue;

void uart_task(void *pvParameter) {
    uint8_t data[BUF_SIZE];

    while (1) {
        if (xQueueReceive(uart_queue, data, portMAX_DELAY)) {
            // Configura la UART según tus necesidades
            uart_config_t uart_config = {
                .baud_rate = 115200,
                .data_bits = UART_DATA_8_BITS,
                .parity    = UART_PARITY_DISABLE,
                .stop_bits = UART_STOP_BITS_1,
                .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
            };

            uart_param_config(UART_NUM_1, &uart_config);
            uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
            uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);

            // Envía los datos por UART
            uart_write_bytes(UART_NUM_1, (const char *)data, strlen((const char *)data));
        }
    }
}

void uart_task_init(void) {
    // Crea la cola para la comunicación entre tareas
    uart_queue = xQueueCreate(10, BUF_SIZE);

    // Crea y lanza la tarea UART
    xTaskCreate(uart_task, "uart_task", 2048, NULL, 10, NULL);
}
