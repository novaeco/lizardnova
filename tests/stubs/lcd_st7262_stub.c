#include "../components/drivers/lcd_st7262/lcd_st7262.h"
#include <stdlib.h>
#include <string.h>

bool lcd_st7262_self_test(void)
{
    const char *env = getenv("LCD_FAIL");
    return !(env && strcmp(env, "1") == 0);
}
