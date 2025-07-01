#include "lvgl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

lv_obj_t *lv_obj_create(lv_obj_t *parent) {
    lv_obj_t *obj = calloc(1, sizeof(lv_obj_t));
    obj->parent = parent;
    if (parent && parent->child_count < 16) {
        parent->children[parent->child_count++] = obj;
    }
    return obj;
}

lv_obj_t *lv_list_create(lv_obj_t *parent) {
    lv_obj_t *obj = lv_obj_create(parent);
    obj->type = 1;
    return obj;
}

lv_obj_t *lv_btn_create(lv_obj_t *parent) {
    lv_obj_t *obj = lv_obj_create(parent);
    obj->type = 2;
    return obj;
}

lv_obj_t *lv_label_create(lv_obj_t *parent) {
    lv_obj_t *obj = lv_obj_create(parent);
    obj->type = 3;
    return obj;
}

void lv_obj_set_size(lv_obj_t *obj, int w, int h) {
    (void)obj; (void)w; (void)h;
}

void lv_obj_clean(lv_obj_t *obj) {
    if (!obj) return;
    for (int i=0;i<obj->child_count;i++) free(obj->children[i]);
    obj->child_count = 0;
}

void lv_label_set_text_fmt(lv_obj_t *label, const char *fmt, ...) {
    va_list args; va_start(args, fmt);
    vsnprintf(label->text, sizeof(label->text), fmt, args);
    va_end(args);
}

void lv_obj_add_event_cb(lv_obj_t *obj, lv_event_cb_t cb) {
    obj->event_cb = cb;
}

void lv_event_send(lv_obj_t *obj) {
    if (obj && obj->event_cb) {
        lv_event_t e = { .target = obj };
        obj->event_cb(&e);
    }
}
