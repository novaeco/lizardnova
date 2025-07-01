#pragma once

#include <stdarg.h>

// Simple logging helpers built on top of ESP-IDF's logging facilities

// Log an informational message using the given tag
void log_info(const char *tag, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

// Log an error message using the given tag
void log_error(const char *tag, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

