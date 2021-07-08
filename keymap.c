/* Copyright 2019 Leo Batyuk
 * Copyright 2020 Drashna Jaelre <@drashna>
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

#ifndef __INTELLISENSE__
#include QMK_KEYBOARD_H
#endif
#include "keymap_hungarian.h"

enum layers {
    _QWERTZ,
    // _GAMING,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMBER,
    _FUNCTION
};

#define BASE TO(_QWERTZ)
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define ADJUST MO(_ADJUST)
#define NUMBER TG(_NUMBER)
#define FUNCT OSL(_FUNCTION)
// #define GAMING TG(_GAMING)

// #define HM_GUIA MT(MOD_LGUI, HU_A)
// #define HM_ALTS MT(MOD_LALT, HU_S)
// #define HM_SFTD MT(MOD_LGUI, HU_D)
// #define HM_CTLF MT(MOD_LCTL, HU_F)
// #define HM_CTLJ MT(MOD_RCTL, HU_J)
// #define HM_SFTK MT(MOD_RSFT, HU_K)
// #define HM_ALTL MT(MOD_LALT, HU_L)
// #define HM_GUIB MT(MOD_RGUI, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTZ
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │  Esc │   1  │   2  │   3  │   4  │   5  │                  │   6  │   7  │   8  │   9  │   0  │ Esc  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │  Tab │   Q  │   W  │   E  │   R  │   T  │                  │   Z  │   U  │   I  │   O  │   P  │ Tab  │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │   ⇧  ┃   A  ┃   S  ┃   D  ┃   F  ┃   G  │ Scl↕        VOL  │   H  ┃   J  ┃   K  ┃   L  ┃BackSp┃   ⇧  │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │   ⎈  │   Y  │   X  │   C  │   V  │   B  │╵Play╵      ╵Mute╵│   N  │   M  │   ,  │   .  │   -  │   ⎈  │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │   ◆  │   ⌥  │  NUM │   ▼  ╷Space │    │Enter ╷   ▲  │  FUN │   ⌥  │   ◆  │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

 [_QWERTZ] = LAYOUT(
    KC_ESC,  HU_1,    HU_2,    HU_3,    HU_4,    HU_5,                      HU_6,    HU_7,    HU_8,    HU_9,    HU_0,    KC_ESC,
    KC_TAB,  HU_Q,    HU_W,    HU_E,    HU_R,    HU_T,                      HU_Z,    HU_U,    HU_I,    HU_O,    HU_P,    KC_TAB,
    KC_LSFT, HU_A,    HU_S,    HU_D,    HU_F,    HU_G,                      HU_H,    HU_J,    HU_K,    HU_L,    KC_BSPC, KC_RSFT,
    // KC_LSFT, HM_GUIA, HM_ALTS, HM_SFTD, HM_CTLF, HU_G,                      HU_H,    HM_CTLJ, HM_SFTK, HM_ALTL, HM_GUIB, KC_RSFT,
    KC_LCTL, HU_Y,    HU_X,    HU_C,    HU_V,    HU_B,    KC_MPLY, KC_MUTE, HU_N,    HU_M,    HU_COMM, HU_DOT,  HU_MINS, KC_RCTL,
             KC_LGUI, KC_LALT, NUMBER,  LOWER,   KC_SPC,  KC_ENT,  RAISE,   FUNCT,   KC_LALT, KC_RGUI
),

/* LOWER
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │  F12 │  F1  │  F2  │  F3  │  F4  │  F5  │                  │  F6  │  F7  │  F8  │  F9  │ F10  │ F11  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │   \  │   |  │   É  │   &  │   /  │                  │   !  │   Ú  │   Í  │   Ó  │   +  │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │   `  ┃   Á  ┃   $  ┃   [  ┃   ]  ┃   '  │ Scl↔        Word │   "  ┃   (  ┃   )  ┃   =  ┃Delete┃   ;  │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │   ^  │   #  │   <  │   >  │   @  │╵    ╵      ╵    ╵│   ~  │   {  │   }  │   %  │   *  │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │      ╷      │    │ Esc  │      │Delete│ AltGr│ Menu │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

[_LOWER] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, HU_BSLS, HU_PIPE, HU_EACU, HU_AMPR, HU_SLSH,                   HU_EXLM, HU_UACU, HU_IACU, HU_OACU, HU_PLUS, _______,
    HU_GRV,  HU_AACU, HU_DLR,  HU_LBRC, HU_RBRC, HU_QUOT,                   HU_DQUO, HU_LPRN, HU_RPRN, HU_EQL,  KC_DEL,  HU_SCLN,
    _______, HU_CIRC, HU_HASH, HU_LABK, HU_RABK, HU_AT,   _______, _______, HU_TILD, HU_LCBR, HU_RCBR, HU_PERC, HU_ASTR, _______,
                      _______, _______, _______, _______, _______, KC_ESC,  _______, KC_DEL,  KC_RALT, KC_APP
),
/* RAISE
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │ Help │Insert│      │      │      │                  │CapsLk│PrtScr│ScrLk │PauBrk│      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │ PgUp │ Home │  Up  │ End  │      │                  │      │   Ü  │ M  ↑ │   Ö  │ MMB  │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │      ┃ PgDn ┃ Left ┃ Down ┃ Right┃      │RGB VAL    RGB HUE│  LMB ┃ M  ← ┃ M  ↓ ┃ M  → ┃ RMB  ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │      │      │      │      │      │╵    ╵      ╵    ╵│      │ Left │ Down │  Up  │Right │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │      ╷      │    │      │      │      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

[_RAISE] = LAYOUT(
    _______, KC_HELP, KC_INS,  _______, _______, _______,                     KC_CLCK, KC_PSCR, KC_SLCK, KC_PAUS, _______, _______,
    _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______,                     _______, HU_UDIA, KC_MS_U, HU_ODIA, KC_BTN3, _______,
    _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______,                     KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN2, _______,
    _______, _______, _______, _______, _______, _______,  _______, _______,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
                      _______, _______, ADJUST,  KC_DEL,   _______, _______,  _______, _______, _______, _______
),
/* ADJUST (Press LOWER and RAISE together)
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │RESET │      │      │      │      │      │                  │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │RGB ON│ HUE+ │ SAT+ │ VAL+ │ BRI- │ Eject│                  │      │   Ű  │      │   Ő  │      │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │ MODE ┃ HUE- ┃ SAT- ┃ VAL- ┃ BRI+ ┃      │                  │ MUTE ┃ Prev ┃ VOL- ┃ VOL+ ┃ Next ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │      │      │ Sleep│      │      │╵    ╵      ╵    ╵│ Stop │ Rwnd │      │      │ Ffwd │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │      ╷      │    │      │      │      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

[_ADJUST] = LAYOUT(
    RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_BRIU, KC_EJCT,                   XXXXXXX, HU_UDAC, XXXXXXX, HU_ODAC, XXXXXXX, XXXXXXX,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_BRID, XXXXXXX,                   KC_MUTE, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_SLEP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MSTP, KC_MRWD, XXXXXXX, XXXXXXX, KC_MFFD, XXXXXXX,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
/* NUMBER
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │                  │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                  │      │      │      │      │      │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │      ┃   1  ┃   2  ┃   3  ┃   4  ┃      │                  │      ┃   7  ┃   8  ┃   9  ┃   0  ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │      │      │      │   5  │      │╵    ╵      ╵    ╵│      │   6  │      │      │      │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │      ╷      │    │      │      │      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

[_NUMBER] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, HU_1,    HU_2,    HU_3,    HU_4,    _______,                   _______, HU_7,    HU_8,    HU_9,    HU_0,    _______,
    _______, _______, _______, _______, HU_5,    _______, _______, _______, _______, HU_6,    _______, _______, _______, _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
/* FUNCTION
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │                  │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                  │      │      │      │      │      │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │ F12  ┃  F1  ┃  F2  ┃  F3  ┃  F4  ┃      │                  │      ┃  F7  ┃  F8  ┃  F9  ┃ F10  ┃ F11  │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │      │      │      │  F5  │      │╵    ╵      ╵    ╵│      │  F6  │      │      │      │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │      ╷      │    │      │      │      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

[_FUNCTION] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,                   _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, _______, KC_F5,   _______, _______, _______, _______, KC_F6,   _______, _______, _______, _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
};


layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed){
        // Turn off numbers layer automatically
        if (IS_LAYER_ON(_NUMBER)) {
            switch (keycode) {
            case HU_0:
            case HU_1 ... HU_9:
                break;
            default:
                layer_off(_NUMBER);
                break;
            }
        }
    }
    return true;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_270;
    }
}

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0};
    oled_write_P(corne_logo, false);
    // oled_write_P(PSTR("Kimiko"), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(_ADJUST)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(_LOWER)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

void render_status_main(void) {
    render_space();
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
    render_space();
    switch(get_highest_layer(layer_state)) {
        case _QWERTZ:
            oled_write_P(PSTR(" BAS"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR(" LWR"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR(" RSE"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR(" ADJ"), false);
            break;
        case _NUMBER:
            oled_write_P(PSTR(" NUM"), false);
            break;
        case _FUNCTION:
            oled_write_P(PSTR(" FUN"), false);
            break;
    }
    // if (layer_state_is(_GAMING) == true) {
    //     render_space(); 
    //     oled_write_P(PSTR(" GAM"), false);
    // }

}

void render_status_secondary(void) {
    render_space();
    render_logo();
    render_space();
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // Left encoder
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _QWERTZ:
                // Mouse scroll Up/Down
                if (clockwise) {
                    tap_code(KC_WH_D);
                } else {
                    tap_code(KC_WH_U);
                }
                break;

            case _LOWER:
                // Mouse scroll Right/Left
                if (clockwise) {
                    tap_code(KC_WH_R);
                } else {
                    tap_code(KC_WH_L);
                }
                break;
            
            case _RAISE:
                // RGB brightness up/down
                if (clockwise) {
                    rgblight_decrease_val();
                } else {
                    rgblight_increase_val();
                }
                break;
        }
    }
    // Right encoder
    else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _QWERTZ:
                // Volume Up/Down
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;

            case _LOWER:

                // Scroll by Word
                if (clockwise) {
                    tap_code16(LCTL(KC_RGHT));
                } else {
                    tap_code16(LCTL(KC_LEFT));
                }
                break;

            case _RAISE:
                // RGB hue Up/Down
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
                break;
        }
    }
    return true;
}
#endif // ENCODER_ENABLE
