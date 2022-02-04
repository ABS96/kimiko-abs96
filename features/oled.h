#pragma once
#include QMK_KEYBOARD_H

typedef struct _master_to_slave_t
{
  int m2s_data;
} master_to_slave_t;

void render_status_primary(char layerStates);
void render_status_secondary(void);
void user_sync_display_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data);
