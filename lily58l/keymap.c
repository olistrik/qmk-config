/* Copyright 2017 F_YUUCHI
 * Copyright 2020 Drashna Jaelre <@drashna>
 * Copyright 2020 Ben Roesner (keycapsss.com)
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

#include QMK_KEYBOARD_H
#include "split_util.h"

#include "luna.h"
#include "oled.h"
#include "state.h"
#include "tetris.h"

#define _QWERTY 0
#define _LOWER 2
#define _RAISE 3
#define _FUNC 4

#define XXXXXXXX XXXXXXX
#define ________ _______
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#define FN_TAB LT(_FUNC, KC_TAB)
#define FN_LOW LT(_LOWER, KC_LEFT)
#define FN_RAZ LT(_RAISE, KC_RIGHT)
#define FN_LOW2 LT(_LOWER, KC_DOWN)
#define FN_RAZ2 LT(_RAISE, KC_UP)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
      ________,________,________,________,________,________,                 ________,________,________,________,________,________,
      FN_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,                 KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSPC ,
      KC_LSFT ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                 KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
      KC_LCTRL,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,________,________,KC_N   ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_ESC  ,
                                 ________,KC_LGUI ,FN_LOW  ,KC_ENT  ,KC_SPC  ,FN_RAZ ,KC_RALT ,________
    ),
    [_LOWER] = LAYOUT(
      ________,________,________,________,________,________,                  ________,________,________,________,________,________,
      KC_TILDE,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,                  KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_RPRN ,KC_BSPC ,
      KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                  ________,KC_UNDS ,KC_PLUS ,KC_LCBR ,KC_RCBR ,KC_PIPE ,
      KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,________,________,________,________,________,________,________,________,
                                 ________,________,________,________,________,FN_RAZ2 ,________,________
    ),
    [_RAISE] = LAYOUT(
      ________,________,________,________,________,________,                  ________,________,________,________,________,________,
      KC_GRAVE,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                  KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_BSPC ,
      KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                  ________,KC_MINUS,KC_EQUAL,KC_LBRC ,KC_RBRC ,KC_BSLS ,
      KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,________,________,________,________,________,________,________,________,
                                 ________,________,FN_LOW2 ,________,________,________,________,________
    ),
    [_FUNC] = LAYOUT(
      ________,________,________,________,________,________,                  ________,________,________,________,________,________,
      ________,________,________,________,________,________,                  ________,________,________,________,________,KC_DEL  ,
      ________,________,________,________,________,________,                  KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT,________,________,
      ________,________,________,________,________,________,________,________,________,________,________,________,________,________,
                                 ________,________,________,________,________,________,________,________
    ),
};

// Rotary encoder related code
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {            // Encoder on master side
    if (IS_LAYER_ON(_RAISE)) { // on Raise layer
      // Cursor control
      if (clockwise) {
        tap_code(KC_MNXT);
      } else {
        tap_code(KC_MPRV);
      }
    } else {
#ifdef TETRIS_ENABLE
      if (tetris_mode()) {
        if (clockwise) {
          tetris_record_key(TET_R, true);
        } else {
          tetris_record_key(TET_L, true);
        }
        return true;
      }
#endif

      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
    }
  } else if (index == 1) {     // Encoder on slave side
    if (IS_LAYER_ON(_LOWER)) { // on Lower layer
      //
      if (clockwise) {
        tap_code(KC_RIGHT);
      } else {
        tap_code(KC_LEFT);
      }
    } else {
      if (clockwise) {
        tap_code(KC_DOWN);
      } else {
        tap_code(KC_UP);
      }
    }
  }
  return true;
}
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
#ifdef TETRIS_ENABLE
  if (tetris_mode()) {
    tetris_tick();
    return false;
  }
#endif

  oled_tick();
  return false;
}
#endif
