#include <pawn.hpp>

Pawn::Pawn() {}

Pawn::~Pawn() {}


std::vector<unsigned short>
Pawn::get_available_moves(const int i, const int j,
                          const Board& board) {
    std::vector<unsigned short> result;
    short coef = 1 - (COLOR_OF(board.get_piece(i, j)) * 2);

    if (inside(i + coef, j) && !board.get_piece(i + coef, j)) {
        result.push_back(Piece::build_move(i, j, i + coef, j));
    }
    if (inside(i + coef, j + coef) && (board.get_piece(i + coef, j + coef)) &&
       (COLOR_OF(board.get_piece(i, j)) ^ COLOR_OF(board.get_piece(i + coef, j + coef)))) {
        result.push_back(Piece::build_move(i, j, i + coef, j + coef));
    }
    if (inside(i + coef, j - coef) && (board.get_piece(i + coef, j - coef)) &&
       (COLOR_OF(board.get_piece(i, j)) ^ COLOR_OF(board.get_piece(i + coef, j - coef)))) {
        result.push_back(Piece::build_move(i, j, i + coef, j - coef));
    }

    // Check if the pawn can move 2 squares forward
    if ((COLOR_OF(board.get_piece(i, j)) == WHITE && i == 1) ||
        (COLOR_OF(board.get_piece(i, j)) == BLACK && i == 6)) {
        if (inside(i + (coef << 2), j) && !board.get_piece(i + (coef << 2), j)) {
            result.push_back(Piece::build_move(i, j, i + coef, j));
        }
    }

    return result;
}
