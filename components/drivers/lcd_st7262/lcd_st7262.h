#pragma once

// Basic driver for an LCD panel using the ST7262 controller.
//
// Wiring requirements
// -------------------
// - SPI MOSI must be connected to the panel's SDI pin.
// - SPI CLK  must be connected to the SCL pin.
// - The CS pin should be driven low for the duration of a transfer.
// - DC toggles between command (low) and data (high) bytes.
// - A reset line should be asserted low for a few milliseconds during
//   startup.
//
// Pin numbers can be configured via menuconfig under the "ST7262 LCD"
// submenu.

#include "lvgl.h"

// Initialize the ST7262 display and register it with LVGL.
void lcd_st7262_init(void);

