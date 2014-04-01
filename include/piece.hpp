#ifndef _PIECE_
#define _PIECE_
#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include <string>
/*
 * Value in Pawns for every Piece
 */
#define PAWN_VALUE 1
#define BISHOP_VALUE 3 
#define KNIGHT_VALUE 4
#define ROOK_VALUE 5
#define QUEEN_VALUE 8
#define KING_VALUE 0

#define PAWN_W 1
#define KNIGHT_W 2
#define BISHOP_W 3
#define ROOK_W 4
#define QUEEN_W 5
#define KING_W 6
#define PAWN_B 9
#define KNIGHT_B 10
#define BISHOP_B 11
#define ROOK_B 12
#define QUEEN_B 13
#define KING_B 14

#define COLOR_OF(c) ((c & 8) >> 3)

typedef std::pair<int, int> Position;
enum Color { WHITE, BLACK, NO_COLOR };

using std::string;
using std::make_pair;
using std::vector;

short to_short(short start_row, short start_col, short dest_row, short dest_col) { 
    short ret = 0;
    ret |= start_row;
    ret |= (start_col << 3);
    ret |= (dest_row << 6);
    ret |= (dest_col << 9);
    return ret; 
}

string to_string(short move) {
    string ret(4, 0);  
    ret[1] = (move & 7) + '0' + 1;
    ret[0] = ((move & (7 << 3)) >> 3) + 'a';
    ret[3] = ((move & (7 << 6)) >> 6) + '0' + 1; 
    ret[2] = ((move & (7 << 9)) >> 9) + 'a';
    return ret;
}

inline bool inside(int i, int j) {
    return (i >= 0 && i < 8 && j >= 0 && j < 8);
    //return !((i & 8) | (j & 8));
}

class Piece {
 public:
  virtual vector<short> get_all_moves(char**, int, int) = 0;
};

class Pawn : public Piece {
 public:
  vector<short> get_all_moves(char** board, int i, int j) { 
      vector<short> ret;
      short coef = 1 - (COLOR_OF(board[i][j]) * 2);
      if(inside(i + coef, j) && !board[i + coef][j])
          ret.push_back(to_short(i, j, i + coef, j));
      if((inside(i + coef, j + coef)) && (board[i + coef][j + coef])
         && (COLOR_OF(board[i][j]) ^ COLOR_OF(board[i + coef][j + coef])))
          ret.push_back(to_short(i, j, i + coef, j + coef));
      if((inside(i + coef, j - coef) && (board[i + coef][j - coef]) && 
          (COLOR_OF(board[i][j]) ^ COLOR_OF(board[i + coef][j - coef]))))
          ret.push_back(to_short(i, j, i + coef, j - coef));
      return ret;
  } 
};

class Bishop : public Piece {
 public:
  vector<short> get_all_moves(char **board, int row, int col) {
      return vector<short>();
  } 
};

class Knight : public Piece {
 public:
  vector<short> get_all_moves(char **board, int row, int col) {
      int dr[] = {1, 2, 2, 1, -1, -2, -2, 1};
      int dc[] = {-2, -1, 1, 2, 2, 1, -1, -2};
      vector<short> ret;
      for(int i = 0; i < 8; i++) {
          short dest_row = row + dr[i];
          short dest_col = col + dc[i];
          if(inside(dest_row, dest_col) && (!board[dest_row][dest_col] ||
             (COLOR_OF(board[dest_row][dest_col]) ^ COLOR_OF(board[row][col])))) {
              ret.push_back(to_short(row, col, dest_row, dest_col)); 
          }

      }
      return ret;
  } 
};

class Rook : public Piece {
 public:
  vector<short> get_all_moves(char **board, int row, int col) {
      return vector<short>();
  }
};

class Queen : public Piece {
 public:
  vector<short> get_all_moves(char **board, int row, int col) {
      return std::vector<short>();
  }
};

class King : public Piece {
 public:
  vector<short> get_all_moves(char **board, int row, int col) {
      return vector<short>();
  }
};
#endif
