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
#include "tetris.h"
#include "luna.h"

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
		KC_LCTRL,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_MPLY ,  KC_MPLY ,KC_N   ,KC_M    ,KC_COMM ,KC_DOT  ,KC_SLSH ,KC_RSFT ,
								  KC_LGUI  ,KC_LALT ,FN_LOW  ,KC_SPC  ,  KC_SPC  ,FN_RAZ ,KC_BSPC ,KC_RGUI
	),
	/* SINGLE HALF
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    | NLCK |  P/  |  P*  |  P-  | ____ | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |FN_Tab|   Q  |   W  |   E  |   R  |   T  |                    |  P7  |  P8  |  P9  |  P+  | ____ | ____ |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|  P4  |  P5  |  P6  |  P+  | ____ | ____ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LCtrl |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|  P1  |  P2  |  P3  | PEnt | ____ | ____ |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |Lower | /Space  /       \  P0  \ | ____ | ____ |  P.  |
 *                   `-----------------------------'         '------''--------------------'
 */

	[_SINGLE] = LAYOUT(
		KC_ESC  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                    KC_NLCK ,KC_PSLS ,KC_PAST ,KC_PMNS ,XXXXXXX ,KC_BSPC ,
		FN_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,                    KC_P7   ,KC_P8   ,KC_P9   ,KC_PPLS ,XXXXXXX ,XXXXXXX ,
		KC_LSFT ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,                    KC_P4   ,KC_P5   ,KC_P6   ,KC_PPLS ,XXXXXXX ,XXXXXXX ,
		KC_LCTRL,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_MPLY ,  XXXXXXX ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PENT ,XXXXXXX ,XXXXXXX ,
								  KC_LGUI  ,KC_LALT ,FN_LOW  ,KC_SPC  ,  KC_P0   ,XXXXXXX ,XXXXXXX ,KC_PDOT
	),
	/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
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
		KC_TILDE,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,                    KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_RPRN ,________,
		KC_TILDE,KC_EXLM ,KC_AT   ,KC_HASH ,KC_DLR  ,KC_PERC ,                    KC_CIRC ,KC_AMPR ,KC_ASTR ,KC_LPRN ,KC_RPRN ,________,
		KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                    ________,KC_UNDS ,KC_PLUS ,KC_LCBR ,KC_RCBR ,KC_PIPE ,
		KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,________,  ________,________,________,________,________,________,________,
								   ________,________,________,________,  ________,FN_RAZ2 ,________,________
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
		KC_GRAVE,________,________,________,________,________,                    ________,________,________,________,________,________,
		KC_GRAVE,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                    KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,________,
		KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6   ,                    ________,KC_MINUS,KC_EQUAL,KC_LBRC ,KC_RBRC ,KC_BSLS ,
		KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12  ,________,  ________,________,________,________,________,________,________,
								   ________,________,FN_LOW2 ,________,  ________,________,________,________
	),

	/* FUNC
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |Tetris|                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |Lower | /Space  /       \Space \ |Raise | Bksp | RGUI |
 *                   `-----------------------------'         '------''--------------------'
 */

	[_FUNC] = LAYOUT(
		________,________,________,________,________,________,                    ________,________,________,________,________,KC_DEL  ,
		________,________,________,________,________,TETRIS  ,                    ________,________,________,________,________,________,
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

bool set_single = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (!set_single) {
		if (!is_transport_connected()) {
			layer_move(_SINGLE);
		}
		set_single = true;
	}
#ifdef TETRIS_ENABLE
	if (tetris_mode() || keycode == TETRIS) {
		switch(keycode) {
			case KC_A:
				keycode = TET_L;
				break;
			case KC_D:
				keycode = TET_R;
				break;
			case KC_S:
				keycode = TET_D;
				break;
			case KC_E:
				keycode = TET_RF;
				break;
			case KC_Q:
				keycode = TET_RR;
				break;
			case KC_SPC:
				keycode = TET_H;
				break;
		}

		tetris_record_key(keycode, record->event.pressed);
		return false;
	}
#endif
#ifdef LUNA_ENABLE
	switch(keycode) {
		case KC_LCTRL:	
		case KC_RCTRL:	
			setSneaking(record->event.pressed);
			return true;
		case KC_SPC:	
			setJumping(record->event.pressed);
			return true;
		default:
			break;
	}
#endif

	switch(keycode) {
		case LT(_FUNC, KC_TAB):
			// if(is_transport_connected()) {
			if (true) {
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


#ifdef OLED_ENABLE
bool oled_task_user(void) {
#ifdef TETRIS_ENABLE
	if(tetris_mode()) {
		tetris_tick();
		return false;
	}
#endif

	oled_tick();
	return false;
}
#endif
