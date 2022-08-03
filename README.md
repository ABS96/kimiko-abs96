# Kimiko - ABS96

This is my customised [QMK](https://qmk.fm/) firmware for the [Kimiko Split Keyboard](https://keycapsss.com/keyboard-parts/pcbs/139/kimiko-split-keyboard-pcb) with the following hardware:

- Pro Micro controllers
- OLED screens (SSD1306)
- rotary encoders (under the TRRS jacks)
- per-key LEDs

## How to use

1. [Set up](https://docs.qmk.fm/#/newbs_getting_started) your QMK Environment
2. Clone this repository into your `<QMK home>/keyboards/keycapsss/kimiko/keymaps` directory
3. If you have different hardware, [change the source code](https://github.com/Keycapsss/Kimiko/blob/master/Keymap.md#customize-the-default-keymap) accordingly
4. Build and flash the firmware using following the QMK CLI command: `make keycapsss/kimiko:abs96:avrdude`

Don't forget to set the [handedness](https://docs.qmk.fm/#/feature_split_keyboard?id=handedness-by-eeprom) of each side in the EEPROM.
