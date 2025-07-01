#include "../components/core/ui/ui_animals.h"
#include "../components/core/animals/animals.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Include stubs
#include "stubs/lvgl.h"

int main(void)
{
    animals_init();
    animal_t a = {"Gecko", 2};
    animals_create(&a);
    animal_t b = {"Snake", 4};
    animals_create(&b);

    lv_obj_t *screen = ui_animals_create();
    assert(screen);
    ui_animals_refresh();

    // screen has list and three control buttons
    assert(screen->child_count == 4);
    lv_obj_t *list = screen->children[0];
    lv_obj_t *btn_add = screen->children[1];
    lv_obj_t *btn_edit = screen->children[2];
    lv_obj_t *btn_del = screen->children[3];
    assert(list->child_count == 2);

    // verify button labels
    assert(strcmp(btn_add->children[0]->text, "Add") == 0);
    assert(strcmp(btn_edit->children[0]->text, "Edit") == 0);
    assert(strcmp(btn_del->children[0]->text, "Delete") == 0);

    // verify initial list items
    for (int i=0;i<2;i++) {
        lv_obj_t *btn = list->children[i];
        assert(btn->child_count == 1);
        lv_obj_t *label = btn->children[0];
        if (i==0) {
            assert(strcmp(label->text, "Gecko (2)") == 0);
        } else {
            assert(strcmp(label->text, "Snake (4)") == 0);
        }
    }

    // trigger Add button
    lv_event_send(btn_add);
    assert(animals_get_count() == 3);
    assert(list->child_count == 3);
    lv_obj_t *new_btn = list->children[2];
    assert(strcmp(new_btn->children[0]->text, "Animal3 (0)") == 0);

    // trigger Edit button
    lv_event_send(btn_edit);
    assert(strcmp(list->children[0]->children[0]->text, "Edited (99)") == 0);

    // trigger Delete button
    lv_event_send(btn_del);
    assert(animals_get_count() == 2);
    assert(list->child_count == 2);
    assert(strcmp(list->children[0]->children[0]->text, "Snake (4)") == 0);

    printf("test_ui: all tests passed\n");
    return 0;
}
