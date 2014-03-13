#ifndef _BOARD_
#define _BOARD_
#include "piece.hpp"

namespace chess {
class board : public std::vector<std::vector<piece*>> {
 public:
  typedef std::vector<std::vector<piece*>> base;
  static const int BOARD_SIZE = 8;
  board() : std::vector<std::vector<piece*>>(8, std::vector<piece*>(8, static_cast<piece*>(0))) {
    for(int i = 0; i < 8; i++) {
      base::operator[](0)[1] = new pawn(position(1, i)); 
      base::operator[](6)[i] = new pawn(position(6, i));
    }

    base::operator[](0)[7] = new rook(position(0, 7));
    base::operator[](0)[0] = new rook(position(0, 0));
    base::operator[](0)[1] = new knight(position(0, 1));
    base::operator[](0)[6] = new knight(position(0, 6));
    base::operator[](0)[5] = new bishop(position(0, 5));
    base::operator[](0)[2] = new bishop(position(0, 2));
    base::operator[](0)[3] = new queen(position(0, 3));
    base::operator[](0)[4] = new king(position(0, 4));

    base::operator[](7)[7] = new rook(position(7, 7));
    base::operator[](7)[0] = new rook(position(7, 0));
    base::operator[](7)[1] = new knight(position(7, 1));
    base::operator[](7)[6] = new knight(position(7, 6));
    base::operator[](7)[5] = new bishop(position(7, 5));
    base::operator[](7)[2] = new bishop(position(7, 2));
    base::operator[](7)[3] = new queen(position(7, 3));
    base::operator[](7)[4] = new king(position(7, 4));
  }
};
}

#endif
