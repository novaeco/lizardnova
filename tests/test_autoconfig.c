#include "../components/agents/autoconfig/autoconfig.h"
#include "../components/storage/storage.h"
#include "stubs/esp_log.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char dir_template[] = "/tmp/autoconfXXXXXX";
    char *tmpdir = mkdtemp(dir_template);
    assert(tmpdir);
    setenv("STORAGE_BASE_PATH", tmpdir, 1);
    assert(storage_init());

    /* missing file triggers default creation */
    autoconfig_verify();
    assert(strstr(esp_log_last_buf, "valid") != NULL);
    char path[512];
    snprintf(path, sizeof(path), "%s/config.json", tmpdir);
    FILE *f = fopen(path, "r");
    assert(f); fclose(f);

    /* invalid content */
    f = fopen(path, "w");
    assert(f); fputs("{\"bad\":1}", f); fclose(f);
    autoconfig_verify();
    assert(strstr(esp_log_last_buf, "invalid") != NULL);

    unlink(path);
    rmdir(tmpdir);
    printf("test_autoconfig: all tests passed\n");
    return 0;
}
