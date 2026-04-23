#include "piece.h"

#include "asset_manager.h"


Piece createPiece(PieceColor color, PieceType type) {
  Piece piece = {
    .color = color,
    .type = type,
    .hasMoved = false
  };
  switch (piece.color) {
    case PC_VOID: {
      break;
    }
    case PC_WHITE: {
      switch (piece.type) {
        case PT_VOID: {
          break;
        }
        case PT_PAWN: {
          piece.texture = getPieceTexture(WHITE_PAWN);
          break;
        }
        case PT_ROOK: {
          piece.texture = getPieceTexture(WHITE_ROOK);
          break;
        }
        case PT_KNIGHT: {
          piece.texture = getPieceTexture(WHITE_KNIGHT);
          break;
        }
        case PT_BISHOP: {
          piece.texture = getPieceTexture(WHITE_BISHOP);
          break;
        }
        case PT_QUEEN: {
          piece.texture = getPieceTexture(WHITE_QUEEN);
          break;
        }
        case PT_KING: {
          piece.texture = getPieceTexture(WHITE_KING);
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
          piece.texture = getPieceTexture(BLACK_PAWN);
          break;
        }
        case PT_ROOK: {
          piece.texture = getPieceTexture(BLACK_ROOK);
          break;
        }
        case PT_KNIGHT: {
          piece.texture = getPieceTexture(BLACK_KNIGHT);
          break;
        }
        case PT_BISHOP: {
          piece.texture = getPieceTexture(BLACK_BISHOP);
          break;
        }
        case PT_QUEEN: {
          piece.texture = getPieceTexture(BLACK_QUEEN);
          break;
        }
        case PT_KING: {
          piece.texture = getPieceTexture(BLACK_KING);
          break;
        }
      }
    }
    break;
  }
  return piece;
}
