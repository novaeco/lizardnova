#pragma once
typedef int gpio_num_t;
#define GPIO_PULLUP_ENABLE 0
#define GPIO_MODE_OUTPUT 0
typedef struct {int mode; unsigned long long pin_bit_mask;} gpio_config_t;
static inline int gpio_config(const gpio_config_t *cfg) { return 0; }
static inline int gpio_set_level(gpio_num_t num, int level) { return 0; }
