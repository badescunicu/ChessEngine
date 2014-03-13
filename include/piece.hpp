#ifndef _PIECE_
#define _PIECE_
#include <vector>
#include <utility>

/*
 * Value in pawns for every piece
 */
#define PAWN_VALUE 1
#define BISHOP_VALUE 3 
#define KNIGHT_VALUE 4
#define ROOK_VALUE 5
#define QUEEN_VALUE 8
#define KING_VALUE 0xffffff
#define row first
#define column second

namespace chess {

typedef std::pair<int,int> position;

class piece {
 public:
  virtual std::vector<position> get_all_moves() = 0;
  void do_move(const position& pos) {
    this->pos = pos;
  }
  piece(int value, const position& pos) : value(value), pos(pos) {} 
  piece(int value) : value(value) {}
 protected:  
  int value;
  position pos;
};

class pawn : public piece {
 public:
  pawn() : piece(PAWN_VALUE) {}
  pawn(const position& pos) : piece(PAWN_VALUE, pos) {}
  std::vector<position> get_all_moves(){
  } 
};


class bishop : public piece {
 public:
  bishop() : piece(KNIGHT_VALUE) {}
  bishop(const position& pos) : piece(KNIGHT_VALUE, pos) {}
  std::vector<position> get_all_moves(){
  } 
};

class knight : public piece {
 public:
  knight() : piece(KNIGHT_VALUE) {}
  knight(const position& pos) : piece(KNIGHT_VALUE, pos) {}
  std::vector<position> get_all_moves(){
  } 
};

class rook : public piece {
 public:
  rook() : piece(ROOK_VALUE) {}
  rook(const position& pos) : piece(ROOK_VALUE, pos) {}
  std::vector<position> get_all_moves(){
  }
};

class queen : public piece {
 public:
  queen() : piece(QUEEN_VALUE) {}
  queen(const position& pos) : piece(QUEEN_VALUE, pos) {}
  std::vector<position> get_all_moves(){
  }
};

class king : public piece {
 public:
  king() : piece(KING_VALUE) {}
  king(const position& pos) : piece(KING_VALUE, pos) {} 
  std::vector<position> get_all_moves(){
  }
};
}
#endif
