#include "../components/agents/monitor/monitor.h"
#include "../components/agents/autoconfig/autoconfig.h"
#include "../components/agents/diagnostic/diagnostic.h"
#include "../components/agents/assistant/assistant.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "stubs/esp_log.h"

int main(void)
{
    monitor_init();
    assert(strcmp(esp_log_last_buf, "monitor init") == 0);

    monitor_poll();
    assert(strstr(esp_log_last_buf, "humidity") != NULL);

    monitor_set_thresholds(20, 40);
    monitor_poll();
    assert(strstr(esp_log_last_buf, "threshold exceeded") != NULL);

    autoconfig_verify();
    assert(strstr(esp_log_last_buf, "config") != NULL);

    diagnostic_run();
    assert(strstr(esp_log_last_buf, "self-tests complete") != NULL);

    assistant_show_help();
    assert(strstr(esp_log_last_buf, "help") != NULL);

    printf("test_agents: all tests passed\n");
    return 0;
}
