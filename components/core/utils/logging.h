#pragma once

#include <stdarg.h>

// Simple logging helpers built on top of ESP-IDF's logging facilities

// Log an informational message using the given tag
void log_info(const char *tag, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

// Log an error message using the given tag
void log_error(const char *tag, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

// Log a warning message using the given tag
void log_warn(const char *tag, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

// Log a debug message using the given tag
void log_debug(const char *tag, const char *fmt, ...) __attribute__((format(printf, 2, 3)));

// Convenience macros mapping to the above helpers
#define LOG_WARN(tag, fmt, ...)  log_warn(tag, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(tag, fmt, ...) log_debug(tag, fmt, ##__VA_ARGS__)

