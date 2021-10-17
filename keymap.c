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
#include "features/oled.h"

enum layers {
    _QWERTZ,

    _NAVIGATION,

    _RSYM,
    _LSYM,

    _NVKP,

    _ADJUST,
    
    _LMOD,
    _RMOD,

    _WASD
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
#define LAY_ASD TO(_WASD)

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
 * │   ⇧  ┃   A  ┃   S  ┃   D  ┃   F  ┃   G  │ Scl↕        Vol↕ │   H  ┃   J  ┃   K  ┃   L  ┃BackSp┃   ⇧  │
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
 * │      │      │Insert│      │      │ WASD │                  │      │      │  MMB │PauBrk│      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │ PgUp │ Home │  Up  │ End  │      │                  │      │  LMB │ M  ↑ │  RMB │  MB4 │CapsLk│
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │      ┃ PgDn ┃ Left ┃ Down ┃ Right┃      │ Wrd↔        Scl↔ │PrtScr┃ M  ← ┃ M  ↓ ┃ M  → ┃  MB5 ┃ ScrLk│
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │ Word←│ Word→│ Tab← │ Tab→ │ Tab  │╵  ⇧ ╵      ╵    ╵│      │ Left │ Down │  Up  │ Right│      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │      ╷      │    │[NAV] │      │      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */
[_NAVIGATION] = LAYOUT(
    _______, _______, KC_INS,  _______, _______, LAY_ASD,                     _______, _______, KC_BTN3, KC_PAUS, _______, _______,
    _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______,                     _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_BTN4, KC_CLCK,
    _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______,                     KC_PSCR, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5, KC_SLCK,
    _______, WRD_PRV, WRD_NXT, TAB_PRV, TAB_NXT, KC_TAB,   KC_LSFT, _______,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
                      _______, _______, _______, _______,  _______, _______,  _______, _______, _______, _______
),

/* RSYM(LMOD) + diaereses
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │  F12 │  F1  │  F2  │  F3  │  F4  │  F5  │                  │  F6  │  F7  │  F8  │  F9  │ F10  │ F11  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │                  │   $  │   Ü  │   !  │   Ö  │   +  │   -  │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤ Work-       RGB  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │      ┃   ◆  ┃   ⌥  ┃   ⎈  ┃   ⇧  ┃      │ spc↔        hue↔ │   "  ┃   (  ┃   )  ┃   ;  ┃Delete┃   _  │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │      │      │      │      │      │╵    ╵      ╵    ╵│   ~  │   {  │   }  │   %  │   *  │   :  │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │[RSYM]╷      │    │ Esc  │  ADJ │      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */
[_RSYM] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, _______, _______, _______,                   HU_DLR,  HU_UDIA, HU_EXLM, HU_ODIA, HU_PLUS, HU_MINS,
    _______, OM_LGUI, OM_LALT, OM_LCTL, OM_LSFT, _______,                   HU_DQUO, HU_LPRN, HU_RPRN, HU_SCLN, KC_DEL,  HU_UNDS,
    _______, _______, _______, _______, _______, _______, _______, _______, HU_TILD, HU_LCBR, HU_RCBR, HU_PERC, HU_ASTR, HU_COLN,
                      _______, _______, _______, _______, _______, _______, LAY_ADJ, _______, _______, _______
),

/* LSYM(RMOD) + acutes
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │  F12 │  F1  │  F2  │  F3  │  F4  │  F5  │                  │  F6  │  F7  │  F8  │  F9  │ F10  │ F11  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │   \  │   |  │   É  │   /  │   &  │                  │      │   Ú  │   Í  │   Ó  │      │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤ RGB              ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │   `  ┃   Á  ┃   =  ┃   [  ┃   ]  ┃   '  │ val↕        Tab↔ │      ┃   ⇧  ┃   ⎈  ┃   ⌥  ┃   ◆  ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │   °  │   ^  │   #  │   <  │   >  │   @  │╵    ╵      ╵    ╵│      │      │      │ AltGr│      │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │  ADJ ╷      │    │      │[LSYM]│      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */
[_LSYM] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, HU_BSLS, HU_PIPE, HU_EACU, HU_SLSH, HU_AMPR,                   _______, HU_UACU, HU_IACU, HU_OACU, _______, _______,
    HU_GRV,  HU_AACU, HU_EQL,  HU_LBRC, HU_RBRC, HU_QUOT,                   _______, OM_RSFT, OM_RCTL, OM_LALT, OM_RGUI, _______,
    HU_RNGA, HU_CIRC, HU_HASH, HU_LABK, HU_RABK, HU_AT,   _______, _______, _______, _______, _______, OM_RALT, _______, _______,
                      _______, _______, _______, LAY_ADJ, _______, _______, _______, _______, _______, _______
),

/* ADJUST (LMOD + RMOD) + double acutes
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │ RESET│      │      │      │      │      │                  │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │RGB ON│ HUE+ │ SAT+ │ VAL+ │ BRI- │      │                  │      │   Ű  │ Play │   Ő  │      │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤ RGB              ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │ MODE ┃ HUE- ┃ SAT- ┃ VAL- ┃ BRI+ ┃      │ Spd↕             │      ┃ Prev ┃ VOL- ┃ VOL+ ┃ Next ┃      │
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
 * │      │      │Insert│      │      │      │                  │      │ NumLk│ KP / │ KP * │ KP - │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │ PgUp │ Home │  Up  │ End  │Delete│                  │      │ KP 4 │ KP 5 │ KP 6 │ KP + │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │      ┃ PgDn ┃ Left ┃ Down ┃ Right┃   ⏎  │ Wrd↔        Scl↔ │ KP . ┃ KP 1 ┃ KP 2 ┃ KP 3 ┃ KP 0 ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │ Word←│ Word→│ Tab← │ Tab→ │ Tab  │╵  ⇧ ╵      ╵    ╵│      │ KP 7 │ KP 8 │ KP 9 │ KP ⏎ │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │[NVKP]│      ╷      │    │      │      │[NVKP]│      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */
[_NVKP] = LAYOUT(
    _______, _______, KC_INS,  _______, _______, _______,                   _______, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, _______,
    _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,                    _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______,
    _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_ENT,                    KC_PDOT, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_0, _______,
    _______, WRD_PRV, WRD_NXT, TAB_PRV, TAB_NXT, KC_TAB,  KC_LSFT, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_PENT, _______,
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
),

/* WASD
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                  ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │ BASE │                  │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┤                  ├──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │   W  │      │      │                  │      │      │  Up  │      │      │      │
 * ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤                  ├──────╆━━━━━━╈━━━━━━╈━━━━━━╈━━━━━━╅──────┤
 * │      ┃      ┃   A  ┃   S  ┃   D  ┃      │                  │      ┃ Left ┃ Down ┃ Right┃      ┃      │
 * ├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤╭┄┄┄┄╮      ╭┄┄┄┄╮├──────╄━━━━━━╇━━━━━━╇━━━━━━╇━━━━━━╃──────┤
 * │      │      │      │      │      │      │╵    ╵      ╵    ╵│      │      │      │      │      │      │
 * └──────┴──────┼──────┼──────┼──────┼──────┘╶─────┐    ┌─────╴└──────┼──────┼──────┼──────┼──────┴──────┘
 *               │      │      │      │      ╷      │    │      │      │      │      │      │
 *               └──────┴──────┴──────┘╶─────┴──────┘    └──────┴─────╴└──────┴──────┴──────┘
 */
[_WASD] = LAYOUT(
    _______, _______, _______, _______, _______, LAY_BAS,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, HU_W,    _______, _______,                   _______, _______, KC_UP,   _______, _______, _______,
    _______, _______, HU_A,    HU_S,    HU_D,    _______,                   _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

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

#ifdef OLED_DRIVER_ENABLE
void suspend_power_down_user() {
    oled_off();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_270;
    }
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        char layerStates = {
            IS_LAYER_ON(_NAVIGATION)  |
            IS_LAYER_ON(_ADJUST) << 1 |
            IS_LAYER_ON(_NVKP)   << 2 |
            IS_LAYER_ON(_RSYM)   << 3 |
            IS_LAYER_ON(_LSYM)   << 4 |
            IS_LAYER_ON(_RMOD)   << 5 |
            IS_LAYER_ON(_LMOD)   << 6 |
            IS_LAYER_ON(_WASD)   << 7
        };
        render_status_primary(layerStates);  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}
#endif // OLED_DRIVER_ENABLE

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // Left encoder
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _QWERTZ:
                // Mouse scroll Up/Down
                if (clockwise) tap_code(KC_WH_U); else tap_code(KC_WH_D);
                break;

            case _NAVIGATION:
            case _NVKP:
                // Scroll by Word
                if (clockwise) tap_code16(LCTL(KC_LEFT)); else tap_code16(LCTL(KC_RGHT));
                break;


            // Right thumb key
            case _LSYM:
            case _RMOD:
                // Switch workspace
                if (clockwise) {
                    tap_code16(LCTL(LGUI(KC_LEFT)));
                } else {
                    tap_code16(LCTL(LGUI(KC_RIGHT)));
                }
                break;

            // Left thumb key
            case _RSYM:
            case _LMOD:
                // RGB brightness ↕
                if (clockwise) rgblight_decrease_val(); else rgblight_increase_val();
                break;
            
            case _ADJUST:
                // RGB speed ↕
                if (clockwise) rgblight_decrease_speed(); else rgblight_increase_speed();
                break;
        }
    }
    // Right encoder
    else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _QWERTZ:
                // Volume Up/Down
                if (clockwise) tap_code(KC_VOLU); else tap_code(KC_VOLD);
                break;

            case _NAVIGATION:
            case _NVKP:
                // Mouse scroll ↔
                if (clockwise) tap_code(KC_WH_R); else tap_code(KC_WH_L);
                break;

            // Left thumb key
            case _RSYM:
            case _LMOD:
                // Switch tab
                if (clockwise) tap_code16(LCTL(KC_TAB)); else tap_code16(LSFT(LCTL(KC_TAB)));
                break;

            // Right thumb key
            case _LSYM:
            case _RMOD:
                // RGB hue ↕
                if (clockwise) rgblight_increase_hue(); else rgblight_decrease_hue();
                break;
        }
    }
    return true;
}
#endif // ENCODER_ENABLE
