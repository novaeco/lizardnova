// Simple filesystem-backed implementation of JSON storage helpers

#include "storage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Base directory used as the mounted filesystem path. By default this
// resolves to "data" but can be overridden at runtime via the
// STORAGE_BASE_PATH environment variable which is useful for tests.
static char s_mount_path[256] = "data";
static bool s_initialised = false;

// Ensure the mount directory exists
static bool ensure_dir(const char *path)
{
    struct stat st;
    if (stat(path, &st) == 0) {
        return S_ISDIR(st.st_mode);
    }
    if (mkdir(path, 0755) != 0) {
        return false;
    }
    return true;
}

// Mount the filesystem. For the host build this simply verifies that the
// directory exists so standard C file APIs can be used.
bool storage_init(void)
{
    const char *env = getenv("STORAGE_BASE_PATH");
    if (env && env[0] != '\0') {
        strncpy(s_mount_path, env, sizeof(s_mount_path) - 1);
        s_mount_path[sizeof(s_mount_path) - 1] = '\0';
    }

    if (!ensure_dir(s_mount_path)) {
        return false;
    }

    s_initialised = true;
    return true;
}

// Save raw data to a file within the mounted directory
bool storage_save(const char *path, const char *data, size_t len)
{
    if (!s_initialised || !path || !data) {
        return false;
    }

    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s%s", s_mount_path, path);

    FILE *f = fopen(full_path, "wb");
    if (!f) {
        return false;
    }

    size_t written = fwrite(data, 1, len, f);
    fclose(f);

    return written == len;
}

// Load data from a file within the mounted directory
bool storage_load(const char *path, char *buffer, size_t len)
{
    if (!s_initialised || !path || !buffer || len == 0) {
        return false;
    }

    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s%s", s_mount_path, path);

    FILE *f = fopen(full_path, "rb");
    if (!f) {
        return false;
    }

    size_t read = fread(buffer, 1, len - 1, f);
    fclose(f);
    buffer[read] = '\0';

    return true;
}

