#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t* state, unsigned int snum);
static char next_square(game_state_t* state, unsigned int snum);
static void update_tail(game_state_t* state, unsigned int snum);
static void update_head(game_state_t* state, unsigned int snum);

#define DEFAULT_ROWS 10
#define DEFAULT_COLS 10
#define DEFAULT_ROWS 10
#define DEFAULT_COLS 10
#define EMPTY_CELL ' '
#define WALL_CELL '#'
#define FOOD_CELL '*'
#define HEAD_UP '^'
#define HEAD_LEFT '<'
#define HEAD_DOWN 'v'
#define HEAD_RIGHT '>'
#define HEAD_DEAD 'x'
#define BODY_VERTICAL '|'
#define BODY_HORIZONTAL '-'
#define TAIL_UP 'w'
#define TAIL_LEFT 'a'
#define TAIL_DOWN 's'
#define TAIL_RIGHT 'd'

/* Task 1 */
game_state_t* create_default_state() {
  game_state_t* state = malloc(sizeof(game_state_t));
  state->num_rows = DEFAULT_ROWS;
  state->board = malloc(state->num_rows * sizeof(char*));
  for (unsigned int i = 0; i < state->num_rows; i++) {
    state->board[i] = malloc(DEFAULT_COLS * sizeof(char));
    for (unsigned int j = 0; j < DEFAULT_COLS; j++) {
      state->board[i][j] = EMPTY_CELL;
    }
  }
  state->num_snakes = 0;
  state->snakes = NULL;
  return state;
}

/* Task 2 */
void free_state(game_state_t* state) {
  for (unsigned int i = 0; i < state->num_rows; i++) {
    free(state->board[i]);
  }
  free(state->board);
  free(state->snakes);
  free(state);
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  for (unsigned int i = 0; i < state->num_rows; i++) {
    for (unsigned int j = 0; j < DEFAULT_COLS; j++) {
      fprintf(fp, "%c", state->board[i][j]);
    }
    fprintf(fp, "\n");
  }
}

/* Task 4.1 */
char get_board_at(game_state_t* state, unsigned int row, unsigned int col) {
  return state->board[row][col];
}

/* Task 4.2 */
static char next_square(game_state_t* state, unsigned int snum) {
  snake_t snake = state->snakes[snum];
  unsigned int next_row = get_next_row(snake.head_row, snake.head_col);
  unsigned int next_col = get_next_col(snake.head_col, snake.head_col);
  return state->board[next_row][next_col];
}

/* Task 4.3 */
static void update_head(game_state_t* state, unsigned int snum) {
  snake_t* snake = &(state->snakes[snum]);
  unsigned int next_row = get_next_row(snake->head_row, snake->head_col);
  unsigned int next_col = get_next_col(snake->head_col, snake->head_col);
  snake->head_row = next_row;
  snake->head_col = next_col;
  set_board_at(state, next_row, next_col, head_to_body(get_board_at(state, snake->head_row, snake->head_col)));
}

/* Task 4.4 */
static void update_tail(game_state_t* state, unsigned int snum) {
  snake_t* snake = &(state->snakes[snum]);
  set_board_at(state, snake->tail_row, snake->tail_col, body_to_tail(get_board_at(state, snake->tail_row, snake->tail_col)));
  snake->tail_row = get_next_row(snake->tail_row, snake->tail_col);
  snake->tail_col = get_next_col(snake->tail_col, snake->tail_col);
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  for (unsigned int i = 0; i < state->num_snakes; i++) {
    char next = next_square(state, i);
    if (is_snake(next) || next == WALL_CELL) {
      state->snakes[i].live = false;
    } else if (next == FOOD_CELL) {
      add_food(state);
    }
    update_head(state, i);
    if (!state->snakes[i].live) {
      update_tail(state, i);
    }
  }
}

/* Task 5 */
game_state_t* load_board(FILE* fp) {
  game_state_t* state = malloc(sizeof(game_state_t));
  fscanf(fp, "%u", &(state->num_rows));
  state->board = malloc(state->num_rows * sizeof(char*));
  for (unsigned int i = 0; i < state->num_rows; i++) {
    state->board[i] = malloc(DEFAULT_COLS * sizeof(char));
    fscanf(fp, "%s", state->board[i]);
  }
  state->num_snakes = 0;
  state->snakes = NULL;
  return state;
}

/* Task 6.1 */
static void find_head(game_state_t* state, unsigned int snum) {
  snake_t* snake = &(state->snakes[snum]);
  for (unsigned int i = 0; i < state->num_rows; i++) {
    for (unsigned int j = 0; j < DEFAULT_COLS; j++) {
      char cell = state->board[i][j];
      if (cell == head_to_body(snake->live ? HEAD_CELL : DEAD_HEAD_CELL)) {
        snake->head_row = i;
        snake->head_col = j;
        return;
      }
    }
  }
}

/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  unsigned int num_snakes = 0;
  for (unsigned int i = 0; i < state->num_rows; i++) {
    for (unsigned int j = 0; j < DEFAULT_COLS; j++) {
      char cell = state->board[i][j];
      if (is_head(cell)) {
        num_snakes++;
      }
    }
  }
  state->num_snakes = num_snakes;
  state->snakes = malloc(num_snakes * sizeof(snake_t));
  unsigned int snum = 0;
  for (unsigned int i = 0; i < state->num_rows; i++) {
    for (unsigned int j = 0; j < DEFAULT_COLS; j++) {
      char cell = state->board[i][j];
      if (is_head(cell)) {
        state->snakes[snum].tail_row = i;
        state->snakes[snum].tail_col = j;
        find_head(state, snum);
        state->snakes[snum].live = true;
        snum++;
      }
    }
  }
  return state;
}

/* Helper function definitions */

static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch) {
  state->board[row][col] = ch;
}

static bool is_tail(char c) {
  return (c == TAIL_UP || c == TAIL_LEFT || c == TAIL_DOWN || c == TAIL_RIGHT);
}

static bool is_head(char c) {
  return (c == HEAD_UP || c == HEAD_LEFT || c == HEAD_DOWN || c == HEAD_RIGHT || c == HEAD_DEAD);
}

static bool is_snake(char c) {
  return (is_tail(c) || is_head(c));
}

static char body_to_tail(char c) {
  switch (c) {
    case BODY_UP:
      return TAIL_UP;
    case BODY_LEFT:
      return TAIL_LEFT;
    case BODY_DOWN:
      return TAIL_DOWN;
    case BODY_RIGHT:
      return TAIL_RIGHT;
    default:
      return c;
  }
}

static char head_to_body(char c) {
  switch (c) {
    case HEAD_UP:
      return BODY_UP;
    case HEAD_LEFT:
      return BODY_LEFT;
    case HEAD_DOWN:
      return BODY_DOWN;
    case HEAD_RIGHT:
      return BODY_RIGHT;
    default:
      return c;
  }
}

static unsigned int get_next_row(unsigned int cur_row, char c) {
  switch (c) {
    case 'v':
    case 's':
    case 'S':
      return cur_row + 1;
    case '^':
    case 'w':
    case 'W':
      return cur_row - 1;
    default:
      return cur_row;
  }
}

static unsigned int get_next_col(unsigned int cur_col, char c) {
  switch (c) {
    case '>':
    case 'd':
    case 'D':
      return cur_col + 1;
    case '<':
    case 'a':
    case 'A':
      return cur_col - 1;
    default:
      return cur_col;
  }
}
