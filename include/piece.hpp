#ifndef _PIECE_
#define _PIECE_
#include <vector>
#include <utility>
#include <functional>
/*
 * Value in Pawns for every Piece
 */
#define PAWN_VALUE 1
#define BISHOP_VALUE 3 
#define KNIGHT_VALUE 4
#define ROOK_VALUE 5
#define QUEEN_VALUE 8
#define KING_VALUE 0xffffff

typedef std::pair<int, int> Position;
typedef std::pair<Position, Position> Move;
enum Color { WHITE, BLACK };

class Piece {
public:
  virtual std::vector<Move> get_all_moves(const std::function<bool(int, int)>& valid) = 0;
  void do_move(const Position& pos) {
    this->pos = pos;
  } 

  Piece(int value, const Position& pos, const Color& color) : color(color), pos(pos), value(value) {} 
  Piece(int value) : value(value) {} 
  Color color;
protected:  
  int value;
  Position pos;
};

class Pawn : public Piece {
public:
  Pawn() : Piece(PAWN_VALUE) {}
  Pawn(const Position& pos, const Color& color) : Piece(PAWN_VALUE, pos, color) {}
  std::vector<Move> get_all_moves(const std::function<bool(int, int)>& valid) {
    return std::vector<Move>();
  } 
};

class Bishop : public Piece {
public:
  Bishop() : Piece(KNIGHT_VALUE) {}
  Bishop(const Position& pos, const Color& color) : Piece(KNIGHT_VALUE, pos, color) {}
  std::vector<Move> get_all_moves(const std::function<bool(int, int)>& valid) {
    return std::vector<Move>();
  } 
};

class Knight : public Piece {
public:
  Knight() : Piece(KNIGHT_VALUE) {}
  Knight(const Position& pos, const Color& color) : Piece(KNIGHT_VALUE, pos, color) {}
  std::vector<Move> get_all_moves(const std::function<bool(int, int)>& valid) {
    std::cout << this->pos.first << ' ' << this->pos.second << '\n';
    int dl[] = {1, 2, 2, 1, -1, -2, -2, 1};
    int dc[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    std::vector<Move> ret;
    for(int i = 0; i < 8; i++)
      if(valid(pos.first + dl[i], pos.second + dc[i]))
        ret.push_back(std::make_pair(this->pos,
                      std::make_pair(pos.first + dl[i], pos.second + dc[i])));
    return ret;
  } 
};

class Rook : public Piece {
public:
  Rook() : Piece(ROOK_VALUE) {}
  Rook(const Position& pos, const Color& color) : Piece(ROOK_VALUE, pos, color) {}
  std::vector<Move> get_all_moves(const std::function<bool(int, int)>& valid) {
    return std::vector<Move>();
  }
};

class Queen : public Piece {
public:
  Queen() : Piece(QUEEN_VALUE) {}
  Queen(const Position& pos, const Color& color) : Piece(QUEEN_VALUE, pos, color) {}
  std::vector<Move> get_all_moves(const std::function<bool(int, int)>& valid) {
    return std::vector<Move>();
  }
};

class King : public Piece {
public:
  King() : Piece(KING_VALUE) {}
  King(const Position& pos, const Color& color) : Piece(KING_VALUE, pos, color) {} 
  std::vector<Move> get_all_moves(const std::function<bool(int, int)>& valid){
    return std::vector<Move>();
  }
};
#endif
