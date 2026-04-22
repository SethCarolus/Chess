#pragma once

#include "board.h"

typedef struct App {
  int width;
  int height;
  int fps;
  const char* title;
  Board board;
} App;

void init(App* app);
void run(App* app);
void shutdown(App* app);
