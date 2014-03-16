#ifndef _BOARD_
#define _BOARD_
#include <vector>
#include <cassert>
#include <utility>
#include <piece.hpp>

enum GameType { DEFAULT, CUSTOM };

class Board {
  std::vector<std::vector<Piece*>> board; 
 public:
  static const int BOARD_SIZE = 8;
  Board(GameType type) : board(BOARD_SIZE, std::vector<Piece*>(BOARD_SIZE, static_cast<Piece*>(0))) {
    if (type == DEFAULT) {
      for(int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = new Pawn(Position(1, i), WHITE); 
        board[6][i] = new Pawn(Position(6, i), BLACK);
      }

      board[0][7] = new Rook(Position(0, 7), WHITE);
      board[0][0] = new Rook(Position(0, 0), WHITE);
      board[0][1] = new Knight(Position(0, 1), WHITE);
      board[0][6] = new Knight(Position(0, 6), WHITE);
      board[0][5] = new Bishop(Position(0, 5), WHITE);
      board[0][2] = new Bishop(Position(0, 2), WHITE);
      board[0][3] = new Queen(Position(0, 3), WHITE);
      board[0][4] = new King(Position(0, 4), WHITE);

      board[7][7] = new Rook(Position(7, 7), BLACK);
      board[7][0] = new Rook(Position(7, 0), BLACK);
      board[7][1] = new Knight(Position(7, 1), BLACK);
      board[7][6] = new Knight(Position(7, 6), BLACK);
      board[7][5] = new Bishop(Position(7, 5), BLACK);
      board[7][2] = new Bishop(Position(7, 2), BLACK);
      board[7][3] = new Queen(Position(7, 3), BLACK);
      board[7][4] = new King(Position(7, 4), BLACK);
    }
  }

  ~Board() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
      for (int j = 0; j < BOARD_SIZE; ++j) {
        if (board[i][j])
          delete board[i][j];
      }
    }
  }

  std::vector<Piece*>& operator [] (int i) { 
   return board[i]; 
  }

  void apply_move(const Move &m) {
    board[m.first.first][m.first.second]->do_move(m.second);
    std::swap(board[m.first.first][m.first.second], board[m.second.first][m.second.second]);
    if(board[m.first.first][m.first.second] != NULL) {
      delete board[m.first.first][m.first.second];
      board[m.first.first][m.first.second] = NULL;
    }
  }

  void add_piece(std::string piece, Color color) {
    Position pos(piece[2] - 1 - '0', piece[1] - 'a');
    switch (piece[0]) {
      case 'P': board[pos.first][pos.second] = new Pawn(pos, color); break;
      case 'R': board[pos.first][pos.second] = new Rook(pos, color); break;
      case 'N': board[pos.first][pos.second] = new Knight(pos, color); break;
      case 'B': board[pos.first][pos.second] = new Bishop(pos, color); break;
      case 'Q': board[pos.first][pos.second] = new Queen(pos, color); break;
      case 'K': board[pos.first][pos.second] = new King(pos, color);
    }
  }
};
#endif
