# Driver Setup and Wiring

This project includes drivers for an ST7262-based LCD and a GT911 touch controller.
The following diagrams show the recommended connections when using an ESP32 board.

## ST7262 LCD

```
ESP32   LCD(ST7262)
------------------
MOSI -> SDI
CLK  -> SCL
CS   -> CS (active low)
DC   -> D/C
RST  -> RESET (optional)
```

`CS` should be held low while data is transferred. `DC` selects command (low) or
pixel data (high). The reset line may be toggled low on startup if the panel
requires it.

## GT911 Touch Controller

```
ESP32   Touch(GT911)
-------------------
SDA -> SDA
SCL -> SCL
INT -> INT (optional)
RST -> RESET (optional)
```

The default I2C address is `0x5D` but it can be changed in software. Consult the
datasheet for the specific panel for pin locations and voltage requirements.
