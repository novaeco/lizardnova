#include "../components/core/animals/animals.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    animals_init();
    assert(animals_get_count() == 0);

    animal_t a;
    memset(&a, 0, sizeof(a));
    strcpy(a.name, "Gecko");
    a.age = 2;
    assert(animals_create(&a));
    assert(animals_get_count() == 1);

    const animal_t *pa = animals_get(0);
    assert(pa);
    assert(strcmp(pa->name, "Gecko") == 0);
    assert(pa->age == 2);

    animal_t b;
    memset(&b, 0, sizeof(b));
    strcpy(b.name, "Lizard");
    b.age = 3;
    assert(animals_update(0, &b));

    pa = animals_get(0);
    assert(pa);
    assert(strcmp(pa->name, "Lizard") == 0);
    assert(pa->age == 3);

    assert(animals_delete(0));
    assert(animals_get_count() == 0);

    printf("test_animals: all tests passed\n");
    return 0;
}
