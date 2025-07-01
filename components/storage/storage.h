#pragma once

#include <stdbool.h>
#include <stddef.h>

// Initialize the storage subsystem. Returns true on success.
bool storage_init(void);

// Save raw JSON data at the given path. Returns true on success.
bool storage_save(const char *path, const char *data, size_t len);

// Load raw JSON data from the given path. The buffer will be null terminated
// if there is space. Returns true on success.
bool storage_load(const char *path, char *buffer, size_t len);
