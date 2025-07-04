#include "ui.h"
#include "lvgl.h"
#include "sensors.h"
#include "storage.h"
#include "esp_log.h"

static const char *TAG = "UI";

static lv_obj_t *label_temp;
static lv_obj_t *label_hum;
static lv_obj_t *slider_temp;
static lv_obj_t *slider_hum;

static void slider_temp_event_cb(lv_event_t * e)
{
    g_habitat_config.target_temp = lv_slider_get_value(slider_temp);
    save_config();
}

static void slider_hum_event_cb(lv_event_t * e)
{
    g_habitat_config.target_humidity = lv_slider_get_value(slider_hum);
    save_config();
}

void ui_init(void)
{
    lv_obj_t *scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x003a57), LV_PART_MAIN);

    label_temp = lv_label_create(scr);
    lv_obj_align(label_temp, LV_ALIGN_TOP_MID, 0, 20);

    label_hum = lv_label_create(scr);
    lv_obj_align(label_hum, LV_ALIGN_TOP_MID, 0, 60);

    slider_temp = lv_slider_create(scr);
    lv_obj_set_width(slider_temp, 200);
    lv_slider_set_range(slider_temp, 0, 50); // Celsius
    lv_obj_align(slider_temp, LV_ALIGN_CENTER, 0, -40);
    lv_obj_add_event_cb(slider_temp, slider_temp_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_slider_set_value(slider_temp, g_habitat_config.target_temp, LV_ANIM_OFF);

    slider_hum = lv_slider_create(scr);
    lv_obj_set_width(slider_hum, 200);
    lv_slider_set_range(slider_hum, 0, 100); // Percent
    lv_obj_align(slider_hum, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_event_cb(slider_hum, slider_hum_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_slider_set_value(slider_hum, g_habitat_config.target_humidity, LV_ANIM_OFF);
}

void ui_update_task(void *arg)
{
    char buf[32];
    while (1) {
        snprintf(buf, sizeof(buf), "Temp: %.2f C", g_sensor_data.temperature);
        lv_label_set_text(label_temp, buf);
        snprintf(buf, sizeof(buf), "Humidity: %.2f %%", g_sensor_data.humidity);
        lv_label_set_text(label_hum, buf);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
