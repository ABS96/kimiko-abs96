#include "oled.h"
#include "capsword.h"
#include "decolayer.h"

// Split communication

uint8_t sync_data = 0;

void user_sync_display_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
  const master_to_slave_t *m2s = (const master_to_slave_t*)in_data;
  sync_data = m2s->m2s_data;
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
  bool gui_on = (mod4 & 0b00001000) == 0b00001000;

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

void render_layer_state(char layerStates) {
  static const char PROGMEM sym_top[] = {0x86, 0x87, 0x88, 0};
  static const char PROGMEM sym_bot[] = {0xA6, 0xA7, 0xA8, 0};

  static const char PROGMEM nav_top[] = {0x89, 0x8A, 0x8B, 0};
  static const char PROGMEM nav_bot[] = {0xA9, 0xAA, 0xAB, 0};

  static const char PROGMEM nkp_top[] = {0x8C, 0x8D, 0x8E, 0};
  static const char PROGMEM nkp_bot[] = {0xAC, 0xAD, 0x8E, 0};

  static const char PROGMEM adj_top[] = {0x20, 0x8F, 0x90, 0};
  static const char PROGMEM adj_bot[] = {0xAE, 0xAF, 0x20, 0};


  if (layerStates & 0x01) { // _NAVIGATION
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(nav_top, false);
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(nav_bot, false);
  }
  else if (layerStates >> 1 & 0x01) { // ADJUST
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(adj_top, false);
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(adj_bot, false);
  }
  else if (layerStates >> 2 & 0x01) { // NVKP
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(nkp_top, false);
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(nkp_bot, false);
  }
  else if (layerStates >> 3 & 0x01) { // RSYM
    oled_write_P(PSTR(" "), false);
    oled_write_P(sym_top, false);
    oled_write_P(PSTR("\x85 "), false);
    oled_write_P(sym_bot, false);
    oled_write_P(PSTR("\xA5"), false);
  }
  else if (layerStates >> 4 & 0x01) { // LSYM
    oled_write_P(PSTR("\x80"), false);
    oled_write_P(sym_top, false);
    oled_write_P(PSTR(" \xD4"), false);
    oled_write_ln_P(sym_bot, false);
  }
  else if (layerStates >> 7 & 0x01) { // WASD
    oled_write_char(7, false);
    oled_write_P(PSTR("WASD"), false);
    render_space();
  }
  else {
    render_space();
    render_space();
  }
}

void render_mod_layer_state(char layerStates) {
  if (layerStates >> 6 & 0x01) // LMOD
    oled_write_P(PSTR("\x1BMOD "), false);
  else if (layerStates >> 5 & 0x01) // RMOD
    oled_write_P(PSTR(" MOD\x1A"), false);
  else
    render_space();
}

void render_lock_state(led_t led_union) {
  if (led_union.compose) {
    oled_write_char(7, false);
    oled_write_P(PSTR("CMPS"), false);
  }
  else
    render_space();

  if (led_union.num_lock) {
    oled_write_char(7, false);
    oled_write_P(PSTR("NUM "), false);
  } else
    render_space();

  if (led_union.caps_lock) {
    oled_write_char(7, false);
    if (capsword_enabled())
      oled_write_P(PSTR("CWRD"), false);
    else
      oled_write_P(PSTR("CAPS"), false);
  } else
    render_space();

  if (led_union.scroll_lock) {
    oled_write_char(7, false);
    oled_write_P(PSTR("SCRL"), false);
  } else
    render_space();
}

void render_deco_layer_state(void) {
  switch(get_deco_state()) {
    case DECO_FULLWIDTH:
      oled_write_P(PSTR("FullW"), false);
      break;
    case DECO_MATHBOLD:
      oled_write_P(PSTR("MthBo"), false);
      break;
    case DECO_SANS:
      oled_write_P(PSTR("SansS"), false);
      break;
    case DECO_SANSBOLD:
      oled_write_P(PSTR("SansB"), false);
      break;
    case DECO_SANSITAL:
      oled_write_P(PSTR("SansI"), false);
      break;
    case DECO_SANSBOIT:
      oled_write_P(PSTR("SnsBI"), false);
      break;
    default:
      render_space();
      break;
  }
}

void render_status_primary(char layerStates) {
  render_logo(); // 3
  render_space();
  render_deco_layer_state();
  render_layer_state(layerStates); // 2
  render_mod_layer_state(layerStates); // 1
  render_modifiers(get_mods() | get_oneshot_mods()); // 4
  render_lock_state(host_keyboard_led_state()); // 3
}

void render_status_secondary(void) {
    const char test_data = '0' + sync_data;
    render_logo();
    oled_write(&test_data, false);
}
