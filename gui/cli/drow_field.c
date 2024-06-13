#include "grafa.h"
void drow_the_field() {
  print_rectangle(0, 21, 0, 21);
  // print_rectangle(0, BOARD_N + 1, BOARD_M + 2, BOARD_M + HUD_WIDTH + 3);

  print_rectangle(1, 3, 26, 26 + 12);
  print_rectangle(4, 6, 26, 26 + 12);
  print_rectangle(7, 9, 26, 26 + 12);
  print_rectangle(10, 12, 26, 26 + 12);
  print_rectangle(17, 21, 26, 35);

  mvprintw(2, 27, "LEVEL");
  mvprintw(5, 27, "SCORE");
  mvprintw(8, 27, "SPEED");
  mvprintw(11, 27, "BEST");
  mvprintw(16, 27, "NEXT");
}
//  MVPRINTW(BOARD_N / 2, (BOARD_M - INTRO_MESSAGE_LEN) / 2 + 1,
//  INTRO_MESSAGE);}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  mvaddch(top_y, left_x, ACS_ULCORNER);
  int i = left_x + 1;

  for (; i < right_x; i++) mvaddch(top_y, i, ACS_HLINE);
  mvaddch(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }

  mvaddch(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) mvaddch(bottom_y, i, ACS_HLINE);
  mvaddch(bottom_y, i, ACS_LRCORNER);
}
void print_blocks(int x, int y) { mvprintw(x, 1 + y * 2, "[]"); }
void start() {
  mvprintw(6, 3, "WELCOM TO TETRIS");
  mvprintw(8, 2, "please push something");
  mvprintw(10, 7, "to start");

  mvprintw(18, 2, "handmade from GAITHERL");
  getch();
}
void print_stats(GameInfo_t *game_info) {
  mvprintw(2, 27 + 6, "%d", game_info->level);
  mvprintw(5, 33, "%d", game_info->score);
  if (game_info->speed > 600) {
    mvprintw(8, 33, "pause");
    mvprintw(8, 2, "please push space");
    mvprintw(10, 7, "to continue");
  } else {
    mvprintw(8, 33, "%d", (600 - game_info->speed) / 40);
  }
  mvprintw(11, 33, "%d", game_info->high_score);
}
void the_end(GameInfo_t *game_info) {
  mvprintw(5, 20, "YOUR SCORE  %d", game_info->score);
  if (game_info->score > game_info->high_score) {
    mvprintw(7, 20, "It's the best result!!!");
    mvprintw(9, 20, "!!!WOW!!!");

    FILE *file;
    if ((file = fopen("the_best_score.txt", "w")) != NULL) {
      fprintf(file, "%d", game_info->score);
    }
  }
}
void drow_al_f(GameInfo_t *game_info) {
  drow_the_field();
  print_stats(game_info);
  for (int i = 2; i < 22; i++) {
    for (int j = 0; j < 10; j++) {
      if (game_info->field[i][j] == 1) {
        print_blocks(i - 1, j);
      }
    }
  }
  for (int k = 0; k < 4; k++) {
    for (int m = 0; m < 4; m++) {
      // if (next_block->block_matrix[k][m]==1){
      if (game_info->next[k][m] == 1) {
        print_blocks(k + 18, m + 13);
      }
    }
  }
}
