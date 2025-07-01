cmake_minimum_required(VERSION 3.5)

# List every component directory explicitly so ESP-IDF can find them
set(EXTRA_COMPONENT_DIRS
    "${CMAKE_CURRENT_LIST_DIR}/components/core/animals"
    "${CMAKE_CURRENT_LIST_DIR}/components/core/ui"
    "${CMAKE_CURRENT_LIST_DIR}/components/core/utils"
    "${CMAKE_CURRENT_LIST_DIR}/components/storage"
    "${CMAKE_CURRENT_LIST_DIR}/components/drivers/lcd_st7262"
    "${CMAKE_CURRENT_LIST_DIR}/components/drivers/touch_gt911"
    "${CMAKE_CURRENT_LIST_DIR}/components/lvgl"
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(esp32-reptile-dashboard)
