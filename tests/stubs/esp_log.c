#include "esp_log.h"
#include <stdio.h>

char esp_log_last_buf[256];

void esp_log_writev(esp_log_level_t level, const char *tag, const char *fmt, va_list args)
{
    (void)level;
    (void)tag;
    vsnprintf(esp_log_last_buf, sizeof(esp_log_last_buf), fmt, args);
}
