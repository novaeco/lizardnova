#pragma once
#include <stdarg.h>

#define ESP_LOG_INFO 0
#define ESP_LOG_ERROR 1

typedef int esp_log_level_t;

void esp_log_writev(esp_log_level_t level, const char *tag, const char *fmt, va_list args);
extern char esp_log_last_buf[256];
