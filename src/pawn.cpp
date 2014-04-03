#include <pawn.hpp>

Pawn::Pawn() {}

Pawn::~Pawn() {}


std::vector<unsigned short>
Pawn::get_available_moves(const int row, const int col,
                          const Board& board) {
    std::vector<unsigned short> result;
    short coef = 1 - (COLOR_OF(board.get_piece(row, col)) * 2);

    if (inside(row + coef, col) && !board.get_piece(row + coef, col)) {
        result.push_back(Piece::build_move(row, col, row + coef, col));
    }
    if (inside(row + coef, col + coef) && (board.get_piece(row + coef, col + coef)) &&
       (COLOR_OF(board.get_piece(row, col)) ^ COLOR_OF(board.get_piece(row + coef, col + coef)))) {
        result.push_back(Piece::build_move(row, col, row + coef, col + coef));
    }
    if (inside(row + coef, col - coef) && (board.get_piece(row + coef, col - coef)) &&
       (COLOR_OF(board.get_piece(row, col)) ^ COLOR_OF(board.get_piece(row + coef, col - coef)))) {
        result.push_back(Piece::build_move(row, col, row + coef, col - coef));
    }

    // Check if the pawn can move 2 squares forward
    if ((COLOR_OF(board.get_piece(row, col)) == WHITE && row == 1) ||
        (COLOR_OF(board.get_piece(row, col)) == BLACK && row == 6)) {
        if (inside(row + (coef << 2), col) && !board.get_piece(row + (coef << 2), col)) {
            result.push_back(Piece::build_move(row, col, row + coef, col));
        }
    }

    return result;
}
