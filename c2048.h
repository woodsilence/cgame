#ifndef C2048_H
#define C2048_H

#include<stdio.h>
#include<time.h>
#include<stdlib.h>


void c2048();


void init_map();
void random_map();
void print_map();
void main_game();

int gameover();
int check();

void up();
void down();
void right();
void left();
void reset();

void swap(int* a,int* b);

#endif // C2048_h
