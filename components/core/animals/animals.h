#pragma once

#include <stdbool.h>
#include <stddef.h>

// Simple in-memory representation of an animal
typedef struct {
    char name[32];
    int age;
} animal_t;

// Initialize the internal list of animals
void animals_init(void);

// Create a new animal entry. Returns true on success.
bool animals_create(const animal_t *animal);

// Retrieve an animal by index. Returns NULL if index is out of range.
const animal_t *animals_get(size_t index);

// Update an existing animal entry. Returns true on success.
bool animals_update(size_t index, const animal_t *animal);

// Delete an animal entry by index. Returns true on success.
bool animals_delete(size_t index);

// Return the current number of stored animals.
size_t animals_get_count(void);

// Load animal data from /animals.json using the storage component.
// Returns true on success.
bool animals_load_from_json(void);
