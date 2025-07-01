#pragma once

// Simple GT911 touch controller driver API

#include "lvgl.h"
#include "driver/i2c.h"
#include "driver/gpio.h"

// Configure the I2C port used by the driver
void gt911_set_i2c_port(i2c_port_t port);

// Configure the I2C SDA/SCL pins
void gt911_set_i2c_pins(gpio_num_t sda, gpio_num_t scl);

// Set the I2C address (default 0x5D)
void gt911_set_i2c_addr(uint8_t addr);

// Set rotation (0-3) to adjust coordinates
void gt911_set_rotation(uint8_t rotation);

// Initialise the controller
void gt911_init(void);

// LVGL input device read callback
void gt911_read(lv_indev_t *indev, lv_indev_data_t *data);

