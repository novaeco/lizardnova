# ESP32 Reptile Dashboard

## Overview
The project provides a skeleton for a reptile monitoring dashboard running on an ESP32.
It uses the LVGL graphics library and includes basic components for LCD and touch
controller drivers. Data about the animals is expected in JSON format and can be
stored on the device for display.

## Hardware requirements
- ESP32 development board
- LCD using an ST7262 controller
- GT911 touch controller
- Optional storage (SPI flash or similar) for JSON data

## Build instructions (ESP‑IDF)
1. Install the [ESP‑IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) toolchain.
2. Configure the project:
   ```bash
   idf.py menuconfig
   ```
3. Build the firmware:
   ```bash
   idf.py build
   ```
   Running `idf.py build` automatically downloads any dependencies declared in `idf_component.yml` during the first build.
   If you prefer to install LVGL manually you can do so with:
   ```bash
   idf.py add-dependency "espressif/lvgl^9"
   ```
4. Flash the board and monitor the output:
   ```bash
   idf.py -p /dev/ttyUSB0 flash monitor
   ```
5. Place any JSON data (e.g. `data/animals.json`) onto the target storage if required.

## Running unit tests

The repository provides a very small test suite that can be executed on the host
without ESP‑IDF. Simply change into the `tests` directory and run `make`:

```bash
cd tests
make
```

This will build two executables, `test_animals` and `test_storage`. Run them to
verify the core components:

```bash
./test_animals
./test_storage
```

Both programs print a confirmation message when the tests pass.

## Sample data file

The `data/animals.json` file contains example reptile entries in JSON format.
After calling `storage_init()` the application can populate the in‑memory list
by invoking `animals_load_from_json()`, which internally uses
`storage_load("/animals.json", ...)` and parses the JSON data.

## Wiring

Below is a minimal reference for connecting the LCD and touch controllers. See
the driver headers for additional context.

### ST7262 LCD

- SPI MOSI &rarr; SDI
- SPI CLK  &rarr; SCL
- Chip select driven low while transferring
- DC pin selects between command (low) and data (high)
- Optional reset line held low briefly on startup

### GT911 touch controller

- Uses I<sup>2</sup>C
- SDA connected to the chosen I2C SDA pin
- SCL connected to the chosen I2C SCL pin
- The address defaults to `0x5D` but can be changed in software

For complete pinouts refer to the datasheets for the specific LCD and touch
modules you are using.
