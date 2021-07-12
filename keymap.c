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

    _LNUM,
    _RNUM,

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
// #define LAY_RSM LT(_RSYM, KC_SPACE)
#define LAY_LSM MO(_LSYM)
#define LAY_ADJ MO(_ADJUST)
#define LAY_LNM MO(_LNUM)
#define LAY_RNM MO(_RNUM)
#define LAY_NAV LT(_NAVIGATION, KC_ENT)

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
 *               │   ◆  │   ⌥  │ RNUM │ RSYM ╷Space │    │ NAV/⏎╷ LSYM │ LNUM │   ⌥  │   ◆  │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

 [_QWERTZ] = LAYOUT(
    KC_ESC,  HU_1,    HU_2,    HU_3,    HU_4,    HU_5,                      HU_6,    HU_7,    HU_8,    HU_9,    HU_0,    KC_ESC,
    KC_TAB,  HU_Q,    HU_W,    HU_E,    HU_R,    HU_T,                      HU_Z,    HU_U,    HU_I,    HU_O,    HU_P,    KC_F13,
    KC_LSFT, HU_A,    HU_S,    HU_D,    HU_F,    HU_G,                      HU_H,    HU_J,    HU_K,    HU_L,    KC_BSPC, KC_RSFT,
    KC_LCTL, HU_Y,    HU_X,    HU_C,    HU_V,    HU_B,    KC_MPLY, KC_MUTE, HU_N,    HU_M,    HU_COMM, HU_DOT,  HU_MINS, KC_RCTL,
             KC_LGUI, KC_LALT, LAY_RNM, LAY_RSM, KC_SPC,  LAY_NAV, LAY_LSM, LAY_LNM, KC_LALT, KC_RGUI
),

/* NAVIGATION
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │Insert│      │      │      │                  │CapsLk│PrtScr│  MMB │PauBrk│ ScrLk│      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │ PgUp │ Home │  Up  │ End  │      │                  │      │  LMB │ M  ↑ │  RMB │  MB4 │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │      ┃ PgDn ┃ Left ┃ Down ┃ Right┃      │ Word↔            │      ┃ M  ← ┃ M  ↓ ┃ M  → ┃  MB5 ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │ Word←│ Word→│ Tab← │ Tab→ │      │╵    ╵      ╵    ╵│      │ Left │ Down │  Up  │ Right│      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │      ╷      │    │[NAV] │      │      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

[_NAVIGATION] = LAYOUT(
    _______, _______, KC_INS,  _______, _______, _______,                     KC_CLCK, KC_PSCR, KC_BTN3, KC_PAUS, KC_SLCK, _______,
    _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______,                     _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN4, _______,
    _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______,                     _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5, _______,
    _______, WRD_PRV, WRD_NXT, TAB_PRV, TAB_NXT, _______,  _______, _______,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
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
 * │      │      │      │      │      │      │╵    ╵      ╵    ╵│   ~  │   {  │   }  │   %  │   *  │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │[RSYM]╷      │    │ Esc  │      │      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */
[_RSYM] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, _______, _______, _______,                   HU_DLR,  HU_UDIA, HU_EXLM, HU_ODIA, HU_PLUS, HU_MINS,
    _______, OM_LGUI, OM_LALT, OM_LCTL, OM_LSFT, _______,                   HU_DQUO, HU_LPRN, HU_RPRN, HU_EQL,  KC_DEL,  HU_UNDS,
    _______, _______, _______, _______, _______, _______, _______, _______, HU_TILD, HU_LCBR, HU_RCBR, HU_PERC, HU_ASTR, _______,
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
    DEBUG,   XXXXXXX, KC_WAKE, KC_SLEP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MRWD, KC_MUTE, KC_MSTP, KC_MFFD, XXXXXXX,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
/* LNUM(RMOD)
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │ KP 1 │ KP 2 │ KP 3 │ KP 4 │ KP 5 │                  │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │  F12 │  F1  │  F2  │  F3  │  F4  │  F5  │                  │      │      │      │      │      │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │      ┃   1  ┃   2  ┃   3  ┃   4  ┃   5  │                  │      ┃   ⇧  ┃   ⎈  ┃   ⌥  ┃   ◆  ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │      │      │      │   5  │      │╵    ╵      ╵    ╵│      │      │      │ AltGr│      │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │      ╷      │    │      │      │[LNUM]│      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

[_LNUM] = LAYOUT(
    _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_4, KC_KP_5,                   _______, _______, _______, _______, _______, _______,
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     _______, _______, _______, _______, _______, _______,
    _______, HU_1,    HU_2,    HU_3,    HU_4,    HU_5,                      _______, OM_RSFT, OM_RCTL, OM_LALT, OM_RGUI, _______,
    _______, _______, _______, _______, HU_5,    _______, _______, _______, _______, _______, _______, OM_RALT, _______, _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
/* RNUM(LMOD)
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │                  │ KP 6 │ KP 7 │ KP 8 │ KP 9 │ KP 0 │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                  │  F6  │  F7  │  F8  │  F9  │  F10 │  F11 │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │      ┃   ◆  ┃   ⌥  ┃   ⎈  ┃   ⇧  ┃      │                  │   6  ┃   7  ┃   8  ┃   9  ┃   0  ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │      │      │      │      │      │╵    ╵      ╵    ╵│ KP . │   6  │ KP / │ KP * │ KP - │ KP + │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │[RNUM]│      ╷      │    │ KP ⏎ │      │      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */

[_RNUM] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   KC_KP_6, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_0, _______,
    _______, _______, _______, _______, _______, _______,                   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, OM_LGUI, OM_LALT, OM_LCTL, OM_LSFT, _______,                   HU_6,    HU_7,    HU_8,    HU_9,    HU_0,    _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_PDOT, HU_6,    KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS,
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
        if (IS_LAYER_ON(_RNUM))
            layer_on(_LMOD);
        if (IS_LAYER_ON(_LNUM))
            layer_on(_RMOD);
        register_code(om_keycodes[keycode - SAFE_RANGE]); // Hold modifier
        ++om_count; // Remember that one mod key is being held
        return false;
    }

    // if (!capsword) {
    //     if (keycode == CAPSWRD && record->event.pressed) {
    //         capsword = true;
    //         register_code(KC_LSFT);
    //     }
    // } else if (record->event.pressed) {
    //     switch (keycode) {
    //     case HU_1:
    //     case HU_2:
    //     case HU_3:
    //     case HU_4:
    //     case HU_5:
    //     case HU_6:
    //     case HU_7:
    //     case HU_8:
    //     case HU_9:
    //     case HU_0:
    //     case HU_A:
    //     case HU_B:
    //     case HU_C:
    //     case HU_D:
    //     case HU_E:
    //     case HU_F:
    //     case HU_G:
    //     case HU_H:
    //     case HU_I:
    //     case HU_J:
    //     case HU_K:
    //     case HU_L:
    //     case HU_M:
    //     case HU_N:
    //     case HU_O:
    //     case HU_P:
    //     case HU_Q:
    //     case HU_R:
    //     case HU_S:
    //     case HU_T:
    //     case HU_U:
    //     case HU_V:
    //     case HU_W:
    //     case HU_X:
    //     case HU_Y:
    //     case HU_Z:
    //     case HU_AACU:
    //     case HU_EACU:
    //     case HU_OACU:
    //     case HU_ODIA:
    //     case HU_ODAC:
    //     case HU_UACU:
    //     case HU_UDIA:
    //     case HU_UDAC:

    //     case HU_MINS:
    //     case HU_UNDS:

    //     case 20738: // RSYM
    //     case 20739: // LSYM
    //     case 20740: // RNUM
    //     case 20741: // LNUM
    //     case KC_LSFT:
    //     case KC_RSFT:
    //         break;
    //     default:
    //         capsword = false;
    //         unregister_code(KC_LSFT);
    //     }
    // } else if (
    //     !record->event.pressed
    //     && (keycode == KC_LSFT || keycode == KC_RSFT)
    // ) {
    //     return false;
    // }

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
    static const char PROGMEM ABS_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0};
    oled_write_P(ABS_logo, false);
}

void render_layer_state(void) {
    if (IS_LAYER_ON(_QWERTZ))
        oled_write_ln_P(PSTR(" BASE"), false);
    else if (IS_LAYER_ON(_NAVIGATION))
        oled_write_ln_P(PSTR(" NAV "), false);
    else if (IS_LAYER_ON(_ADJUST))
        oled_write_ln_P(PSTR(" ADJ "), false);
    else if (IS_LAYER_ON(_LNUM))
        oled_write_ln_P(PSTR(" LNUM"), false);
    else if (IS_LAYER_ON(_RNUM))
        oled_write_ln_P(PSTR(" RNUM"), false);
    else if (IS_LAYER_ON(_RSYM))
        oled_write_ln_P(PSTR(" RSYM"), false);
    else if (IS_LAYER_ON(_LSYM))
        oled_write_ln_P(PSTR(" LSYM"), false);
    else
        oled_write_ln_P(PSTR("     "), false);
}

void render_mod_layer_state(void) {
    if (IS_LAYER_ON(_LMOD))
        oled_write_ln_P(PSTR(" LMOD"), false);
    else if (IS_LAYER_ON(_RMOD))
        oled_write_ln_P(PSTR(" RMOD"), false);
    else
        oled_write_ln_P(PSTR("     "), false);
}

void render_status_main(void) {
    // static char kc_txt[6];
    // snprintf(kc_txt, 5, "%d", debug_kc);
    render_space();
    render_logo();
    render_space();
    render_space();
    render_space();
    render_layer_state();
    render_mod_layer_state();
    render_space();
    // oled_write_ln(kc_txt, false);
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void render_status_secondary(void) {
    render_space();
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
