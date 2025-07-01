// LVGL screen for displaying a list of animals

#include "ui_animals.h"
#include "core/animals/animals.h"
#include <stdio.h>
#include <string.h>

static lv_obj_t *s_screen = NULL;
static lv_obj_t *s_list = NULL;
static lv_obj_t *s_add_btn = NULL;
static lv_obj_t *s_edit_btn = NULL;
static lv_obj_t *s_delete_btn = NULL;

static void on_add(lv_event_t *e)
{
    (void)e;
    animal_t a = {0};
    snprintf(a.name, sizeof(a.name), "Animal%zu", animals_get_count() + 1);
    animals_create(&a);
    ui_animals_refresh();
}

static void on_edit(lv_event_t *e)
{
    (void)e;
    if (animals_get_count() == 0) {
        return;
    }
    animal_t a = {0};
    strncpy(a.name, "Edited", sizeof(a.name) - 1);
    a.age = 99;
    animals_update(0, &a);
    ui_animals_refresh();
}

static void on_delete(lv_event_t *e)
{
    (void)e;
    if (animals_get_count() == 0) {
        return;
    }
    animals_delete(0);
    ui_animals_refresh();
}

// Populate the list widget with the current animals
void ui_animals_refresh(void)
{
    if (!s_list) {
        return;
    }

    lv_obj_clean(s_list);

    size_t count = animals_get_count();
    for (size_t i = 0; i < count; ++i) {
        const animal_t *a = animals_get(i);
        if (!a) {
            continue;
        }

        lv_obj_t *btn = lv_btn_create(s_list);
        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text_fmt(label, "%s (%d)", a->name, a->age);
    }
}

// Create the animal screen and initial list
lv_obj_t *ui_animals_create(void)
{
    if (s_screen) {
        return s_screen;
    }

    s_screen = lv_obj_create(NULL);
    s_list = lv_list_create(s_screen);
    lv_obj_set_size(s_list, lv_pct(100), lv_pct(100));

    s_add_btn = lv_btn_create(s_screen);
    lv_obj_add_event_cb(s_add_btn, on_add);
    lv_obj_t *add_label = lv_label_create(s_add_btn);
    lv_label_set_text_fmt(add_label, "Add");

    s_edit_btn = lv_btn_create(s_screen);
    lv_obj_add_event_cb(s_edit_btn, on_edit);
    lv_obj_t *edit_label = lv_label_create(s_edit_btn);
    lv_label_set_text_fmt(edit_label, "Edit");

    s_delete_btn = lv_btn_create(s_screen);
    lv_obj_add_event_cb(s_delete_btn, on_delete);
    lv_obj_t *delete_label = lv_label_create(s_delete_btn);
    lv_label_set_text_fmt(delete_label, "Delete");

    ui_animals_refresh();

    return s_screen;
}
