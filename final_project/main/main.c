#include <stdio.h>
#include "nvs_flash.h"
#include "wifi_app.h"
#include "sensor.h"
#include "uart.h"
#include "NTC.h"
#include "motor.h"

void app_main(void)
{
	thermistor_setup();
	// Initialize NVS
	uart_task_init();
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	// Start Wifi
	wifi_app_start();
	sensor_init();
	create_task();
	servo_init();
}