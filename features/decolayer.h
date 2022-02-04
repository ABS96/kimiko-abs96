#pragma once
#include QMK_KEYBOARD_H
#include "keymap_hungarian.h"

enum decolayer_state {
  DECO_OFF = 0,
  DECO_FULLWIDTH,
  DECO_MATHBOLD,
  DECO_SANS,
  DECO_SANSBOLD,
  DECO_SANSITAL,
  DECO_SANSBOIT
};

void deco_off(void);
void deco_on(enum decolayer_state selected);

enum decolayer_state get_deco_state(void);
bool process_decolayer(uint16_t keycode, const keyrecord_t *record);
