#include "monitor.h"
#include "core/utils/logging.h"

#define TEMP_THRESHOLD 30
#define HUM_THRESHOLD 80

static int s_temp = 25;
static int s_hum  = 50;

void monitor_init(void)
{
    log_info("MON", "monitor init");
}

void monitor_poll(void)
{
    // Stubbed sensor read
    log_info("MON", "temp=%d humidity=%d", s_temp, s_hum);
    if (s_temp > TEMP_THRESHOLD || s_hum > HUM_THRESHOLD) {
        log_error("MON", "threshold exceeded");
    }
}
