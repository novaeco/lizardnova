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
    if (obj) obj->event_cb = cb;
}

void lv_event_send(lv_obj_t *obj) {
    if (obj && obj->event_cb) {
        lv_event_t e = { .target = obj };
        obj->event_cb(&e);
    }
}

/* Additional stubs for the example project */

void lv_init(void) {
    /* Nothing to initialise in the stub */
}

lv_display_t *lv_display_create(int hor_res, int ver_res) {
    lv_display_t *d = calloc(1, sizeof(lv_display_t));
    if (d) {
        d->hor_res = hor_res;
        d->ver_res = ver_res;
    }
    return d;
}

void lv_display_set_buffers(lv_display_t *disp, lv_color_t *buf1, lv_color_t *buf2, size_t size, int render_mode) {
    (void)render_mode;
    if (disp) {
        disp->buf1 = buf1;
        disp->buf2 = buf2;
        disp->buf_size = size;
    }
}

void lv_display_set_flush_cb(lv_display_t *disp, void (*flush_cb)(lv_display_t *, const lv_area_t *, uint8_t *)) {
    if (disp) disp->flush_cb = flush_cb;
}

void lv_display_flush_ready(lv_display_t *disp) {
    (void)disp;
}

static lv_obj_t *s_active_screen = NULL;

lv_indev_t *lv_indev_create(void) {
    return calloc(1, sizeof(lv_indev_t));
}

void lv_indev_set_type(lv_indev_t *indev, int type) {
    if (indev) indev->type = type;
}

void lv_indev_set_read_cb(lv_indev_t *indev, void (*read_cb)(lv_indev_t *, lv_indev_data_t *)) {
    if (indev) indev->read_cb = read_cb;
}

void lv_scr_load(lv_obj_t *scr) {
    s_active_screen = scr;
    (void)s_active_screen;
}

void lv_timer_handler(void) {
    /* nothing */
}

