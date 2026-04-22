#include "piece.h"


Texture loadPieceTexture(const char* path) {
  Image img = LoadImage(path);
  ImageResize(&img, GetScreenWidth() / 8, GetScreenHeight() / 8);
  Texture texture = LoadTextureFromImage(img);
  UnloadImage(img);
  return texture;
}

Piece createPiece(PieceColor color, PieceType type) {
  Piece piece = {
    .color = color,
    .type = type,
    .hasMoved = false
  };
  switch (piece.color) {
    case PC_WHITE: {
      switch (piece.type) {
        case PT_VOID: {
          break;
        }
        case PT_PAWN: {
          piece.texture = loadPieceTexture("../resources/pieces-basic-png/white-pawn.png");
          break;
        }
        case PT_ROOK: {
          piece.texture = loadPieceTexture("../resources/pieces-basic-png/white-rook.png");
          break;
        }
        case PT_KNIGHT: {
          piece.texture = loadPieceTexture("../resources/pieces-basic-png/white-knight.png");
          break;
        }
        case PT_BISHOP: {
          piece.texture = loadPieceTexture("../resources/pieces-basic-png/white-bishop.png");
          break;
        }
        case PT_QUEEN: {
          piece.texture = loadPieceTexture("../resources/pieces-basic-png/white-queen.png");
          break;
        }
        case PT_KING: {
          piece.texture = loadPieceTexture("../resources/pieces-basic-png/white-king.png");
          break;
        }
      }
      break;
    }
    case PC_BLACK: {
      switch (piece.type) {
        case PT_VOID: {
          break;
        }
        case PT_PAWN: {
          piece.texture = loadPieceTexture("../resources/pieces-basic-png/black-pawn.png");
          break;
        }
        case PT_ROOK: {
          piece.texture = loadPieceTexture("../resources/pieces-basic-png/black-rook.png");
          break;
        }
        case PT_KNIGHT: {
          piece.texture = loadPieceTexture("../resources/pieces-basic-png/black-knight.png");
          break;
        }
        case PT_BISHOP: {
          piece.texture = loadPieceTexture("../resources/pieces-basic-png/black-bishop.png");
          break;
        }
        case PT_QUEEN: {
          piece.texture = loadPieceTexture("../resources/pieces-basic-png/black-queen.png");
          break;
        }
        case PT_KING: {
          piece.texture = loadPieceTexture("../resources/pieces-basic-png/black-king.png");
          break;
        }
      }
    }
    break;
  }
  return piece;
}
