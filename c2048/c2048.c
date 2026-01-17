#include "c2048.h"
#include "ncurses.h"
#include <string.h>

#define SIZE 4
int score;
int map[SIZE][SIZE];

void c2048() {
  init_game();
  while (game_loop() == 1)
    ;
  end_game();
}

int init_game() {
  initscr();
  srand(time(NULL));
  init_map();
  return 0;
}

int game_loop() {
  random_map();
  int res = game_check();
  if (res == -1)
    return !game_over();
  print_map();
  Operation op = get_operation();
  switch (op) {
  case MoveUp:
    up();
    break;
  case MoveDown:
    down();
    break;
  case MoveLeft:
    left();
    break;
  case MoveRight:
    right();
    break;
  case Quit:
    return 0;
  case Restart:
    reset();
  default:
    return 1;
  }

  return 1;
}

int end_game() {
  endwin(); // 结束ncurses模式
  return 0;
}

Operation get_operation() {
  int key = getch();
  if (key == 224)
    key = getch();
  switch (key) {
  case 72:
  case 119:
    return MoveUp;
  case 80:
  case 115:
    return MoveDown;
  case 75:
  case 97:
    return MoveLeft;
  case 77:
  case 100:
    return MoveRight;
  case 27:
  case 101:
    return Quit;
  case 114:
    return Restart;
  default:
    return Pause;
  }
}

int game_check() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (map[i][j] == 0)
        return 0;
    }
  }
  for (int i = 1; i < SIZE; i++) {
    for (int j = 1; j < SIZE; j++) {
      if ((map[i][j] == map[i - 1][j]) || (map[i][j] == map[i][j - 1]))
        return 1;
    }
  }
  return game_over();
}

int game_over() {
  clear(); // 刷新屏幕
  printw("FINAL SCORE: %d\n", score);
  printw("PRESS R TO PLAY AGAIN\nPRESS E TO EXIT\n");
  refresh();
  while (1) {
    int key2 = getch();
    if (key2 == 224)
      key2 = getch();
    if (key2 == 114) {
      reset();
      return 0;
    } else if (key2 == 27 || key2 == 101)
      return 1;
  }
  return -1;
}
void init_map() {
  memset(map, 0, SIZE * SIZE * sizeof(int));
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      map[i][j] = 0;
    }
  }
}
void random_map() {
  int i, j;
  do {
    i = rand() % SIZE;
    j = rand() % SIZE;
  } while (map[i][j] != 0);
  map[i][j] = 2;
}
void print_map() {
  erase(); // 清屏
  printw(" SCORE: %d\n", score);
  for (int i = 0; i < SIZE; i++) {
    printw("+----+----+----+----+\n");
    printw("|");
    for (int j = 0; j < SIZE; j++) {
      if (map[i][j] < 10) {
        printw("  %d ", map[i][j]);
      } else if (map[i][j] < 100) {
        printw(" %d ", map[i][j]);
      } else if (map[i][j] < 1000) {
        printw(" %d", map[i][j]);
      } else {
        printw("%d", map[i][j]);
      }
      printw("|");
    }
    printw("\n");
  }
  printw("+----+----+----+----+\n");
  refresh();
}
// 平移->合并->平移
void up() {
  for (int j = 0; j < SIZE; j++) {
    for (int i = 0; i < SIZE; i++) {
      if (map[i][j] == 0) {
        for (int k = i + 1; k < SIZE; k++) {
          if (map[k][j] != 0) {
            swap(&map[k][j], &map[i][j]);
            break;
          }
        }
      }
    }
    for (int i = 1; i < SIZE; i++) {
      if (map[i - 1][j] == map[i][j]) {
        map[i - 1][j] *= 2;
        score += map[i - 1][j];
        map[i][j] = 0;
      }
    }
    for (int i = 0; i < SIZE; i++) {
      if (map[i][j] == 0) {
        for (int k = i + 1; k < SIZE; k++) {
          if (map[k][j] != 0) {
            swap(&map[k][j], &map[i][j]);
            break;
          }
        }
      }
    }
  }
}
void down() {
  for (int j = 0; j < SIZE; j++) {
    for (int i = SIZE - 1; i > -1; i--) {
      if (map[i][j] == 0) {
        for (int k = i - 1; k > -1; k--) {
          if (map[k][j] != 0) {
            swap(&map[k][j], &map[i][j]);
            break;
          }
        }
      }
    }
    for (int i = SIZE - 2; i > -1; i--) {
      if (map[i + 1][j] == map[i][j]) {
        map[i + 1][j] *= 2;
        score += map[i + 1][j];
        map[i][j] = 0;
      }
    }
    for (int i = SIZE - 1; i > -1; i--) {
      if (map[i][j] == 0) {
        for (int k = i - 1; k > -1; k--) {
          if (map[k][j] != 0) {
            swap(&map[k][j], &map[i][j]);
            break;
          }
        }
      }
    }
  }
}
void left() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (map[i][j] == 0) {
        for (int l = j + 1; l < SIZE; l++) {
          if (map[i][l] != 0) {
            swap(&map[i][l], &map[i][j]);
            break;
          }
        }
      }
    }
    for (int j = 1; j < SIZE; j++) {
      if (map[i][j - 1] == map[i][j]) {
        map[i][j - 1] *= 2;
        score += map[i][j - 1];
        map[i][j] = 0;
      }
    }
    for (int j = 0; j < SIZE; j++) {
      if (map[i][j] == 0) {
        for (int l = j + 1; l < SIZE; l++) {
          if (map[i][l] != 0) {
            swap(&map[i][l], &map[i][j]);
            break;
          }
        }
      }
    }
  }
}
void right() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = SIZE - 1; j > -1; j--) {
      if (map[i][j] == 0) {
        for (int l = j - 1; l > -1; l--) {
          if (map[i][l] != 0) {
            swap(&map[i][l], &map[i][j]);
            break;
          }
        }
      }
    }
    for (int j = SIZE - 2; j > -1; j--) {
      if (map[i][j + 1] == map[i][j]) {
        map[i][j + 1] *= 2;
        score += map[i][j + 1];
        map[i][j] = 0;
      }
    }
    for (int j = 0; j < SIZE; j++) {
      if (map[i][j] == 0) {
        for (int l = j - 1; l > -1; l--) {
          if (map[i][l] != 0) {
            swap(&map[i][l], &map[i][j]);
            break;
          }
        }
      }
    }
  }
}
void reset() {
  init_map();
  score = 0;
}


void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}