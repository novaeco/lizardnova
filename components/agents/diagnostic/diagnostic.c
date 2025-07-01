#include "diagnostic.h"
#include "core/utils/logging.h"
#include "drivers/lcd_st7262/lcd_st7262.h"
#include "drivers/touch_gt911/gt911.h"
#include <stdbool.h>

void diagnostic_run(void)
{
    log_info("DIAG", "running self-tests");

    bool failed = false;

    if (!gt911_self_test()) {
        log_error("DIAG", "touch test failed");
        failed = true;
    }

    if (!lcd_st7262_self_test()) {
        log_error("DIAG", "display test failed");
        failed = true;
    }

    if (failed) {
        log_error("DIAG", "self-tests failed");
    } else {
        log_info("DIAG", "self-tests complete");
    }
}
