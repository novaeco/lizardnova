#include "../components/drivers/touch_gt911/gt911.h"
#include <stdlib.h>
#include <string.h>

bool gt911_self_test(void)
{
    const char *env = getenv("TOUCH_FAIL");
    return !(env && strcmp(env, "1") == 0);
}
