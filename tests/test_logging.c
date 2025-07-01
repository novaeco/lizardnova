#include "../components/core/utils/logging.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "stubs/esp_log.h"

int main(void)
{
    log_info("TEST", "num=%d", 5);
    assert(strcmp(esp_log_last_buf, "num=5") == 0);

    log_error("TEST", "str %s %d", "hi", 3);
    assert(strcmp(esp_log_last_buf, "str hi 3") == 0);

    printf("test_logging: all tests passed\n");
    return 0;
}
