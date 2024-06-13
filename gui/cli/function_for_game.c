#include "grafa.h"

void game_loop(matrix *A, GameInfo_t *game_info) {
  UserAction_t action = Action;
  start();

  while (A->game_over != 1) {
    refresh();
    timeout(game_info->speed);
    action = userInput(action, 1);
    clear();
    drow_al_f(game_info);
    sigact(action, A, game_info);
    clear();
    drow_al_f(game_info);
    if (game_info->speed < 700) {
      sigact(6, A, game_info);
    }
  }
}

void cleanup_resources(GameInfo_t *game_info) {
  clear();
  timeout(3000);
  the_end(game_info);
  getch();
  endwin();
  free_field(game_info);
}
