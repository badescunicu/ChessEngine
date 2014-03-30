#include <pawn.hpp>

Pawn::Pawn() {}

Pawn::~Pawn() {}


std::vector<unsigned short>
Pawn::get_available_moves(const int initial_row, const int initial_column,
                          const Board& board) {
    std::vector<unsigned short> result;
    if (initial_row + 1 < BOARD_SIZE) {
        result.push_back(Piece::build_move(initial_row, initial_column,
                                           initial_row + 1, initial_column));
    }
    if (initial_row + 2 < BOARD_SIZE) {
        result.push_back(Piece::build_move(initial_row, initial_column,
                                           initial_row + 2, initial_column));
    }
    return result;
}
