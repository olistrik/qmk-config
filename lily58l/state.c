#include QMK_KEYBOARD_H
#include "action_layer.h"

#include "state.h"

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}
