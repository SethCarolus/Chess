#pragma once

#include "raylib.h"

typedef enum PieceTextureType {
  WHITE_PAWN = 0,
  WHITE_ROOK,
  WHITE_KNIGHT,
  WHITE_BISHOP,
  WHITE_QUEEN,
  WHITE_KING,
  BLACK_PAWN,
  BLACK_ROOK,
  BLACK_KNIGHT,
  BLACK_BISHOP,
  BLACK_QUEEN,
  BLACK_KING,
} PieceTextureType;


void loadAssets();
Texture* getPieceTexture(PieceTextureType type);
Texture* getBoardTexture();
void unloadAssets();
