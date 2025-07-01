#include "../components/core/animals/animals.h"
#include "../components/storage/storage.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void copy_animals_json(const char *dst_dir)
{
    char src_path[512];
    snprintf(src_path, sizeof(src_path), "../data/animals.json");
    FILE *src = fopen(src_path, "rb");
    assert(src);

    char dst_path[512];
    snprintf(dst_path, sizeof(dst_path), "%s/animals.json", dst_dir);
    FILE *dst = fopen(dst_path, "wb");
    assert(dst);

    char buf[128];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), src)) > 0) {
        fwrite(buf, 1, n, dst);
    }

    fclose(src);
    fclose(dst);
}

int main(void)
{
    char tmp_template[] = "/tmp/animalsXXXXXX";
    char *tmpdir = mkdtemp(tmp_template);
    assert(tmpdir);

    copy_animals_json(tmpdir);
    setenv("STORAGE_BASE_PATH", tmpdir, 1);
    assert(storage_init());

    animals_init();
    assert(animals_load_from_json());
    assert(animals_get_count() == 3);

    const animal_t *a = animals_get(0);
    assert(a && strcmp(a->name, "Leo") == 0 && a->age == 4);

    a = animals_get(1);
    assert(a && strcmp(a->name, "Shelly") == 0 && a->age == 10);

    a = animals_get(2);
    assert(a && strcmp(a->name, "Fang") == 0 && a->age == 1);

    char dst_path[512];
    snprintf(dst_path, sizeof(dst_path), "%s/animals.json", tmpdir);
    unlink(dst_path);
    rmdir(tmpdir);

    printf("test_animals_load: all tests passed\n");
    return 0;
}
