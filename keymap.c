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
// #include <stdio.h>

enum layers {
    _QWERTZ,

    _NAVIGATION,

    _RSYM,
    _LSYM,

    _NVKP,

    _ADJUST,
    
    _LMOD,
    _RMOD,
};

enum custom_keycodes {
    OM_LSFT = SAFE_RANGE,
    OM_LCTL,
    OM_LALT,
    OM_LGUI,
    OM_RSFT,
    OM_RCTL,
    OM_RALT,
    OM_RGUI,

    // CAPSWRD
};

uint16_t om_keycodes[] = {
    KC_LSFT,
    KC_LCTL,
    KC_LALT,
    KC_LGUI,
    KC_RSFT,
    KC_RCTL,
    KC_RALT,
    KC_RGUI
};
uint16_t om_count = 0;

// uint16_t debug_kc = 0;
bool capsword = false;

#define LAY_BAS TO(_QWERTZ)
#define LAY_RSM MO(_RSYM)
#define LAY_LSM MO(_LSYM)
#define LAY_ADJ MO(_ADJUST)
#define LAY_NKP MO(_NVKP)
#define LAY_NAV MO(_NAVIGATION)
#define ENT_NAV LT(_NAVIGATION, KC_ENT)

#define TAB_NXT C(KC_TAB)
#define TAB_PRV S(C(KC_TAB))
#define WRD_NXT C(KC_RIGHT)
#define WRD_PRV C(KC_LEFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTZ
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │  Esc │   1  │   2  │   3  │   4  │   5  │                  │   6  │   7  │   8  │   9  │   0  │ Esc  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │  Tab │   Q  │   W  │   E  │   R  │   T  │                  │   Z  │   U  │   I  │   O  │   P  │F13CWD│
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │   ⇧  ┃   A  ┃   S  ┃   D  ┃   F  ┃   G  │ Scl↕        VOL↕ │   H  ┃   J  ┃   K  ┃   L  ┃BackSp┃   ⇧  │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │   ⎈  │   Y  │   X  │   C  │   V  │   B  │╵Play╵      ╵Mute╵│   N  │   M  │   ,  │   .  │   -  │   ⎈  │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │   ◆  │   ⌥  │NAV/KP│ RSYM ╷Space │    │ NAV/⏎╷ LSYM │NAV/KP│   ⌥  │   ◆  │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

 [_QWERTZ] = LAYOUT(
    KC_ESC,  HU_1,    HU_2,    HU_3,    HU_4,    HU_5,                      HU_6,    HU_7,    HU_8,    HU_9,    HU_0,    KC_ESC,
    KC_TAB,  HU_Q,    HU_W,    HU_E,    HU_R,    HU_T,                      HU_Z,    HU_U,    HU_I,    HU_O,    HU_P,    KC_F13,
    KC_LSFT, HU_A,    HU_S,    HU_D,    HU_F,    HU_G,                      HU_H,    HU_J,    HU_K,    HU_L,    KC_BSPC, KC_RSFT,
    KC_LCTL, HU_Y,    HU_X,    HU_C,    HU_V,    HU_B,    KC_MPLY, KC_MUTE, HU_N,    HU_M,    HU_COMM, HU_DOT,  HU_MINS, KC_RCTL,
             KC_LGUI, KC_LALT, LAY_NKP, LAY_RSM, KC_SPC,  ENT_NAV, LAY_LSM, LAY_NKP, KC_LALT, KC_RGUI
),

/* NAVIGATION
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │Insert│      │      │      │                  │CapsLk│PrtScr│  MMB │PauBrk│ ScrLk│      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │ PgUp │ Home │  Up  │ End  │      │                  │      │  LMB │ M  ↑ │  RMB │  MB4 │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │      ┃ PgDn ┃ Left ┃ Down ┃ Right┃      │ Word↔            │      ┃ M  ← ┃ M  ↓ ┃ M  → ┃  MB5 ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │ Word←│ Word→│ Tab← │ Tab→ │ Tab  │╵    ╵      ╵    ╵│      │ Left │ Down │  Up  │ Right│      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │      ╷      │    │[NAV] │      │      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

[_NAVIGATION] = LAYOUT(
    _______, _______, KC_INS,  _______, _______, _______,                     KC_CLCK, KC_PSCR, KC_BTN3, KC_PAUS, KC_SLCK, _______,
    _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______,                     _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN4, _______,
    _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______,                     _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5, _______,
    _______, WRD_PRV, WRD_NXT, TAB_PRV, TAB_NXT, KC_TAB,   _______, _______,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
                      _______, _______, _______, _______,  _______, _______,  _______, _______, _______, _______
),
/* RSYM(LMOD) + diaereses
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │  F12 │  F1  │  F2  │  F3  │  F4  │  F5  │                  │  F6  │  F7  │  F8  │  F9  │ F10  │ F11  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                  │   $  │   Ü  │   !  │   Ö  │   +  │   -  │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │      ┃   ◆  ┃   ⌥  ┃   ⎈  ┃   ⇧  ┃      │ Scl↔             │   "  ┃   (  ┃   )  ┃   =  ┃Delete┃   _  │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │      │      │      │      │      │╵    ╵      ╵    ╵│   ~  │   {  │   }  │   %  │   *  │   :  │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │[RSYM]╷      │    │ Esc  │      │      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */
[_RSYM] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, _______, _______, _______,                   HU_DLR,  HU_UDIA, HU_EXLM, HU_ODIA, HU_PLUS, HU_MINS,
    _______, OM_LGUI, OM_LALT, OM_LCTL, OM_LSFT, _______,                   HU_DQUO, HU_LPRN, HU_RPRN, HU_EQL,  KC_DEL,  HU_UNDS,
    _______, _______, _______, _______, _______, _______, _______, _______, HU_TILD, HU_LCBR, HU_RCBR, HU_PERC, HU_ASTR, HU_COLN,
                      _______, _______, _______, _______, _______, KC_ESC,  _______, _______, _______, _______
),
/* LSYM(RMOD) + acutes
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │  F12 │  F1  │  F2  │  F3  │  F4  │  F5  │                  │  F6  │  F7  │  F8  │  F9  │ F10  │ F11  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │   \  │   |  │   É  │   /  │   &  │                  │      │   Ú  │   Í  │   Ó  │      │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │   `  ┃   Á  ┃   ;  ┃   [  ┃   ]  ┃   '  │RGB VAL    RGB HUE│      ┃   ⇧  ┃   ⎈  ┃   ⌥  ┃   ◆  ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │   ^  │   #  │   <  │   >  │   @  │╵    ╵      ╵    ╵│      │      │      │ AltGr│      │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │      ╷      │    │      │[LSYM]│      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

[_LSYM] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, HU_BSLS, HU_PIPE, HU_EACU, HU_SLSH, HU_AMPR,                   _______, HU_UACU, HU_IACU, HU_OACU, _______, _______,
    HU_GRV,  HU_AACU, HU_SCLN, HU_LBRC, HU_RBRC, HU_QUOT,                   _______, OM_RSFT, OM_RCTL, OM_LALT, OM_RGUI, _______,
    _______, HU_CIRC, HU_HASH, HU_LABK, HU_RABK, HU_AT,   _______, _______, _______, _______, _______, OM_RALT, _______, _______,
                      _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______, _______
),
/* ADJUST (LMOD + RMOD) + double acutes
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │ RESET│      │      │      │      │      │                  │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │RGB ON│ HUE+ │ SAT+ │ VAL+ │ BRI- │      │                  │      │   Ű  │ Play │   Ő  │      │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │ MODE ┃ HUE- ┃ SAT- ┃ VAL- ┃ BRI+ ┃      │                  │      ┃ Prev ┃ VOL- ┃ VOL+ ┃ Next ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │ DEBUG│      │ Wake │ Sleep│      │      │╵    ╵      ╵    ╵│      │ Rwnd │ Mute │ Stop │ Ffwd │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │ [ADJ]╷      │    │      │ [ADJ]│      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

[_ADJUST] = LAYOUT(
    RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_BRIU, XXXXXXX,                   XXXXXXX, HU_UDAC, KC_MPLY, HU_ODAC, XXXXXXX, XXXXXXX,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_BRID, XXXXXXX,                   XXXXXXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_WAKE, KC_SLEP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MRWD, KC_MUTE, KC_MSTP, KC_MFFD, XXXXXXX,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
/* NAVIGATION / KEYPAD
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │Insert│Delete│      │      │                  │      │ NumLk│ KP / │ KP * │ KP - │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │ PgUp │ Home │  Up  │ End  │      │                  │      │ KP 4 │ KP 5 │ KP 6 │ KP + │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │      ┃ PgDn ┃ Left ┃ Down ┃ Right┃   ⏎  │                  │ KP . ┃ KP 1 ┃ KP 2 ┃ KP 3 ┃ KP 0 ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │ Word←│ Word→│ Tab← │ Tab→ │ Tab  │╵    ╵      ╵    ╵│      │ KP 7 │ KP 8 │ KP 9 │ KP ⏎ │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │[NVKP]│      ╷      │    │      │      │[NVKP]│      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

[_NVKP] = LAYOUT(
    _______, _______, KC_INS,  KC_DEL,  _______, _______,                   _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, _______,
    _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______,                   _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______,
    _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT,                    KC_PDOT, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_0, _______,
    _______, WRD_PRV, WRD_NXT, TAB_PRV, TAB_NXT, KC_TAB,  _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PENT, _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_LMOD] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, OM_LGUI, OM_LALT, OM_LCTL, OM_LSFT, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
[_RMOD] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                   _______, OM_RSFT, OM_RCTL, OM_LALT, OM_RGUI, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, OM_RALT, _______, _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};


layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LSYM, _RSYM, _ADJUST);
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {    
    // One-shot modifier fire detection
    if (IS_LAYER_ON(_LMOD) || IS_LAYER_ON(_RMOD)) {
        if (OM_LSFT <= keycode && keycode <= OM_RGUI) {
            if (record->event.pressed) {
                register_code(om_keycodes[keycode - SAFE_RANGE]);
                ++om_count;
            } else {
                unregister_code(om_keycodes[keycode - SAFE_RANGE]);
                --om_count;
                if (om_count < 1) {
                    layer_off(_LMOD);
                    layer_off(_RMOD);
                }
            }
        }
    }

    // One-shot modifier entry point
    if (
        (om_count == 0) // no one-shot modifiers are currently held and
        && (OM_LSFT <= keycode && keycode <= OM_RGUI) // a one-shot mod
        && record->event.pressed                      // was pressed
    ) {
        if (IS_LAYER_ON(_RSYM)) {
            layer_off(_RSYM);
            layer_on(_LMOD);
        }
        if (IS_LAYER_ON(_LSYM)) {
            layer_off(_LSYM);
            layer_on(_RMOD);
        }

        register_code(om_keycodes[keycode - SAFE_RANGE]); // Hold modifier
        ++om_count; // Remember that one mod key is being held
        return false;
    }

    return true;
}

void suspend_power_down_user() {
    oled_off();
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

uint8_t count_ones(uint8_t sample) {
    static const uint8_t LUT4[16] = {
        0, 1, 1, 2, 1, 2, 2, 3,
        1, 2, 2, 3, 2, 3, 3, 4
    };

    return LUT4[sample & 0x0F];
}

void render_modifiers(uint8_t mods) {
    static const char PROGMEM ctrl_4x[] = {
        0x20, 0xC3, 0xC4, 0xC5, 0xC6,
        0x20, 0xC7, 0xC8, 0xC9, 0xCA,
        0x20, 0xCB, 0xCC, 0xCD, 0xCB,
    0};
    static const char PROGMEM shift_4x[] = {
        0x20, 0x20, 0x92, 0x93, 0x20,
        0x20, 0xCE, 0xCF, 0xD0, 0xD1,
        0x20, 0x20, 0x91, 0x94, 0x20,
    0};
    static const char PROGMEM alt_4x[] = {
        0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0xBD, 0x9D, 0x9E, 0x9F,
        0x20, 0x20, 0x20, 0x20, 0x20,
    0};
    static const char PROGMEM gui_4x[] = {
        0x20, 0x20, 0x92, 0x93, 0x20,
        0x20, 0xB1, 0xB2, 0xB3, 0xB4,
        0x20, 0x20, 0xD2, 0xD3, 0x20,
    0};
    static const char PROGMEM meh_1x[] = {
        0xD5, 0xD6, 0xD7, 0xD8, 0xD9,
    0};
    static const char PROGMEM hyper_4x[] = {
        0x20, 0x20, 0xBE, 0xBF, 0x20,
        0x20, 0xDA, 0xDB, 0xDC, 0xDD,
        0x20, 0x20, 0xDE, 0xDF, 0x20,
    0};

    static const char PROGMEM ctrl_2x_top[] =     {0x95, 0x96, 0};
    static const char PROGMEM ctrl_2x_bottom[] =  {0xB5, 0xB6, 0};
    static const char PROGMEM shift_2x_top[] =    {0x97, 0x98, 0};
    static const char PROGMEM shift_2x_bottom[] = {0xB7, 0xB8, 0};
    static const char PROGMEM alt_2x_top[] =      {0x99, 0x9A, 0};
    static const char PROGMEM alt_2x_bottom[] =   {0xB9, 0xBA, 0};
    static const char PROGMEM gui_2x_top[] =      {0x9B, 0x9C, 0};
    static const char PROGMEM gui_2x_bottom[] =   {0xBB, 0xBC, 0};

    // mods: (GASC)R(GASC)L
    uint8_t mod4 = (mods >> 4) | (mods & 0x0F);
    bool ctrl_on =  (mod4 & 0b00000001) == 0b00000001;
    bool shift_on = (mod4 & 0b00000010) == 0b00000010;
    bool alt_on =   (mod4 & 0b00000100) == 0b00000100;
    bool gui_on =   (mod4 & 0b00001000) == 0b00001000;

    if (mod4 == 0x0F) {
        oled_write_P(hyper_4x, false);
        render_space();
        return;
    }

    if (mod4 == 0b00000111) {
        render_space();
        oled_write_P(meh_1x, false);
        render_space();
        render_space();
        return;
    }

    if (count_ones(mod4) >= 2) {
        oled_write_P(PSTR(" "), false);
        if (ctrl_on)  oled_write_P(ctrl_2x_top, false);  else oled_write_P(PSTR("  "), false);
        if (shift_on) oled_write_P(shift_2x_top, false); else oled_write_P(PSTR("  "), false);

        oled_write_P(PSTR(" "), false);
        if (ctrl_on)  oled_write_P(ctrl_2x_bottom, false);  else oled_write_P(PSTR("  "), false);
        if (shift_on) oled_write_P(shift_2x_bottom, false); else oled_write_P(PSTR("  "), false);


        oled_write_P(PSTR(" "), false);
        if (alt_on)   oled_write_P(alt_2x_top, false); else oled_write_P(PSTR("  "), false);
        if (gui_on)   oled_write_P(gui_2x_top, false); else oled_write_P(PSTR("  "), false);

        oled_write_P(PSTR(" "), false);
        if (alt_on)   oled_write_P(alt_2x_bottom, false); else oled_write_P(PSTR("  "), false);
        if (gui_on)   oled_write_P(gui_2x_bottom, false); else oled_write_P(PSTR("  "), false);

        return;
    }


    if (count_ones(mod4) == 1) {
        if (ctrl_on)  oled_write_P(ctrl_4x, false);
        if (shift_on) oled_write_P(shift_4x, false);
        if (alt_on)   oled_write_P(alt_4x, false);
        if (gui_on)   oled_write_P(gui_4x, false);
        render_space();
        return;
    }

    if (count_ones(mod4) == 0) {
        render_space();
        render_space();
        render_space();
        render_space();
        return;
    }
}

void render_logo(void) {
    static const char PROGMEM ABS_logo[] = {
        0x20, 0x81, 0x82, 0x83, 0x84,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
        0xC0, 0xC1, 0xC2, 0x20, 0x20,
    0};
    oled_write_P(ABS_logo, false);
}

void render_layer_state(void) {
    static const char PROGMEM sym_top[] = {0x86, 0x87, 0x88, 0};
    static const char PROGMEM sym_bot[] = {0xA6, 0xA7, 0xA8, 0};

    static const char PROGMEM nav_top[] = {0x89, 0x8A, 0x8B, 0};
    static const char PROGMEM nav_bot[] = {0xA9, 0xAA, 0xAB, 0};

    static const char PROGMEM nkp_top[] = {0x8C, 0x8D, 0x8E, 0};
    static const char PROGMEM nkp_bot[] = {0xAC, 0xAD, 0x8E, 0};

    static const char PROGMEM adj_top[] = {0x20, 0x8F, 0x90, 0};
    static const char PROGMEM adj_bot[] = {0xAE, 0xAF, 0x20, 0};


    if (IS_LAYER_ON(_NAVIGATION)) {
        oled_write_P(PSTR(" "), false);
        oled_write_ln_P(nav_top, false);
        oled_write_P(PSTR(" "), false);
        oled_write_ln_P(nav_bot, false);
    }
    else if (IS_LAYER_ON(_ADJUST)) {
        oled_write_P(PSTR(" "), false);
        oled_write_ln_P(adj_top, false);
        oled_write_P(PSTR(" "), false);
        oled_write_ln_P(adj_bot, false);
    }
    else if (IS_LAYER_ON(_NVKP)) {
        oled_write_P(PSTR(" "), false);
        oled_write_ln_P(nkp_top, false);
        oled_write_P(PSTR(" "), false);
        oled_write_ln_P(nkp_bot, false);
    }
    else if (IS_LAYER_ON(_RSYM)) {
        oled_write_P(PSTR(" "), false);
        oled_write_P(sym_top, false);
        oled_write_P(PSTR("\x85 "), false);
        oled_write_P(sym_bot, false);
        oled_write_P(PSTR("\xA5"), false);
    }
    else if (IS_LAYER_ON(_LSYM)) {
        oled_write_P(PSTR("\x80"), false);
        oled_write_P(sym_top, false);
        oled_write_P(PSTR(" \xD4"), false);
        oled_write_ln_P(sym_bot, false);
    }
    else {
        render_space();
        render_space();
    }
}

void render_mod_layer_state(void) {
    if (IS_LAYER_ON(_LMOD))
        oled_write_P(PSTR("\x1BMOD "), false);
    else if (IS_LAYER_ON(_RMOD))
        oled_write_P(PSTR(" MOD\x1A"), false);
    else
        render_space();
}

void render_lock_state(led_t led_union) {
    if (led_union.num_lock) {
        oled_write_char(7, false);
        oled_write_P(PSTR("NUM "), false);
    } else
        render_space();

    if (led_union.caps_lock) {
        oled_write_char(7, false);
        oled_write_P(PSTR("CAPS"), false);
    } else
        render_space();

    if (led_union.scroll_lock) {
        oled_write_char(7, false);
        oled_write_P(PSTR("SCRL"), false);
    } else
        render_space();
}

void render_status_main(void) {
    render_logo(); // 3
    render_space();
    render_space();
    render_layer_state(); // 2
    render_mod_layer_state(); // 1
    render_space();
    render_modifiers(get_mods() | get_oneshot_mods()); // 4
    render_lock_state(host_keyboard_led_state()); // 3
}

void render_status_secondary(void) {
    render_logo();
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

            case _NAVIGATION:
            case _NVKP:

                // Scroll by Word
                if (clockwise) {
                    tap_code16(LCTL(KC_LEFT));
                } else {
                    tap_code16(LCTL(KC_RGHT));
                }
                break;

            case _LMOD:
                // Mouse scroll Right/Left
                if (clockwise) {
                    tap_code(KC_WH_R);
                } else {
                    tap_code(KC_WH_L);
                }
                break;
            
            case _RMOD:
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

            case _NAVIGATION:
            case _NVKP:

                // Switch tab
                if (clockwise) {
                    tap_code16(LSFT(LCTL(KC_TAB)));
                } else {
                    tap_code16(LCTL(KC_TAB));
                }
                break;

            case _RMOD:
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
