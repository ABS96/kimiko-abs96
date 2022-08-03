/* Copyright 2019 MechMerlin
 * Copyright 2020 @ben_roe (keycapsss.com)
 * Copyright 2021 @ABS96 (antokben.hu)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* Split functionality */

// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

/* Display */

#define OLED_FONT_H "keyboards/keycapsss/kimiko/keymaps/ABS96/glcdfont.c"
// #define OLED_FONT_WIDTH 5
// #define OLED_FONT_HEIGHT 7
#define OLED_BRIGHTNESS 100 // 0-255
#define OLED_FONT_START 0
#define OLED_FONT_END 223

/* Key lighting */

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_SPLIT
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_DEFAULT_HUE 4 // yellow
#define RGBLIGHT_DEFAULT_VAL RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_SLEEP            // the RGB lighting will be switched off when the host goes to sleep
#define RGBLIGHT_DISABLE_KEYCODES // redefine RGB_XXX keycodes to avoid EEPROM writes

// #define RGBLIGHT_ANIMATIONS // enables all animations
#define RGBLIGHT_EFFECT_STATIC
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
// #define RGBLIGHT_EFFECT_ALTERNATING // left-right
// #define RGBLIGHT_EFFECT_BREATHING
// #define RGBLIGHT_EFFECT_CHRISTMAS // red and green, fading
// #define RGBLIGHT_EFFECT_KNIGHT // Knight Rider
// #define RGBLIGHT_EFFECT_RAINBOW_MOOD // fading, single colour
// #define RGBLIGHT_EFFECT_RAINBOW_SWIRL // continuous fade, time shift by location
// #define RGBLIGHT_EFFECT_RGB_TEST // R, G, B
// #define RGBLIGHT_EFFECT_SNAKE
// #define RGBLIGHT_EFFECT_TWINKLE // random keys
#endif

/* Mouse input simulation */

#ifdef MOUSEKEY_ENABLE
#define MK_COMBINED
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#endif

/* Hardware-specific */

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK

// #undef DEBOUNCE
// #define DEBOUNCE 55

/* Reduce firmware size */

#define NO_ACTION_ONESHOT  // one-shot modifiers
#define NO_ACTION_MACRO    // old-style macros
#define NO_ACTION_FUNCTION // old-style functions
