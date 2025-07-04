idf_component_register(SRCS "main.cpp"
                    "sensors.cpp"
                    "storage.cpp"
                    "ui.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES i2c_devices)
