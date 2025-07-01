#pragma once
#include <string.h>
typedef int i2c_port_t;
typedef int i2c_cmd_handle_t;
typedef struct {int mode; int sda_io_num; int scl_io_num; int sda_pullup_en; int scl_pullup_en; struct {int clk_speed;} master; int clk_flags;} i2c_config_t;
static inline int i2c_param_config(i2c_port_t port, const i2c_config_t *conf) { return 0; }
static inline int i2c_driver_install(i2c_port_t port, int mode, int rx, int tx, int flags) { return 0; }
static inline i2c_cmd_handle_t i2c_cmd_link_create(void) { return 0; }
static inline void i2c_cmd_link_delete(i2c_cmd_handle_t cmd) { (void)cmd; }
static inline int i2c_master_start(i2c_cmd_handle_t cmd) { return 0; }
static inline int i2c_master_write_byte(i2c_cmd_handle_t cmd, int data, int ack) { return 0; }
static inline int i2c_master_write(i2c_cmd_handle_t cmd, const void *buf, int len, int ack) { return 0; }
static inline int i2c_master_read(i2c_cmd_handle_t cmd, void *buf, int len, int last_nack) { memset(buf,0,len); return 0; }
static inline int i2c_master_stop(i2c_cmd_handle_t cmd) { return 0; }
static inline int i2c_master_cmd_begin(i2c_port_t port, i2c_cmd_handle_t cmd, int ticks) { return 0; }
