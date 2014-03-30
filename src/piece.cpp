#include <piece.hpp>

Piece::Piece() {}

Piece::~Piece() {}

unsigned short Piece::build_move(const int initial_row,
                                 const int initial_column,
                                 const int destination_row,
                                 const int destination_column)  {
    unsigned short result = 0;
    result |= initial_row;
    result |= (initial_column << 3);
    result |= (destination_row << 6);
    result |= (destination_column << 9);
    return result;
}
