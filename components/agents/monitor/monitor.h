#pragma once

// Initialize monitoring subsystem
void monitor_init(void);

// Configure threshold values for temperature and humidity
void monitor_set_thresholds(int temp, int hum);

// Poll sensors and check thresholds (stubbed)
void monitor_poll(void);
