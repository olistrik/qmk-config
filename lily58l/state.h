#pragma once

enum layers {
  _QWERTY,
  _SINGLE,
  _LOWER,
  _RAISE,
  _ADJUST,
  _FUNC,
};

layer_state_t layer_state_set_user(layer_state_t state);
