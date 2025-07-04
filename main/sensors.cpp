#include "sensors.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "bsp_i2c.h"
#include "htu21.h"
#include <stdio.h>

static const char *TAG = "Sensors";

sensor_data_t g_sensor_data = {0};

extern "C" void sensor_task(void *arg)
{
    (void)arg;

    // Initialize I2C bus and HTU21 sensor
    bsp_i2c_init(I2C_NUM_0, 400000);
    htu21_init();

    while (1) {
        g_sensor_data.temperature = htu21_get_temp();
        g_sensor_data.humidity = htu21_get_humid();
        ESP_LOGI(TAG, "Temp: %.2f C, Humidity: %.2f %%", g_sensor_data.temperature, g_sensor_data.humidity);
        FILE *f = fopen("/spiffs/sensor.log", "a");
        if (f) {
            fprintf(f, "%.2f,%.2f\n", g_sensor_data.temperature, g_sensor_data.humidity);
            fclose(f);
        } else {
            ESP_LOGE(TAG, "Failed to open log file");
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
