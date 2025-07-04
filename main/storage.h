#pragma once
#include "esp_err.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int32_t target_temp;      // Celsius
    int32_t target_humidity;  // Percent
} habitat_config_t;

extern habitat_config_t g_habitat_config;
esp_err_t load_config();
esp_err_t save_config();

#ifdef __cplusplus
}
#endif
