#include "monitor.h"
#include "core/utils/logging.h"

#ifndef CONFIG_MONITOR_TEMP_THRESHOLD
#define CONFIG_MONITOR_TEMP_THRESHOLD 30
#endif

#ifndef CONFIG_MONITOR_HUM_THRESHOLD
#define CONFIG_MONITOR_HUM_THRESHOLD 80
#endif

static int s_temp = 25;
static int s_hum  = 50;
static int s_temp_threshold = CONFIG_MONITOR_TEMP_THRESHOLD;
static int s_hum_threshold  = CONFIG_MONITOR_HUM_THRESHOLD;

void monitor_init(void)
{
    log_info("MON", "monitor init");
}

void monitor_set_thresholds(int temp, int hum)
{
    s_temp_threshold = temp;
    s_hum_threshold = hum;
}

void monitor_poll(void)
{
    // Stubbed sensor read
    log_info("MON", "temp=%d humidity=%d", s_temp, s_hum);
    if (s_temp > s_temp_threshold || s_hum > s_hum_threshold) {
        log_error("MON", "threshold exceeded");
    }
}
