#include "sensors.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include <stdio.h>

static const char *TAG = "Sensors";

sensor_data_t g_sensor_data = {0};

static float read_temperature()
{
    return 20.0f + (float)(esp_random() % 1000) / 100.0f;
}

static float read_humidity()
{
    return 40.0f + (float)(esp_random() % 600) / 10.0f;
}

extern "C" void sensor_task(void *arg)
{
    (void)arg;
    while (1) {
        g_sensor_data.temperature = read_temperature();
        g_sensor_data.humidity = read_humidity();
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
