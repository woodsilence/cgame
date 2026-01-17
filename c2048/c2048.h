#ifndef C2048_H
#define C2048_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum Operation {
  MoveLeft,
  MoveRight,
  MoveUp,
  MoveDown,
  Quit,
  Restart,
  Pause
} Operation;

void c2048();

int init_game();
int game_loop();
int end_game();

Operation get_operation();

void init_map();
void random_map();
void print_map();

int game_over();
int game_check();

void up();
void down();
void right();
void left();
void reset();

void swap(int *a, int *b);

#endif // C2048_h
