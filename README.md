# ESP32 Reptile Dashboard

[![CI](https://github.com/openai/lizardnova/actions/workflows/ci.yml/badge.svg)](https://github.com/openai/lizardnova/actions/workflows/ci.yml)

## Overview
The project provides a skeleton for a reptile monitoring dashboard running on an ESP32.
It uses the LVGL graphics library and includes basic components for LCD and touch
controller drivers. Data about the animals is expected in JSON format and can be
stored on the device for display.

Additional documentation can be found in the [docs](docs/) directory.
An overview of the built-in agents is provided in [docs/agents.md](docs/agents.md).

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
Host-based unit tests live in `tests/` and link against the system `cjson` library. Install the development package before building the tests:

```bash
sudo apt-get install libcjson-dev
```

After installing the dependency, build and run the tests from the `tests/` directory:

```bash
cd tests
make            # builds all test binaries
./test_animals
./test_animals_load
./test_logging
./test_storage
./test_ui
```

Continuous integration executes the same steps as defined in `.github/workflows/ci.yml`. See [docs/testing_ci.md](docs/testing_ci.md) for details.

## Sample data file

The `data/animals.json` file contains example reptile entries in JSON format.
After calling `storage_init()` the application can populate the in‑memory list
by invoking `animals_load_from_json()`, which internally uses
`storage_load("/animals.json", ...)` and parses the JSON data.

## Wiring

For wiring diagrams and driver setup instructions see [docs/driver_setup.md](docs/driver_setup.md).

## Contributing

Guidelines for extending the codebase are provided in [docs/extending.md](docs/extending.md).
