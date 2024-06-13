#ifndef grafa_h
#define grafa_h
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../../brick_game/tetris/tetris.h"

void drow_the_field();
void begin_the_game();
void print_blocks(int x, int y);
void start();
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_stats(GameInfo_t *game_info);
void the_end(GameInfo_t *game_info);
void drow_al_f(GameInfo_t *game_info);
void game_loop(matrix *A, GameInfo_t *game_info);
void cleanup_resources(GameInfo_t *game_info);

#endif
