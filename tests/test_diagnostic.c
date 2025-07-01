#include "../components/agents/diagnostic/diagnostic.h"
#include "stubs/esp_log.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    unsetenv("LCD_FAIL");
    unsetenv("TOUCH_FAIL");
    diagnostic_run();
    assert(strstr(esp_log_last_buf, "complete") != NULL);

    setenv("LCD_FAIL", "1", 1);
    diagnostic_run();
    printf("log=%s\n", esp_log_last_buf);
    assert(strstr(esp_log_last_buf, "self-tests failed") != NULL);
    unsetenv("LCD_FAIL");

    setenv("TOUCH_FAIL", "1", 1);
    diagnostic_run();
    printf("log=%s\n", esp_log_last_buf);
    assert(strstr(esp_log_last_buf, "self-tests failed") != NULL);
    unsetenv("TOUCH_FAIL");

    printf("test_diagnostic: all tests passed\n");
    return 0;
}
