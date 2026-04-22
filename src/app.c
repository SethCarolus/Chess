#include "app.h"

#include "raylib.h"
#include "board.h"
#include "renderer.h"
#include "movement.h"
#include "asset_manager.h"

void init(App* app) {
  InitWindow(app->width, app->height, app->title);
  SetTargetFPS(app->fps);
  InitAudioDevice();
  loadAssets();
  app->board = createBoard();
}

void run(App* app) {
  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    displayBoard(&app->board);
    handleMovement(&app->board);
    EndDrawing();
  }
}

void shutdown(App* app) {
  unloadAssets();
  CloseWindow();
}
