#pragma once
#include QMK_KEYBOARD_H
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define BLOCK_SIZE 3
#define BLOCK_COUNT 7
#define LEVEL_CAP 15
#define MS_FRAME 50
#define STAGE_LENGTH 10
#define BLINK_COUNT 8
#define BLINK_SPEED 100

enum tetris_keycodes {
  TETRIS = SAFE_RANGE,
  TET_L,
  TET_R,
  TET_D,
  TET_RF,
  TET_RR,
  TET_H,
};

bool tetris_mode(void);
uint16_t tetris_score(void);

// State change
void tetris_new(void);
void tetris_quit(void);

// logic
void tetris_tick(void);
bool tetris_record_key(uint16_t keycode, bool pressed);
