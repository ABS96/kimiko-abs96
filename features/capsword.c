#include "capsword.h"

static bool capsword_active = false;
static int8_t distance_to_delimiter = -1;

bool capsword_enabled(void) {
  return capsword_active;
}

void capsword_on(void) {
  capsword_active = true;
  if (!host_keyboard_led_state().caps_lock) {
    tap_code(KC_CAPS);
    distance_to_delimiter = -1;
  }
}

void capsword_off(void) {
  capsword_active = false;
  if (host_keyboard_led_state().caps_lock) {
    tap_code(KC_CAPS);
  }
}

void capsword_toggle(void) {
  if (capsword_enabled())
    capsword_off();
  else
    capsword_on();
}

bool should_capsword_terminate(uint16_t keycode, const keyrecord_t *record) {
  switch (keycode) {
    case HU_0:
    case HU_1 ... HU_9:
    case KC_KP_1 ... KC_KP_0:
    case KC_A ... KC_Z:
    case HU_AACU:
    case HU_EACU:
    case HU_IACU:
    case HU_OACU:
    case HU_ODIA:
    case HU_ODAC:
    case HU_UACU:
    case HU_UDIA:
    case HU_UDAC:
    case HU_MINS:
    case HU_UNDS:
    case KC_BSPC:
      break;
    default:
      if (record->event.pressed)
        return true;
  }
  return false;
}

bool process_capsword(uint16_t keycode, const keyrecord_t *record) {
  if (capsword_enabled()) {
    // Ignore (pass through) special keys
    if (QK_LAYER_TAP <= keycode && keycode <= QK_ONE_SHOT_LAYER_MAX)
      return true;

    // Handle double space to escape
    if (record->event.pressed) {
      if (keycode == KC_SPACE) {
        if (distance_to_delimiter == 0) {
          capsword_off();
          tap_code16(KC_BSPC);
          tap_code16(KC_SPACE);
          return false;
        }
        else {
          distance_to_delimiter = 0;
          tap_code16(HU_UNDS);
          return false;
        }
      } else if (keycode == KC_BSPC) {
        --distance_to_delimiter;
      } else {
        ++distance_to_delimiter;
      }

      if (should_capsword_terminate(keycode, record)) {
        capsword_off();
      }
    }
  }
  return true;
}