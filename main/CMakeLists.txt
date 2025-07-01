idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "." "../components"
    REQUIRES animals storage ui utils lcd_st7262 touch_gt911
)
