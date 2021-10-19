#pragma once
#include QMK_KEYBOARD_H
#include "keymap_hungarian.h"

bool capsword_enabled(void);
void capsword_on(void);
void capsword_off(void);
void capsword_toggle(void);

bool process_capsword(uint16_t keycode, const keyrecord_t *record);
