ENCODER_ENABLE = yes

OLED_DRIVER_ENABLE = yes
RGBLIGHT_ENABLE = yes
MOUSEKEY_ENABLE = yes

LTO_ENABLE = yes
BOOTLOADER = caterina      # Compile for Pro Micro 

SRC += features/oled.c
SRC += features/capsword.c
SRC += features/decolayer.c
