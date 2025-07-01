#include "../components/core/animals/animals.h"
#include "../components/storage/storage.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char tmp_template[] = "/tmp/animalsXXXXXX";
    char *tmpdir = mkdtemp(tmp_template);
    assert(tmpdir);

    char json_path[512];
    snprintf(json_path, sizeof(json_path), "%s/animals.json", tmpdir);
    FILE *f = fopen(json_path, "w");
    assert(f);
    fputs("[{\"name\":\"Tim\",\"age\":5},{\"name\":\"Lily\",\"age\":2}]", f);
    fclose(f);

    setenv("STORAGE_BASE_PATH", tmpdir, 1);
    assert(storage_init());

    animals_init();
    assert(animals_load_from_json());
    assert(animals_get_count() == 2);

    const animal_t *a = animals_get(0);
    assert(a && strcmp(a->name, "Tim") == 0 && a->age == 5);

    a = animals_get(1);
    assert(a && strcmp(a->name, "Lily") == 0 && a->age == 2);

    unlink(json_path);
    rmdir(tmpdir);

    printf("test_animals_load: all tests passed\n");
    return 0;
}
