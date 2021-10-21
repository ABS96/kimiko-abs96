#include "decolayer.h"

static enum decolayer_state decolayer_state = DECO_OFF;

void deco_off(void) {
  decolayer_state = DECO_OFF;
}

void deco_on(enum decolayer_state selected) {
  if (decolayer_state == selected)
    deco_off();
  else
    decolayer_state = selected;
}

enum decolayer_state get_deco_state(void) {
  return decolayer_state;
}

// MSB [1 byte offset | 3 bytes codepoint] LSB
// offset = codepoint("a") - codepoint("A")
const uint32_t PROGMEM offsets_and_codepoints[] = {
  [DECO_OFF]       = 0x00000000,
  [DECO_FULLWIDTH] = 0x2000FF21,
  [DECO_MATHBOLD]  = 0x1A01D400,
  [DECO_SANS]      = 0x1A01D5A0,
  [DECO_SANSBOLD]  = 0x1A01D5D4,
  [DECO_SANSITAL]  = 0x1A01D608,
  [DECO_SANSBOIT]  = 0x1A01D63C
};

uint8_t get_hex_digit_kc(uint8_t digit) {
  switch (digit) {
    case 0:
      return HU_0;
    case 1 ... 9:
      return 0x1D + digit;
    case 10:
      return KC_A;
    case 11:
      return KC_B;
    case 12:
      return KC_C;
    case 13:
      return KC_D;
    case 14:
      return KC_E;
    case 15:
      return KC_F;
    default:
      return KC_R;
  }
}

void tap_unicode_number(uint32_t number) {
  int magnitude = -1;
  uint32_t shiftee = number;
  // Check how many characters the number takes to write
  while (shiftee) {
    shiftee >>= 4;
    ++magnitude;
  }
  // Type each hex digit
  for (; magnitude >= 0; --magnitude) {
    uint8_t digit = ((number >> (magnitude * 4)) & 0x0F);
    tap_code(get_hex_digit_kc(digit));
  }
}

// WinCompose implementation (see Unicode @ QMK Docs for other platforms)
void compose_unicode(uint32_t number) {
  uint8_t saved_mods = get_mods();
  clear_mods();

  // Type [Compose] [u] [x] ... [x]  [Enter]
  tap_code(KC_RALT);
  tap_code(KC_U);
  tap_unicode_number(number);
  tap_code(KC_ENTER);

  set_mods(saved_mods);
}

void compose_letter(uint32_t offset_and_cp, uint16_t keycode) {
  bool capital = (get_mods() & MOD_MASK_SHIFT) || host_keyboard_led_state().caps_lock;
  // QWERTZ correction
  if (keycode >= KC_Y) {
    keycode = keycode == KC_Z ? KC_Y : KC_Z;
  }
  // Start from "A" in the selected alphabet, go to the current letter, and add ("a" - "A") if capital
  // See offsets_and_codepoints
  compose_unicode(
    (offset_and_cp & 0x00FFFFFF)
    + keycode - KC_A
    + (capital ? 0 : offset_and_cp >> 24)
  );
}

// Change a letter with diacritics to one without, return the unicode number of its diacritic
uint16_t handle_hungarian_accents(uint16_t* keycode) {
  switch (*keycode) {
    case HU_AACU:
      *keycode = KC_A;
      return 0x0301;
    case HU_EACU:
      *keycode = KC_E;
      return 0x0301;
    case HU_IACU:
      *keycode = KC_I;
      return 0x0301;
    case HU_OACU:
      *keycode = KC_O;
      return 0x0301;
    case HU_UACU:
      *keycode = KC_U;
      return 0x0301;
    case HU_ODIA:
      *keycode = KC_O;
      return 0x0308;
    case HU_UDIA:
      *keycode = KC_U;
      return 0x0308;
    case HU_ODAC:
      *keycode = KC_O;
      return 0x030B;
    case HU_UDAC:
      *keycode = KC_U;
      return 0x030B;
    default:
      return 0;
  }
}

bool process_decolayer(uint16_t keycode, const keyrecord_t *record) {
  if (get_deco_state() != DECO_OFF && record->event.pressed) {
    // Ignore mods and special keys
    if (
      ((get_mods() | get_oneshot_mods()) & (MOD_MASK_CAG)) ||
      (QK_LAYER_TAP <= keycode && keycode <= QK_ONE_SHOT_LAYER_MAX)
    )
      return true;

    uint16_t accent = handle_hungarian_accents(&keycode);

    switch (get_deco_state()) {
      case DECO_FULLWIDTH:
        switch (keycode) {
          case KC_A ... KC_Z:
            compose_letter(offsets_and_codepoints[DECO_FULLWIDTH], keycode);
            return false;
          case HU_0:
            compose_unicode(0xFF10);
            return false;
          case HU_1 ... HU_9:
            compose_unicode(0xFEF3 + keycode);
            return false;
          case KC_SPACE:
            compose_unicode(0x3000);
            return false;
        }
        break;

      case DECO_MATHBOLD: 
      case DECO_SANS:
      case DECO_SANSBOLD:
      case DECO_SANSITAL:
      case DECO_SANSBOIT:
        switch (keycode) {
          case KC_A ... KC_Z:
            // Since offsets_and_codepoints is stored in PROGMEM, it can only be accessed by pgm_read_dword_near()
            compose_letter(
              pgm_read_dword_near(offsets_and_codepoints + get_deco_state()),
              keycode
            );
            if (accent)
              compose_unicode(accent);
            return false;
        }
        break;

      default:
        break;
    }
  }
  return true;
}
