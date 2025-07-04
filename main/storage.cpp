#include "storage.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_log.h"

static const char *TAG = "Storage";

habitat_config_t g_habitat_config = {30, 50};

esp_err_t load_config()
{
    nvs_handle_t handle;
    esp_err_t err = nvs_open("habitat", NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open NVS (%s)", esp_err_to_name(err));
        return err;
    }
    int32_t temp = g_habitat_config.target_temp;
    int32_t hum = g_habitat_config.target_humidity;
    nvs_get_i32(handle, "temp", &temp);
    nvs_get_i32(handle, "hum", &hum);
    g_habitat_config.target_temp = temp;
    g_habitat_config.target_humidity = hum;
    nvs_close(handle);
    return ESP_OK;
}

esp_err_t save_config()
{
    nvs_handle_t handle;
    esp_err_t err = nvs_open("habitat", NVS_READWRITE, &handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open NVS (%s)", esp_err_to_name(err));
        return err;
    }
    nvs_set_i32(handle, "temp", g_habitat_config.target_temp);
    nvs_set_i32(handle, "hum", g_habitat_config.target_humidity);
    err = nvs_commit(handle);
    nvs_close(handle);
    return err;
}
