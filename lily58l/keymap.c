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

#include "oled.h"
#include "state.h"

/*
enum custom_keycodes {
  FN_TAB = SAFE_RANGE,
};
*/

#define XXXXXXXX XXXXXXX
#define ________ _______
#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

#define FN_TAB LT(_FUNC, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |FN_Tab|   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | '  " |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  | ;  : |Enter |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LCtrl |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  | ,  < | .  > | /  ? |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |Lower | /Space  /       \Space \ |Raise | Bksp | RGUI |
 *                   `-----------------------------'         '------''--------------------'
 */

[_QWERTY] = LAYOUT(
  KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                    KC_6   ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_BSPC ,
  FN_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,                    KC_Y   ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_QUOT ,
  KC_LSFT ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                    KC_H   ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_ENT  ,
  KC_LCTRL,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,________,  ________,KC_N   ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
                            KC_LGUI  ,KC_LALT ,LOWER   ,KC_SPC  ,  KC_SPC  ,RAISE  ,KC_BSPC ,KC_RGUI
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |   _  |   +  |   {  |   }  |   |  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |Lower | /Space  /       \Space \ |Raise | Bksp | RGUI |
 *                   `-----------------------------'         '------''--------------------'
 */
[_LOWER] = LAYOUT(
  ________,________,________,________,________,________,                    ________,________,________,________,________,________,
  KC_TILDE,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,                    KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_RPRN ,________,
  ________,________,________,________,________,________,                    ________,KC_UNDS ,KC_PLUS ,KC_LCBR ,KC_RCBR ,KC_PIPE ,
  ________,________,________,________,________,________,________,  ________,________,________,________,________,________,________,
                             ________,________,________,________,  ________,________,________,________
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |      |      |      |      |      |                    |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |   -  |   =  |   [  |    ] |   \  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |Lower | /Space  /       \Space \ |Raise | Bksp | RGUI |
 *                   `-----------------------------'         '------''--------------------'
 */

[_RAISE] = LAYOUT(
  ________,________,________,________,________,________,                    ________,________,________,________,________,________,
  ________,________,________,________,________,________,                    ________,________,________,________,________,________,
  ________,________,________,________,________,________,                    ________,KC_MINUS,KC_EQUAL,KC_LBRC ,KC_RBRC ,KC_BSLS ,
  ________,________,________,________,________,________,________,  ________,________,________,________,________,________,________,
                             ________,________,________,________,  ________,________,________,________
),

/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |Lower | /Space  /       \Space \ |Raise | Bksp | RGUI |
 *                   `-----------------------------'         '------''--------------------'
 */

[_FUNC] = LAYOUT(
  ________,________,________,________,________,________,                    ________,________,________,________,________,________,
  ________,________,________,________,________,________,                    ________,________,________,________,________,________,
  ________,________,________,________,________,________,                    KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RIGHT,________,________,
  ________,________,________,________,________,________,________,  ________,________,________,________,________,________,________,
                             ________,________,________,________,  ________,________,________,________
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_ADJUST] = LAYOUT(
  XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,                    XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,
  XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,                    XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,
  XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,                    XXXXXXXX,XXXXXXXX,RGB_TOG ,RGB_HUI ,RGB_SAI ,RGB_VAI ,
  XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,XXXXXXXX,  XXXXXXXX,XXXXXXXX,XXXXXXXX,RGB_MOD ,RGB_HUD ,RGB_SAD ,RGB_VAD ,
                             ________,________,________,________,  ________, ________,________,________
)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef OLED_ENABLE
  if (record->event.pressed) {
    add_keylog(keycode);
  }
  #endif

  switch(keycode) {
    case LT(_FUNC, KC_TAB):
      if(is_transport_connected()) {
        return true;
      }
      if (record->event.pressed) {
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      return false;
    default:
      return true;
  }
}


// Rotary encoder related code
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { // Encoder on master side
    if(IS_LAYER_ON(_RAISE)) { // on Raise layer
      // Cursor control
      if (clockwise) {
        tap_code(KC_MNXT);
      } else {
        tap_code(KC_MPRV);
      }
    }
    else {
      if (clockwise) {
        tap_code(KC_VOLU);
      } else {
        tap_code(KC_VOLD);
      }
    }
  }
  else if (index == 1) { // Encoder on slave side
    if(IS_LAYER_ON(_LOWER)) { // on Lower layer
      //
      if (clockwise) {
        tap_code(KC_RIGHT);
      } else {
        tap_code(KC_LEFT);
      }
    }
    else {
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
