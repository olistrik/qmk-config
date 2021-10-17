#include <string.h>
#include QMK_KEYBOARD_H
#include "tetris.h"

typedef signed char sbyte;
typedef uint8_t ubyte;


#define BUFFER_SIZE 32
char str_buffer[BUFFER_SIZE];

uint16_t points_per_row[5] = {0, 40, 100, 300, 1200};
int timer = 0;

typedef struct Block {
  ubyte size; // the x & y dimension of the block mask.
  ubyte len; // size * size.
  bool shape[2][16]; // the 0 and 90 rot's of the block.
} Block;

typedef struct State {
  bool game_over;     // show gameover.
  bool playing;       // is tetris playing?
  bool drop;          // Is drop held?
  bool hold_swappable;// Can we swap the held block?
  ubyte blinking;     // blinks remaining
  uint16_t ms_tick;   // ms between frames.
  uint32_t score;
  ubyte level;
  ubyte lines;
  bool board[BOARD_HEIGHT*BOARD_WIDTH]; // flat board, rows appended.
  bool full_lines[BOARD_HEIGHT];        // is line at y full?
  Block *block; // the current block.
  Block *hold;  // the current held block.
  ubyte r;  // the rotation of the current block.
  sbyte x;  // the x of the current block (top left).
  sbyte y;  // the y of the current block (top left).
} State;


Block block_I = {
  .size = 4,
  .len = 16,
  .shape = {{0,0,0,0, 1,1,1,1, 0,0,0,0, 0,0,0,0},
            {0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0}},
};

Block block_L = {
  .size = 3,
  .len = 9,
  .shape = {{1,0,0, 1,1,1, 0,0,0},
            {0,1,1, 0,1,0, 0,1,0}},

};

Block block_J = {
  .size = 3,
  .len = 9,
  .shape = {{0,0,1, 1,1,1, 0,0,0},
            {0,1,0, 0,1,0, 0,1,1}},
};

Block block_O = {
  .size = 2,
  .len = 4,
  .shape = {{1,1, 1,1},
            {1,1, 1,1}},
};

Block block_S = {
  .size = 3,
  .len = 9,
  .shape = {{0,1,1, 1,1,0, 0,0,0},
            {0,1,0, 0,1,1, 0,0,1}},
};

Block block_T = {
  .size = 3,
  .len = 9,
  .shape = {{0,1,0, 1,1,1, 0,0,0},
            {0,1,0, 0,1,1, 0,1,0}},
};

Block block_Z = {
  .size = 3,
  .len = 9,
  .shape = {{1,1,0, 0,1,1, 0,0,0},
            {0,0,1, 0,1,1, 0,1,0}},
};

Block *blocks[] = {
  &block_O, // Block O must be first.
  &block_I,
  &block_J,
  &block_L,
  &block_S,
  &block_T,
  &block_Z,
};

State state = {
  .playing = false,
  .game_over = false,
  .drop = false,
  .hold_swappable = false,
  .blinking = 0,
  .score = 0,
  .ms_tick = 0,
  .level = 0,
  .lines = 0,
  .board = {0},
  .full_lines = {0},
  .block = NULL,
  .hold = NULL,
  .x = 0,
  .y = 0,
  .r = 0,
};


uint8_t BOX_WIDTH = BLOCK_SIZE * BOARD_WIDTH + 2;
uint8_t BOX_HEIGHT = BLOCK_SIZE * BOARD_HEIGHT + 2;

bool block_board_mask(bool (*callback)(sbyte x, sbyte y, bool on), sbyte x, sbyte y, ubyte r, bool on);
void set_ms_tick(void);

// UTILITY

bool block_board_mask(bool (*callback)(sbyte x, sbyte y, bool on), sbyte x, sbyte y, ubyte r, bool on) {
  bool overlap = false; // used for collision detection.

  if (state.block == NULL) {
    return overlap;
  }

  bool vertical = r % 2; // rotation 1 or 270
  bool flipped = r / 2; // rotation > 90

  for (ubyte i = 0; i < state.block->size; i += 1) {
    for (ubyte j = 0; j < state.block->size; j += 1) {
      sbyte xx = x + i;
      sbyte yy = y + j;

      ubyte idx = j * state.block->size + i; // get index in flat image.

      if (flipped) { // 180 and 270: read array in reverse.
        idx = state.block->len - idx - 1;
      }

      if (state.block->shape[vertical][idx]) { // only write if masked.
        if ( xx < 0 || yy < 0 || xx > BOARD_WIDTH - 1 || yy > BOARD_HEIGHT - 1) {
          overlap = true;
          continue;
        }

        overlap |= (*callback)(xx, yy, on);
      }
    }
  }

  return overlap;
}

void set_ms_tick() {
  state.ms_tick = MS_FRAME * (LEVEL_CAP - state.level);
}

// RENDER

bool render_cube(sbyte x, sbyte y, bool on);
void render_line(ubyte y, bool on);
void render_checkers(void);
void render_block(bool on);
void render_hold(bool on);
void render_tetris_box(void);
bool render_row(ubyte y);
void render_stage(void);
void render_offset_cube(sbyte x, sbyte y, short ox, short oy, bool on);

void draw_block(void);
void clear_block(void);
void draw_hold(void);
void clear_hold(void);
void clear_line(void);

void render_offset_cube(sbyte x, sbyte y, short ox, short oy, bool on) {
  uint8_t xx = x * BLOCK_SIZE + 1;
  uint8_t yy = y * BLOCK_SIZE + 1;

  for (ubyte i = 0; i < BLOCK_SIZE; i += 1) {
    for (ubyte j = 0; j < BLOCK_SIZE; j+= 1) {
      oled_write_pixel(xx + ox + i, yy + oy + j, on);
    }
  }
}

bool render_cube(sbyte x, sbyte y, bool on) {
  render_offset_cube(x, y, 0, 0, on);
  return on;
}

void render_checkers() {
  for (ubyte i = 0; i < BOARD_WIDTH; i++) {
    for (ubyte j = 0; j < BOARD_HEIGHT; j++) {
      if ((i + j) % 2) {
        render_cube(i, j, true);
      }
    }
  }
}

void render_block(bool on) {
  block_board_mask(&render_cube, state.x, state.y, state.r, on);
}

void render_hold(bool on) {
  ubyte x = BOARD_WIDTH - state.hold->size;
  ubyte y = BOARD_HEIGHT + 1;



  for (ubyte i = 0; i < state.hold->size; i += 1) {
    for (ubyte j = 0; j < state.hold->size; j += 1) {
      sbyte xx = x + i;
      sbyte yy = y + j;

      ubyte idx = j * state.hold->size + i; // get index in flat image.

      if (state.hold->shape[0][idx]) { // only write if masked.
        render_offset_cube(xx, yy, -1, 0, on);
      }
    }
  }
}

void render_tetris_box() {
  for (ubyte i = 0; i < BOX_WIDTH; i += 1) {
    oled_write_pixel(i, 0, true);
    oled_write_pixel(i, BOX_HEIGHT - 1, true);
  }
  for (ubyte i = 1; i < BOX_HEIGHT - 1; i += 1) {
    oled_write_pixel(0, i, true);
    oled_write_pixel(BOX_WIDTH - 1, i, true);
  }
}

void draw_block() {
  render_block(true);
}

void draw_hold() {
  render_hold(true);
}

void clear_block() {
  render_block(false);
}

void clear_hold() {
  render_hold(false);
}

void render_line(ubyte y, bool on) {
  for(ubyte i = 0; i < BOARD_WIDTH; i++) {
    render_cube(i, y, on);
  }
}

bool render_row(ubyte y) {
  bool empty = true;
  uint16_t offset = y * BOARD_WIDTH;
  for(ubyte i = 0; i < BOARD_WIDTH; i++) {
    if (render_cube(i, y, state.board[offset + i])) {
      empty = false;
    }
  }
  return empty;
}

void render_stage() {
  oled_set_cursor(0, 8);
  if (state.level < 10) {
    oled_write("0", false);
    oled_set_cursor(1, 8);
  }
  oled_write(utoa(state.level, str_buffer, 10), false);
  oled_set_cursor(0, 9);
  oled_write(utoa(state.lines, str_buffer, 10), false);
  oled_set_cursor(0, 10);
  oled_write(utoa(state.score, str_buffer, 10), false);
}

// LOGIC
bool check_collision_board (sbyte x, sbyte y, bool on);
bool check_collision_down(void);
bool check_collision_left(void);
bool check_collision_right(void);
bool move_down(void);
bool move_left(void);
bool move_right(void);
bool rotate_left(void);
bool rotate_right(void);
void check_for_lines(void);
void clear_lines(void);
void position_block(void);
void hold_block(void);
void new_bag(void);
void new_block(void);
bool set_board(sbyte x, sbyte y, bool on);
void set_block(void);
void step(void);
void blink(void);
void game_over(void);
void add_score(ubyte rows);

ubyte bag_idx = 0;
ubyte bag[BLOCK_COUNT] = {0,1,2,3,4,5,6};

void new_bag() {
  bag_idx = 0;
  ubyte i = BLOCK_COUNT; // 7
  ubyte s = 0;
  do {
    i--; // 6 -> 0
    ubyte j = rand() % BLOCK_COUNT;
    s = bag[i];
    bag[i] = bag[j];
    bag[j] = s;

  } while (i > 0);
}

void position_block() {
  state.x = 3;
  state.y = 0;
  state.r = 0;

  if (state.block == blocks[0]) { // Block_O starts one block over.
    state.x++;
  }

  if(block_board_mask(&check_collision_board, state.x, state.y, state.r, false)) {
    game_over();
    state.block = NULL;
  }
}

void new_block() {
  if (bag_idx == BLOCK_COUNT) { // bag is empty
    new_bag();
  }
  state.block = blocks[bag[bag_idx++]]; // take from bag.
  state.hold_swappable = true;

  position_block();
}

bool set_board(sbyte x, sbyte y, bool on) {
  state.board[BOARD_WIDTH * y + x] = on;
  return false;
}

void set_block() {
  block_board_mask(&set_board, state.x, state.y, state.r, true);
}

bool check_collision_board(sbyte x, sbyte y, bool on) {
  return state.board[BOARD_WIDTH * y + x];
}

bool check_collision_down () {
  return block_board_mask(&check_collision_board, state.x, state.y + 1, state.r, false);
}

bool check_collision_left () {
  return block_board_mask(&check_collision_board, state.x - 1, state.y, state.r, false);
}

bool check_collision_right () {
  return block_board_mask(&check_collision_board, state.x + 1, state.y, state.r, false);
}

bool check_collision_rotate(ubyte r) {
  return block_board_mask(&check_collision_board, state.x, state.y, r, false);
}

bool move_left() {
  if (!check_collision_left()) {
    clear_block();
    state.x--;
    draw_block();
    return true;
  }
  return false;
}

bool move_right() {
  if (!check_collision_right()) {
    clear_block();
    state.x++;
    draw_block();
    return true;
  }

  return false;
}

bool move_down() {
  if (check_collision_down()) {
    return false;
  }

  clear_block();
  state.y++;
  draw_block();

  return true;
}

bool rotate_right() {
  ubyte new_r = (state.r + 1) % 4;
  if (check_collision_rotate(new_r)) {
    return false;
  }

  clear_block();
  state.r = new_r;
  draw_block();

  return true;
}

bool rotate_left() {
  ubyte new_r = (state.r - 1) % 4;
  if (check_collision_rotate(new_r)) {
    return false;
  }

  clear_block();
  state.r = new_r;
  draw_block();

  return true;
}

void hold_block() {
  if (state.hold_swappable) {
    clear_block();
    clear_hold();

    Block *swap = state.block;
    state.block = state.hold;
    state.hold = swap;

    position_block();
    draw_block();
    draw_hold();

    state.hold_swappable = false;
  }
}

void add_score(ubyte rows) {
  state.score += points_per_row[rows] * (state.level + 1);
  state.lines += rows;

  if (state.lines / STAGE_LENGTH > state.level && state.level < LEVEL_CAP) {
    state.level++;
    set_ms_tick();
  }

  render_stage();
}

void check_for_lines() {
  memset(state.full_lines, false, BOARD_HEIGHT);
  ubyte y, i, j, count = 0;
  size_t offset = 0;

  for (i = 0; i < state.block->size; i++) {
    y = state.y + i;
    offset = y * BOARD_WIDTH; // offset for rows.
    state.full_lines[y] = true; // line is full?

    for (j = 0; j < BOARD_WIDTH; j++) {
      if (!state.board[offset + j]) { // if we find an empty spot.
        state.full_lines[y] = false;         // line is not full.
        break;
      }
    }

    if (state.full_lines[y]) {
      count++;
    }
  }

  if (count > 0) {
    // if there were lines
    add_score(count);
    state.blinking = BLINK_COUNT;
  }
}

void clear_lines() {
  ubyte y, shift = 0;
  uint16_t current_row, shift_row;

  for (int i = BOARD_HEIGHT; i > 0; i--) {
    y = i - 1;
    if(state.full_lines[y]) {
      shift++; // a new blank line.
      continue;
    }

    if(shift > 0) {
      current_row = BOARD_WIDTH * y; // the empty row.
      shift_row = BOARD_WIDTH * (y + shift); // the row to drop.
      // shift that memory.
      memmove(state.board + shift_row, state.board + current_row, BOARD_WIDTH);
      memset(state.board + current_row, false, BOARD_WIDTH);
      render_row(y);
      render_row(y + shift);
    }
  }
}

void blink() {
  for (ubyte i = 0; i < BOARD_HEIGHT; i++) {
    if (state.full_lines[i]) {
      render_line(i, state.blinking % 2);
    }
  }
}

void step() {
  if(!move_down()) {
    set_block();
    check_for_lines();
    state.block = NULL;
    timer = 0;
  }
}

void game_over() {
  state.game_over = true;
  render_checkers();
  oled_set_cursor(0, 3);
  oled_write_P(PSTR("GAME"), false);
  oled_set_cursor(1, 4);
  oled_write_P(PSTR("OVER"), false);
}

// PUBLIC FUNCTIONS

bool tetris_mode() {
  return state.playing;
}

uint16_t tetris_score() {
  return state.score;
}

void tetris_new() {
  state.playing = true;
  state.game_over = false;
  state.score = 0;
  state.level = 0;
  state.lines = 0;
  state.drop = false;
  state.hold_swappable = true;
  memset(state.board, false, BOARD_WIDTH*BOARD_HEIGHT);

  set_ms_tick();
  new_bag();
  new_block();

  oled_clear();
  render_tetris_box();
  render_stage();
}

void tetris_quit() {
  state.playing = false;
  oled_clear();
}

void tetris_tick() {
  if (state.blinking > 0) {
    if (timer_elapsed(timer) > BLINK_SPEED) {
      timer = timer_read();
      blink();
      state.blinking--;
      if (state.blinking == 0) {
        clear_lines();
        timer = 0;
      }
    }
    return;
  }
  if (!state.game_over && (state.drop || timer_elapsed(timer) > state.ms_tick)) {
    timer = timer_read();
    if (state.block == NULL) {
      new_block();
      draw_block();
    } else {
      step();
    }
  }
}

bool tetris_record_key(uint16_t keycode, bool pressed) {
  if (keycode == TET_D) {
    state.drop = pressed;
  }

  if(pressed){
    switch(keycode) {
    case TETRIS:
      if(tetris_mode()) {
        tetris_quit();
      } else {
        tetris_new();
      }
      return true;
    case TET_L:
      move_left();
      break;
    case TET_R:
      move_right();
      break;
    case TET_RF:
      rotate_right();
      break;
    case TET_RR:
      rotate_left();
      break;
    case TET_H:
      hold_block();
      break;
    }
  }
  return tetris_mode();
}




/*
* 0
* 1
* 2
* 3
* 4
* 5
* 6
* 7
* 8
* 9
*10
*11
*12
*13
*14
*15
*16
*17
*18
*19
*20     .A.
*21     AAA
******  ...
*/

