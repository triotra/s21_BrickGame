#include "tetris.h"
//////////////////////////////////////выбор
///фигуры////////////////////////////////////////////////
int choose_figure(matrix *A) {  /// каждая фигура рандомно появляется на
                                /// поле,когда вызываем эту функцию

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A->block_matrix[i][j] = 0;
    }
  }
  A->x = 0;
  A->y = 3;

  switch (A->rez) {
    case 0:  // poloska

      A->block_matrix[1][3] = 1;
      A->block_matrix[1][2] = 1;
      A->block_matrix[1][1] = 1;
      A->block_matrix[1][0] =
          1;  //{0 ,0 ,0 ,0 ,1 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};
      break;
    case 1:  // g verx sleva
      A->block_matrix[0][1] = 1;
      A->block_matrix[1][2] = 1;
      A->block_matrix[1][1] = 1;
      A->block_matrix[1][3] = 1;

      break;
    case 2:  // g verx sprava
      A->block_matrix[0][2] = 1;
      A->block_matrix[1][2] = 1;
      A->block_matrix[1][1] = 1;
      A->block_matrix[1][0] = 1;

      break;
    case 3:
      A->block_matrix[2][2] = 1;
      A->block_matrix[1][2] = 1;
      A->block_matrix[1][1] = 1;
      A->block_matrix[2][1] = 1;

      break;
    case 4:
      A->block_matrix[2][0] = 1;
      A->block_matrix[1][2] = 1;
      A->block_matrix[1][1] = 1;
      A->block_matrix[2][1] = 1;

      break;
    case 5:
      A->block_matrix[2][1] = 1;
      A->block_matrix[2][2] = 1;
      A->block_matrix[1][1] = 1;
      A->block_matrix[1][0] = 1;

      break;
    case 6:
      A->block_matrix[0][1] = 1;
      A->block_matrix[1][2] = 1;
      A->block_matrix[1][1] = 1;
      A->block_matrix[1][0] = 1;
      break;
  }

  return 0;
}
//////////////////////////////////////выбор
///фигуры////////////////////////////////////////////////

/////////////////////////////////////добавляем фигуру на нашу
///матрицу/////////////////////////////

int add_figure_at_screen(
    matrix *A,
    GameInfo_t
        *game_info) {  //добавляет фигуру на поле учитывая координаы куда должна
                       //поместиться. возвращает 1 если не может этого сделать
                       //(при этом меняет  with check for continue -did it/
  int res = 0;

  res = check_continue(*A, *game_info);
  if (res == 0) {
    for (int m = 0; m < 4; m++) {
      for (int k = 0; k < 4; k++) {
        if (A->block_matrix[m][k] == 1) {
          game_info->field[A->x + m][A->y + k] = 1;
        }
      }
    }
  }
  return res;
}
/////////////////////////////////////добавляем фигуру на нашу
///матрицу/////////////////////////////

void print_matrix(GameInfo_t *game_info) {
  for (int i = 0; i < 22; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%d ", game_info->field[i][j]);
    }
    printf("\n");
  }
}

///////////////////////////////////////удаляем
///строку//////////////////////////////////////////
int del_the_line(matrix *A, GameInfo_t *game_info) {
  int check = 1;
  A->col_line = 0;
  for (int i = 0; i < 22; i++) {
    check = 1;
    for (int j = 0; j < 10; j++) {
      // check=A->screen_matrix[i][j]*check;
      check = game_info->field[i][j] * check;
    }

    if (check == 1) {
      A->col_line++;
      // getch();
      // col_line++;
      for (int k = 0; k < i; k++) {
        for (int m = 0; m < 10; m++) {
          game_info->field[i - k][m] = game_info->field[i - k - 1][m];
        }
      }
    }
  }
  updateCurrentState(A, game_info);

  return check;  // return 0 if not delete the line .
}
///////////////////////////////////////удаляем
///строку//////////////////////////////////////////

/////SPAWN
/// begin////////////////////////////////////////////////////////////////////
int spawn(matrix *A, GameInfo_t *game_info) {  /////SPAWN

  int res = 0;

  delete_the_block(A, game_info);
  A->x++;  //добавить проверку на конец поля
  res = check_continue(*A, *game_info);
  if (res == 0) {
    add_figure_at_screen(A, game_info);
    A->shag++;
  }

  if (res == 1) {
    matrix next_block;
    // &next_block={0};
    A->figura++;
    A->x--;
    add_figure_at_screen(A, game_info);
    del_the_line(A, game_info);
    A->x = 0;
    A->y = 3;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        // A->block_matrix[i][j] = next_block->block_matrix[i][j];}}//vunesti v
        // konechnui avtomat
        A->block_matrix[i][j] = game_info->next[i][j];
      }
    }
    srand(time(NULL));                          // sfsdfdf
    next_block.rez = (rand() + A->figura) % 7;  // fdsfsfd
    choose_figure(&next_block);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        game_info->next[i][j] = next_block.block_matrix[i][j];
      }
    }
    A->shag = 0;

    int n = add_figure_at_screen(A, game_info);
    //  del_the_line(A);
    if (n == 1) {
      A->game_over = 1;
    }
  }

  return res;
}
//////////////////////////////////////////////////////////////////spawn end

////////////////////////////////////сдвиг вправо////////////////////////////
int right(matrix *A, GameInfo_t *game_info) {
  int res = 0;
  delete_the_block(A, game_info);
  A->y--;
  if (check_continue(*A, *game_info) == 0) {
    add_figure_at_screen(A, game_info);
  } else {
    A->y++;
    add_figure_at_screen(A, game_info);
    res = 1;
  }

  return res;
}
////////////////////////////////////сдвиг вправо////////////////////////////

////////////////////////////////////ПОВОРОТ////////////////////////////
int turn(matrix *A, GameInfo_t *game_info) {
  int res = 0;
  delete_the_block(A, game_info);
  int b[4][4] = {0};
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      b[i][j] = A->block_matrix[i][j];
    }
  }  // na vsyakiu slychau

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A->block_matrix[i][j] = b[4 - j - 1][i];
    }
  }
  if (check_continue(*A, *game_info) == 0) {
    add_figure_at_screen(A, game_info);
  } else {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        A->block_matrix[i][j] = b[i][j];
      }
    }
    add_figure_at_screen(A, game_info);
    res = 1;
  }

  return res;
}
////////////////////////////////////ПОВОРОТ////////////////////////////

////////////////////////////////////сдвиг влево////////////////////////////
int left(matrix *A, GameInfo_t *game_info) {
  int res = 0;
  delete_the_block(A, game_info);
  A->y++;
  if (check_continue(*A, *game_info) == 0) {
    add_figure_at_screen(A, game_info);
  } else {
    A->y--;
    add_figure_at_screen(A, game_info);
    res = 1;
  }

  return res;
}
////////////////////////////////////сдвиг влево////////////////////////////

////////////////////////////////////удалить фигуру с
///матрицы////////////////////////////
int delete_the_block(matrix *B, GameInfo_t *game_info) {
  for (int m = 0; m < 4; m++) {
    for (int k = 0; k < 4; k++) {
      if (B->block_matrix[m][k] == 1) {  //
        game_info->field[B->x + m][B->y + k] = 0;
      }
    }
  }
  return 0;
}
//////////////////////////удалить фигуру с
///матрицы/////////////////////////////////////

/////////////////////////проверка на
///соединение///////////////////////////////////////
int check_continue(matrix A, GameInfo_t game_info) {
  int res = 0;
  for (int m = 0; m < 4; m++) {
    for (int k = 0; k < 4; k++) {
      if (A.block_matrix[m][k] == 1 && (A.x + m) > 21) {
        res = 1;
        break;
      } else if (A.block_matrix[m][k] == 1 && (A.y + k) > 9) {
        res = 1;
        break;
      } else if (A.block_matrix[m][k] == 1 && (A.y + k) < 0) {
        res = 1;
        break;
      } else if (A.block_matrix[m][k] == 0) {
        continue;
      }

      else if (game_info.field[A.x + m][A.y + k] == 1 &&
               ((A.y + k) > -1 && (A.y + k) < 10) &&
               A.block_matrix[m][k] == 1) {
        res = 1;
        break;
      } else {
        continue;
      }
    }
    if (res == 1) {
      break;
    }
  }

  return res;
}
/////////////////////////проверка на
///соединение///////////////////////////////////////

//////////////////////////////////////////update current state/////////////
GameInfo_t init_game(matrix *A) {
  GameInfo_t game_info;

  game_info.field = malloc(25 * sizeof(int *));
  for (int i = 0; i < 25; i++) {
    game_info.field[i] = malloc(10 * sizeof(int));
  }

  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 10; j++) {
      game_info.field[i][j] = 0;
    }
  }
  game_info.next = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    game_info.next[i] = malloc(4 * sizeof(int));
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      game_info.next[i][j] = A->block_matrix[i][j];
    }
  }

  FILE *file;

  if ((file = fopen("the_best_score.txt", "r")) != NULL) {
    fscanf(file, "%d", &game_info.high_score);
  }

  else {
    game_info.high_score = 0;
  }
  game_info.score = 0;

  game_info.level = 0;
  game_info.speed = 600;
  game_info.pause = 0;
  return game_info;
}
GameInfo_t updateCurrentState(matrix *A, GameInfo_t *game_info) {
  if (A->col_line == 1) {
    game_info->score = game_info->score + 100;
  }
  if (A->col_line == 2) {
    game_info->score = game_info->score + 300;
  }
  if (A->col_line == 3) {
    game_info->score = game_info->score + 700;
  }
  if (A->col_line == 4) {
    game_info->score = game_info->score + 1500;
  }
  game_info->speed = 600;
  // game_info->speed=game_info->speed+game_info->level*40;
  game_info->level = game_info->score / 600;
  if (game_info->level > 10) {
    game_info->level = 10;
  }

  game_info->speed = game_info->speed - game_info->level * 40;
  A->col_line = 0;
  return *game_info;
}

//////////////////////////////////////////update current state/////////////

void free_field(GameInfo_t *game_info) {
  for (int i = 0; i < 25; i++) {
    free(game_info->field[i]);
  }
  free(game_info->field);
  for (int i = 0; i < 4; i++) {
    free(game_info->next[i]);
  }
  free(game_info->next);
}
