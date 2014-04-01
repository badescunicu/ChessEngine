#ifndef _BOARD_
#define _BOARD_
#include <vector>
#include <iostream>
#include <cassert>
#include <utility>
#include <piece.hpp>

using std::cerr;
enum GameType { DEFAULT, CUSTOM };

class Board {
  char **board;
 public:
  static const int BOARD_SIZE = 8;
  Board(GameType type) {
    board = (char**)calloc(BOARD_SIZE, sizeof(char*)); 
    for(int i = 0; i < BOARD_SIZE; i++)
      board[i] = (char*)calloc(BOARD_SIZE, sizeof(char));

    if (type == DEFAULT) {
      for(int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = PAWN_W; 
        board[6][i] = PAWN_B;
      }

      board[0][7] = ROOK_W; 
      board[0][0] = ROOK_W; 
      board[0][1] = KNIGHT_W; 
      board[0][6] = KNIGHT_W; 
      board[0][5] = BISHOP_W;
      board[0][2] = BISHOP_W; 
      board[0][3] = QUEEN_W; 
      board[0][4] = KING_W; 

      board[7][7] = ROOK_B; 
      board[7][0] = ROOK_B; 
      board[7][1] = KNIGHT_B; 
      board[7][6] = KNIGHT_B; 
      board[7][5] = BISHOP_B;
      board[7][2] = BISHOP_B; 
      board[7][3] = QUEEN_B; 
      board[7][4] = KING_B; 
    }
  }

  char** getBoard() {
    return board;
  }

  ~Board() {
    for (int i = 0; i < BOARD_SIZE; ++i)
        delete board[i];
    delete board;
  }

  void apply_move(const string& move) {
    std::swap(board[move[1] - '0' - 1][move[0] - 'a'], board[move[3] - '0' - 1][move[2] - 'a']);
    board[move[1] - '0' - 1][move[0] - 'a'] = 0; 
  }
  

  /*
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
  */
};
#endif
