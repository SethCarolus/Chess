#include "asset_manager.h"
#include "raylib.h"

#define NUMBER_OF_PIECES 12

Sound moveSound;
Sound captureSound;

Texture pieceTextures[NUMBER_OF_PIECES];
Texture boardTexture;

Texture loadPieceTexture(const char* path) {
  Image img = LoadImage(path);
  ImageResize(&img, GetScreenWidth() / 8, GetScreenHeight() / 8);
  Texture texture = LoadTextureFromImage(img);
  UnloadImage(img);
  return texture;
}

void loadAssets() {
  // PIECE TEXTURES
  pieceTextures[WHITE_PAWN] = loadPieceTexture("../resources/pieces-basic-png/white-pawn.png");
  pieceTextures[WHITE_ROOK] = loadPieceTexture("../resources/pieces-basic-png/white-rook.png");
  pieceTextures[WHITE_KNIGHT] = loadPieceTexture("../resources/pieces-basic-png/white-knight.png");
  pieceTextures[WHITE_BISHOP] = loadPieceTexture("../resources/pieces-basic-png/white-bishop.png");
  pieceTextures[WHITE_QUEEN] = loadPieceTexture("../resources/pieces-basic-png/white-queen.png");
  pieceTextures[WHITE_KING] = loadPieceTexture("../resources/pieces-basic-png/white-king.png");
  pieceTextures[BLACK_PAWN] = loadPieceTexture("../resources/pieces-basic-png/black-pawn.png");
  pieceTextures[BLACK_ROOK] = loadPieceTexture("../resources/pieces-basic-png/black-rook.png");
  pieceTextures[BLACK_KNIGHT] = loadPieceTexture("../resources/pieces-basic-png/black-knight.png");
  pieceTextures[BLACK_BISHOP] = loadPieceTexture("../resources/pieces-basic-png/black-bishop.png");
  pieceTextures[BLACK_QUEEN] = loadPieceTexture("../resources/pieces-basic-png/black-queen.png");
  pieceTextures[BLACK_KING] = loadPieceTexture("../resources/pieces-basic-png/black-king.png");

  // BOARD TEXTURE
  Image boardImg = LoadImage("../resources/boards-png/rect-8x8.png");
  ImageResize(&boardImg, GetScreenWidth(), GetScreenHeight());
  boardTexture = LoadTextureFromImage(boardImg);
  UnloadImage(boardImg);

  // PIECE SOUNDS
  moveSound = LoadSound("../resources/sounds/move.wav");
  captureSound = LoadSound("../resources/sounds/capture.wav");
}

Texture* getPieceTexture(PieceTextureType type) {
 return &pieceTextures[type];
}

Texture* getBoardTexture() {
  return &boardTexture;
}

void unloadAssets() {
  // PIECE TEXTURES
  for (int i = 0; i < NUMBER_OF_PIECES; i++) {
    UnloadTexture(pieceTextures[i]);
  }

  // BOARD TEXTURE
  UnloadTexture(boardTexture);

  UnloadSound(moveSound);
  UnloadSound(captureSound);
}
