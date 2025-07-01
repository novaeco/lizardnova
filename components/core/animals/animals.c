// Simple in-memory CRUD implementation for animal entries

#include "animals.h"
#include "storage/storage.h"
#include "core/utils/logging.h"
#include <string.h>
#include "cJSON.h"

#define MAX_ANIMALS 10

static animal_t s_animals[MAX_ANIMALS];
static size_t s_count = 0;

void animals_init(void)
{
    s_count = 0;
    memset(s_animals, 0, sizeof(s_animals));
}

bool animals_create(const animal_t *animal)
{
    if (!animal || s_count >= MAX_ANIMALS) {
        return false;
    }
    s_animals[s_count] = *animal;
    s_count++;
    return true;
}

const animal_t *animals_get(size_t index)
{
    if (index >= s_count) {
        return NULL;
    }
    return &s_animals[index];
}

bool animals_update(size_t index, const animal_t *animal)
{
    if (!animal || index >= s_count) {
        return false;
    }
    s_animals[index] = *animal;
    return true;
}

bool animals_delete(size_t index)
{
    if (index >= s_count) {
        return false;
    }

    for (size_t i = index; i + 1 < s_count; ++i) {
        s_animals[i] = s_animals[i + 1];
    }

    memset(&s_animals[s_count - 1], 0, sizeof(animal_t));
    s_count--;
    return true;
}

size_t animals_get_count(void)
{
    return s_count;
}

bool animals_load_from_json(void)
{
    char buffer[1024];
    if (!storage_load("/animals.json", buffer, sizeof(buffer))) {
        log_error("ANIMALS", "failed to load /animals.json");
        return false;
    }

    cJSON *root = cJSON_Parse(buffer);
    if (!root || !cJSON_IsArray(root)) {
        log_error("ANIMALS", "invalid JSON format");
        cJSON_Delete(root);
        return false;
    }

    animals_init();

    size_t count = 0;
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, root) {
        if (count >= MAX_ANIMALS) {
            break;
        }
        if (!cJSON_IsObject(item)) {
            continue;
        }

        cJSON *name = cJSON_GetObjectItem(item, "name");
        cJSON *age = cJSON_GetObjectItem(item, "age");
        if (!cJSON_IsString(name)) {
            continue;
        }

        animal_t a;
        memset(&a, 0, sizeof(a));
        strncpy(a.name, name->valuestring, sizeof(a.name) - 1);
        if (cJSON_IsNumber(age)) {
            a.age = age->valueint;
        }
        animals_create(&a);
        count++;
    }

    cJSON_Delete(root);
    return true;
}

