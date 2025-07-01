#pragma once

#include "lvgl.h"

// Create and return the animals screen object
lv_obj_t *ui_animals_create(void);

// Refresh the animal list to reflect current data
void ui_animals_refresh(void);
