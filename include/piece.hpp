#ifndef __PIECE__HPP
#define __PIECE__HPP
#include <vector>
#include <board.hpp>

class Piece {
public:
    Piece();
    static unsigned short build_move(const int initial_row,
                              const int initial_column,
                              const int destination_row,
                              const int destination_column);
    std::vector<unsigned short> get_available_moves(const int initial_row,
                                           const int initial_column, const Board& board);
    ~Piece();
};

#endif
