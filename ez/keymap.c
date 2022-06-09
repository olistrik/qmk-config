/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"


enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
	_FUNC
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define FN_TAB LT(_FUNC, KC_TAB)
#define FN_LOW LT(_LOWER, KC_LEFT)
#define FN_RAZ LT(_RAISE, KC_RIGHT)
#define FN_LOW2 LT(_LOWER, KC_DOWN)
#define FN_RAZ2 LT(_RAISE, KC_UP)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |      | Alt  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
		KC_ESC  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_BSPC ,
		FN_TAB  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
		KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_ENT  ,
		KC_LCTL ,KC_LGUI ,KC_NO   ,KC_LALT ,LOWER   ,KC_SPC  ,KC_NO   ,RAISE   ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Play | Vol- | Vol+ | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
		KC_TILD ,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_RPRN ,KC_BSPC ,
		KC_DEL  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_UNDS ,KC_PLUS ,KC_LCBR ,KC_RCBR ,KC_PIPE ,
		_______ ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,_______ ,_______ ,KC_HOME ,KC_END  ,_______ ,
		_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_NO   ,_______ ,KC_MNXT ,KC_VOLD ,KC_VOLU ,KC_MPLY ),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      | Vol- |Pg Dn |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
		KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,_______ ,
		KC_DEL  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,KC_MINS ,KC_EQL  ,KC_LBRC ,KC_RBRC ,KC_BSLS ,
		_______ ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,_______ ,_______ ,_______ ,_______ ,_______ ,
		_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_NO   ,_______ ,_______ ,KC_PGDN ,KC_PGUP ,_______ ),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      | Reset|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______,_______ ,_______ ,_______ ,RGB_TOG ,TERM_ON ,TERM_OFF,_______ ,_______ ,_______ ,_______ ,_______ ,
    _______,AU_TOG  ,MU_TOG  ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,RESET   ,
    _______,CK_TOGG ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
    _______,_______ ,_______ ,_______ ,_______ ,_______ ,KC_NO   ,_______ ,_______ ,_______ ,_______ ,_______ ),

/* Legacy FN
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNC] = LAYOUT_planck_grid(
		BACKLIT ,KC_BTN2 ,KC_MS_U ,KC_BTN1 ,KC_WH_U ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_PSCR ,KC_DEL  ,
		_______ ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D ,_______ ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,_______ ,_______ ,
		_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
		_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_NO   ,_______ ,_______ ,_______ ,_______ ,_______ ),

};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

#define COLOR_0 {146,244,255}
#define COLOR_1 {16,255,255}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [_QWERTY] = {
      COLOR_1 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_1 ,
      COLOR_1 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_1 ,
      COLOR_1 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_1 ,
      COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_0          ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 },

    [_LOWER] = {
      COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_0 ,
      COLOR_1 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,
      COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_1 ,COLOR_1 ,COLOR_0 ,
      COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_1 ,COLOR_0          ,COLOR_0 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 },

    [_RAISE] = {
      COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_0 ,
      COLOR_1 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,
      COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,
      COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0          ,COLOR_0 ,COLOR_0 ,COLOR_1 ,COLOR_1 ,COLOR_0 },

    [_ADJUST] = {
      COLOR_0 ,COLOR_1 ,COLOR_1 ,COLOR_0 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,
      COLOR_0 ,COLOR_1 ,COLOR_1 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,
      COLOR_0 ,COLOR_1 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,
      COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0          ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 },

    [_FUNC] = {
      COLOR_0 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_1 ,COLOR_1 ,
      COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_0 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_1 ,COLOR_0 ,COLOR_0 ,
      COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,
      COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0          ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 ,COLOR_0 },
};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

#ifdef AUDIO_ENABLE
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            // static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                // if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                // if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            // play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
