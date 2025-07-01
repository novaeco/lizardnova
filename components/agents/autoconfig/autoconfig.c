#include "autoconfig.h"
#include "core/utils/logging.h"
#include "storage/storage.h"
#include <string.h>
#include "cJSON.h"

void autoconfig_verify(void)
{
    log_info("AUTOCONFIG", "verifying configuration");
    char buf[256];
    if (!storage_load("/config.json", buf, sizeof(buf))) {
        const char *def = "{\"device_name\":\"ESP32\",\"version\":1}";
        if (storage_save("/config.json", def, strlen(def))) {
            strncpy(buf, def, sizeof(buf) - 1);
            buf[sizeof(buf) - 1] = '\0';
            log_warn("AUTOCONFIG", "default config created");
        } else {
            log_error("AUTOCONFIG", "failed to create config");
            return;
        }
    } else {
        log_info("AUTOCONFIG", "config present");
    }

    cJSON *root = cJSON_Parse(buf);
    if (!root || !cJSON_IsObject(root)) {
        log_error("AUTOCONFIG", "config parse error");
        cJSON_Delete(root);
        return;
    }
    cJSON *name = cJSON_GetObjectItem(root, "device_name");
    cJSON *ver = cJSON_GetObjectItem(root, "version");
    if (!cJSON_IsString(name) || !cJSON_IsNumber(ver)) {
        log_error("AUTOCONFIG", "invalid config");
    } else {
        log_info("AUTOCONFIG", "config valid");
    }
    cJSON_Delete(root);
}
