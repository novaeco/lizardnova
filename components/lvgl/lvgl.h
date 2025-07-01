#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/* Minimal LVGL stubs sufficient for building the example project */

typedef struct lv_obj_s {
    int type;
    char text[64];
    struct lv_obj_s *parent;
    struct lv_obj_s *children[16];
    int child_count;
} lv_obj_t;

typedef struct {
    int x1, y1, x2, y2;
} lv_area_t;

typedef struct lv_display_s lv_display_t;

typedef uint16_t lv_color_t;

struct lv_display_s {
    int hor_res;
    int ver_res;
    lv_color_t *buf1;
    lv_color_t *buf2;
    size_t buf_size;
    void (*flush_cb)(lv_display_t *, const lv_area_t *, uint8_t *);
};

typedef struct lv_indev_s lv_indev_t;

typedef struct {
    struct { int16_t x; int16_t y; } point;
    int state;
} lv_indev_data_t;

struct lv_indev_s {
    int type;
    void (*read_cb)(lv_indev_t *, lv_indev_data_t *);
};

/* Constants */
#define LV_INDEV_TYPE_POINTER 1
#define LV_INDEV_STATE_REL 0
#define LV_INDEV_STATE_PR 1
#define LV_DISPLAY_RENDER_MODE_PARTIAL 0

/* Basic object helpers */
lv_obj_t *lv_obj_create(lv_obj_t *parent);
lv_obj_t *lv_list_create(lv_obj_t *parent);
lv_obj_t *lv_btn_create(lv_obj_t *parent);
lv_obj_t *lv_label_create(lv_obj_t *parent);
void lv_obj_set_size(lv_obj_t *obj, int w, int h);
void lv_obj_clean(lv_obj_t *obj);
void lv_label_set_text_fmt(lv_obj_t *label, const char *fmt, ...);

/* Display interface */
void lv_init(void);
lv_display_t *lv_display_create(int hor_res, int ver_res);
void lv_display_set_buffers(lv_display_t *disp, lv_color_t *buf1, lv_color_t *buf2, size_t size, int render_mode);
void lv_display_set_flush_cb(lv_display_t *disp, void (*flush_cb)(lv_display_t *, const lv_area_t *, uint8_t *));
void lv_display_flush_ready(lv_display_t *disp);

/* Input device */
lv_indev_t *lv_indev_create(void);
void lv_indev_set_type(lv_indev_t *indev, int type);
void lv_indev_set_read_cb(lv_indev_t *indev, void (*read_cb)(lv_indev_t *, lv_indev_data_t *));

/* Misc helpers */
void lv_scr_load(lv_obj_t *scr);
void lv_timer_handler(void);
