#ifndef tetris_h
#define tetris_h

//#include "../../gui/cli/grafa.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define int screen_matrix[23][10];
//#define int block_matrix[4][4];

typedef struct {
  // int screen_matrix[22][10];
  int block_matrix[4][4];
  int x;
  int y;
  int rez;
  int col_line;
  int shag;    // kolvo shagov ot verha do
  int figura;  // kolvo-figur v igre
  int game_over;
} matrix;
/// from readme for game
typedef enum {
  Start,      //начало игры
  Pause,      //остановка
  Terminate,  //завершение?
  Left,       //
  Right,
  Up,
  Down,   //
  Action  //
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;
GameInfo_t updateCurrentState(matrix *A, GameInfo_t *game_info);
GameInfo_t init_game(matrix *A);

int userInput(UserAction_t action, bool hold);
void print_stats(GameInfo_t *game_info);
void the_end(GameInfo_t *game_info);

/// my function for game
void sigact(UserAction_t action, matrix *A, GameInfo_t *game_info);  //
int choose_figure(matrix *A);
int add_figure_at_screen(matrix *A, GameInfo_t *game_info);
int delete_the_block(matrix *A, GameInfo_t *game_info);
int spawn(matrix *A, GameInfo_t *game_info);
int right(matrix *A, GameInfo_t *game_info);
int left(matrix *A, GameInfo_t *game_info);
int turn(matrix *A, GameInfo_t *game_info);
int del_the_line(matrix *A, GameInfo_t *game_info);
int check_continue(matrix A, GameInfo_t game_info);
void free_field(GameInfo_t *game_info);

// extra function
void print_matrix(GameInfo_t *game_info);

#endif
