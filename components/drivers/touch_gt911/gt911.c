// Minimal GT911 I2C driver

#include "gt911.h"
#include "core/utils/logging.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Default I2C address for the controller
#define GT911_ADDR 0x5D

static i2c_port_t s_port = I2C_NUM_0;
static gpio_num_t s_sda = GPIO_NUM_21;
static gpio_num_t s_scl = GPIO_NUM_22;
static uint8_t s_addr = GT911_ADDR;
static uint8_t s_rotation = 0;

void gt911_set_i2c_port(i2c_port_t port)
{
    s_port = port;
}

void gt911_set_i2c_pins(gpio_num_t sda, gpio_num_t scl)
{
    s_sda = sda;
    s_scl = scl;
}

void gt911_set_i2c_addr(uint8_t addr)
{
    s_addr = addr;
}

void gt911_set_rotation(uint8_t rotation)
{
    s_rotation = rotation & 0x03;
}

void gt911_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = s_sda,
        .scl_io_num = s_scl,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000,
        .clk_flags = 0,
    };

    esp_err_t err = i2c_param_config(s_port, &conf);
    if (err == ESP_OK) {
        err = i2c_driver_install(s_port, conf.mode, 0, 0, 0);
    }
    if (err != ESP_OK) {
        log_error("GT911", "I2C init failed (%d)", err);
    }
}

void gt911_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    (void)indev;

    uint8_t reg[2] = {0x81, 0x4E};
    uint8_t buf[5] = {0};

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (s_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write(cmd, reg, 2, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (s_addr << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, buf, sizeof(buf), I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);

    esp_err_t err = i2c_master_cmd_begin(s_port, cmd, pdMS_TO_TICKS(50));
    i2c_cmd_link_delete(cmd);

    if (err != ESP_OK) {
        data->state = LV_INDEV_STATE_REL;
        return;
    }

    if (buf[0] & 0x01) {
        uint16_t x = buf[1] | ((uint16_t)buf[2] << 8);
        uint16_t y = buf[3] | ((uint16_t)buf[4] << 8);

        switch (s_rotation) {
        case 1:
            data->point.x = y;
            data->point.y = LV_HOR_RES_MAX - x;
            break;
        case 2:
            data->point.x = LV_HOR_RES_MAX - x;
            data->point.y = LV_VER_RES_MAX - y;
            break;
        case 3:
            data->point.x = LV_VER_RES_MAX - y;
            data->point.y = x;
            break;
        default:
            data->point.x = x;
            data->point.y = y;
            break;
        }

        data->state = LV_INDEV_STATE_PR;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}

