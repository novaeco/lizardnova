# Reptile Manager Pro

## Project Overview
Reptile Manager Pro is a basic example using the LVGL graphics library on the ESP32‑S3 RGB Panel board. The project initializes LVGL and displays a colored screen that you can extend to build your own UI. It serves as a starting point for developing applications on Espressif's RGB panel hardware.

## Hardware Requirements
- ESP32‑S3 RGB Panel board (8&nbsp;MB flash, 8&nbsp;MB PSRAM)
- 4.0‑inch 480×480 RGB565 display with GT911 capacitive touch
- ES8311 audio codec (supported by the board)
- External USB‑to‑UART adapter for flashing

## Build and Flash Instructions
1. Install **ESP-IDF 5.0** or newer. Follow the [ESP-IDF setup guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/).
2. From the project directory, set the target and build the firmware:
   ```bash
   idf.py set-target esp32s3
   idf.py build
   ```
3. Put the board into download mode if necessary (hold **BOOT**, press **RST**, release **RST**, then release **BOOT**). Flash and monitor:
   ```bash
   idf.py flash monitor
   ```

## Usage and Documentation
After flashing, the board will reboot and show the LVGL demo screen. Use `Ctrl+]` to exit the monitor.

Board details and assembly instructions are located in [components/ESP32-S3-RGB-Panel/README.md](components/ESP32-S3-RGB-Panel/README.md) and [components/ESP32-S3-RGB-Panel/docs/Assemble-espP32-rgb-4inch.pdf](components/ESP32-S3-RGB-Panel/docs/Assemble-espP32-rgb-4inch.pdf). Additional information can be found in the hardware repository: [https://github.com/W00ng/ESP32-S3-RGB-Panel](https://github.com/W00ng/ESP32-S3-RGB-Panel).
