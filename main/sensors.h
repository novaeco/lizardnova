#pragma once
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float temperature;
    float humidity;
} sensor_data_t;

extern sensor_data_t g_sensor_data;
void sensor_task(void *arg);

#ifdef __cplusplus
}
#endif
