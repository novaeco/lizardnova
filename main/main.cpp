#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_port_tick.h"
#include "lv_port_fs.h"

#include "sensors.h"
#include "ui.h"
#include "storage.h"

static const char *TAG = "MainApp";

// LVGL tick task
void lv_tick_task(void *arg)
{
    while(1) 
    {
        vTaskDelay(pdMS_TO_TICKS(10));
        lv_task_handler();        
    }
}

extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "Booting Reptile-Manager-Pro...");

    // Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize LVGL and its drivers
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    lv_port_fs_init();
    lv_port_tick_init();

    ESP_LOGI(TAG, "LVGL initialization complete.");

    // Load saved configuration
    load_config();

    // Initialize UI
    ui_init();

    // Create tasks
    xTaskCreate(lv_tick_task, "lv_tick_task", 4096 * 2, NULL, 1, NULL);
    xTaskCreate(sensor_task, "sensor_task", 4096, NULL, 5, NULL);
    xTaskCreate(ui_update_task, "ui_update_task", 4096, NULL, 4, NULL);

    ESP_LOGI(TAG, "Reptile-Manager-Pro started successfully.");
}

