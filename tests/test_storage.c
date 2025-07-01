#include "../components/storage/storage.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void prepare_animals_json(const char *dir)
{
    char path[512];
    snprintf(path, sizeof(path), "%s/animals.json", dir);
    FILE *f = fopen(path, "w");
    assert(f);
    fputs("[]", f);
    fclose(f);
}

static void verify_file_contents(const char *path, const char *expected)
{
    FILE *f = fopen(path, "r");
    assert(f);
    char buf[16];
    size_t n = fread(buf, 1, sizeof(buf) - 1, f);
    fclose(f);
    buf[n] = '\0';
    assert(strcmp(buf, expected) == 0);
}

int main(void)
{
    char tmp_template[] = "/tmp/storageXXXXXX";
    char *tmpdir = mkdtemp(tmp_template);
    assert(tmpdir);

    setenv("STORAGE_BASE_PATH", tmpdir, 1);

    assert(storage_init());

    prepare_animals_json(tmpdir);

    char buffer[16];
    memset(buffer, 0, sizeof(buffer));
    assert(storage_load("/animals.json", buffer, sizeof(buffer)));
    assert(strcmp(buffer, "[]") == 0);

    assert(storage_save("/animals.json", "{}", 2));

    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s/animals.json", tmpdir);
    verify_file_contents(full_path, "{}");

    unlink(full_path);
    rmdir(tmpdir);

    printf("test_storage: all tests passed\n");
    return 0;
}
