// ST7262 LCD driver using ESP-IDF SPI master

#include "lcd_st7262.h"
#include "core/utils/logging.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LCD_H_RES 800
#define LCD_V_RES 480

#ifndef CONFIG_LCD_ST7262_MOSI
#define CONFIG_LCD_ST7262_MOSI 23
#endif
#ifndef CONFIG_LCD_ST7262_SCLK
#define CONFIG_LCD_ST7262_SCLK 18
#endif
#ifndef CONFIG_LCD_ST7262_CS
#define CONFIG_LCD_ST7262_CS 5
#endif
#ifndef CONFIG_LCD_ST7262_DC
#define CONFIG_LCD_ST7262_DC 21
#endif
#ifndef CONFIG_LCD_ST7262_RST
#define CONFIG_LCD_ST7262_RST 22
#endif

static spi_device_handle_t s_spi;
static lv_display_t *s_disp;
static lv_color_t s_buf1[LCD_H_RES * 10];
static lv_color_t s_buf2[LCD_H_RES * 10];

static inline void st7262_send(bool dc, const uint8_t *data, size_t len)
{
    gpio_set_level(CONFIG_LCD_ST7262_DC, dc);
    spi_transaction_t t = {
        .length = len * 8,
        .tx_buffer = data,
    };
    spi_device_polling_transmit(s_spi, &t);
}

static inline void st7262_cmd(uint8_t cmd)
{
    st7262_send(false, &cmd, 1);
}

static inline void st7262_data(const uint8_t *data, size_t len)
{
    st7262_send(true, data, len);
}

static void st7262_set_window(int x1, int y1, int x2, int y2)
{
    uint8_t buf[4];
    st7262_cmd(0x2A); // Column addr set
    buf[0] = x1 >> 8; buf[1] = x1 & 0xFF;
    buf[2] = x2 >> 8; buf[3] = x2 & 0xFF;
    st7262_data(buf, 4);

    st7262_cmd(0x2B); // Row addr set
    buf[0] = y1 >> 8; buf[1] = y1 & 0xFF;
    buf[2] = y2 >> 8; buf[3] = y2 & 0xFF;
    st7262_data(buf, 4);

    st7262_cmd(0x2C); // Memory write
}

static void st7262_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    int w = area->x2 - area->x1 + 1;
    int h = area->y2 - area->y1 + 1;
    st7262_set_window(area->x1, area->y1, area->x2, area->y2);
    st7262_data(px_map, w * h * sizeof(lv_color_t));
    lv_display_flush_ready(disp);
}

void lcd_st7262_init(void)
{
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL<<CONFIG_LCD_ST7262_DC) | (1ULL<<CONFIG_LCD_ST7262_RST)
    };
    gpio_config(&io_conf);

    spi_bus_config_t buscfg = {
        .mosi_io_num = CONFIG_LCD_ST7262_MOSI,
        .miso_io_num = -1,
        .sclk_io_num = CONFIG_LCD_ST7262_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_H_RES * 40
    };
    spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);

    spi_device_interface_config_t devcfg = {
        .mode = 0,
        .clock_speed_hz = 40 * 1000 * 1000,
        .spics_io_num = CONFIG_LCD_ST7262_CS,
        .queue_size = 1,
    };
    spi_bus_add_device(SPI2_HOST, &devcfg, &s_spi);

    gpio_set_level(CONFIG_LCD_ST7262_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(CONFIG_LCD_ST7262_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(120));

    st7262_cmd(0x01); // Software reset
    vTaskDelay(pdMS_TO_TICKS(120));
    st7262_cmd(0x11); // Sleep out
    vTaskDelay(pdMS_TO_TICKS(120));
    uint8_t data = 0x55; // 16bit
    st7262_cmd(0x3A);
    st7262_data(&data, 1);
    data = 0x00;
    st7262_cmd(0x36); // MADCTL
    st7262_data(&data, 1);
    st7262_cmd(0x21); // display inversion
    st7262_cmd(0x29); // display on

    s_disp = lv_display_create(LCD_H_RES, LCD_V_RES);
    lv_display_set_buffers(s_disp, s_buf1, s_buf2, sizeof(s_buf1),
                           LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(s_disp, st7262_flush);

    log_info("ST7262", "display initialised");
}

