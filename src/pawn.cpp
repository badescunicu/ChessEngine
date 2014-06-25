#include <pawn.hpp>

Pawn::Pawn() {}

Pawn::~Pawn() {}


std::vector<unsigned short>
Pawn::get_available_moves(const int row, const int col,
                          const Board& board) {
    std::vector<unsigned short> result;
    short coef = 1 - (COLOR_OF(board.get_piece(row, col)) * 2);

    if (inside(row + coef, col) && !board.get_piece(row + coef, col)) {
        if (row + coef == (COLOR_OF(board.get_piece(row, col)) == WHITE ? BOARD_SIZE - 1 : 0)) {
            // Promotions
            PieceType options[] = {KNIGHT_W, BISHOP_W, ROOK_W, QUEEN_W};
            for (int i = 0; i < 4; ++i)
                Piece::update_moves(result, Piece::build_move(row, col, row + coef, col,
                  static_cast<PieceType>(options[i] + (COLOR_OF(board.get_piece(row, col)) << 3))),
                  board);
        } else
            Piece::update_moves(result, Piece::build_move(row, col, row + coef, col), board);
    }

    // Attacks
    if (inside(row + coef, col + coef) && (board.get_piece(row + coef, col + coef)) &&
       (COLOR_OF(board.get_piece(row, col)) ^ COLOR_OF(board.get_piece(row + coef, col + coef)))) {
        Piece::update_moves(result, Piece::build_move(row, col, row + coef, col + coef), board);
    }
    if (inside(row + coef, col - coef) && (board.get_piece(row + coef, col - coef)) &&
       (COLOR_OF(board.get_piece(row, col)) ^ COLOR_OF(board.get_piece(row + coef, col - coef)))) {
        Piece::update_moves(result, Piece::build_move(row, col, row + coef, col - coef), board);
    }

    // Check if the pawn can move 2 squares forward
    if ((COLOR_OF(board.get_piece(row, col)) == WHITE && row == 1) ||
        (COLOR_OF(board.get_piece(row, col)) == BLACK && row == 6)) {
        if (!board.get_piece(row + coef, col) && !board.get_piece(row + (coef << 2), col)) {
            Piece::update_moves(result, Piece::build_move(row, col, row + coef, col), board);
        }
    }

    // Check for en passant
    if (row == (COLOR_OF(board.get_piece(row, col)) == WHITE ? 4 : 3)) {
        int victim_row, victim_column;
        if (board.valid_en_passant(victim_row, victim_column)) {
            if (COLOR_OF(board.get_piece(victim_row, victim_column)) !=
                COLOR_OF(board.get_piece(row, col)) && abs(victim_column - col) == 1) {
                Piece::update_moves(result, Piece::build_move(row, col, row + coef, victim_column),
                                    board);
            }
        }
    }

    return result;
}
