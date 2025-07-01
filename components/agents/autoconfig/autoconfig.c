#include "autoconfig.h"
#include "core/utils/logging.h"
#include "storage/storage.h"
#include <string.h>

void autoconfig_verify(void)
{
    log_info("AUTOCONFIG", "verifying configuration");
    char buf[8];
    if (storage_load("/config.json", buf, sizeof(buf))) {
        log_info("AUTOCONFIG", "config present");
    } else {
        log_error("AUTOCONFIG", "config missing");
    }
}
