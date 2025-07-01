#pragma once
#include <stdarg.h>

struct lv_event_s;
typedef struct lv_event_s lv_event_t;
typedef struct lv_obj_s {
    int type;
    char text[64];
    struct lv_obj_s *parent;
    struct lv_obj_s *children[16];
    int child_count;
    void (*event_cb)(lv_event_t *);
} lv_obj_t;

struct lv_event_s {
    lv_obj_t *target;
};

typedef void (*lv_event_cb_t)(lv_event_t *);

static inline int lv_pct(int v) { return v; }

lv_obj_t *lv_obj_create(lv_obj_t *parent);
lv_obj_t *lv_list_create(lv_obj_t *parent);
lv_obj_t *lv_btn_create(lv_obj_t *parent);
lv_obj_t *lv_label_create(lv_obj_t *parent);
void lv_obj_set_size(lv_obj_t *obj, int w, int h);
void lv_obj_clean(lv_obj_t *obj);
void lv_label_set_text_fmt(lv_obj_t *label, const char *fmt, ...);
void lv_obj_add_event_cb(lv_obj_t *obj, lv_event_cb_t cb);
void lv_event_send(lv_obj_t *obj);
