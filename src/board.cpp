#include <iostream>
#include <board.hpp>
#include <piece.hpp>

Board::Board() {
    for (int i = 0; i < 8; i++) {
        board[i] = 0;
    }

    // Set Pawns
    for (int j = 0; j < 8; j++) {
        set_pos_value(1, j, PAWN_W);
        set_pos_value(6, j, PAWN_B);
    }

    // Set Rooks
    set_pos_value(0, 0, ROOK_W);
    set_pos_value(0, 7, ROOK_W);
    set_pos_value(7, 0, ROOK_B);
    set_pos_value(7, 7, ROOK_B);

    // Set Knights
    set_pos_value(0, 1, KNIGHT_W);
    set_pos_value(0, 6, KNIGHT_W);
    set_pos_value(7, 1, KNIGHT_B);
    set_pos_value(7, 6, KNIGHT_B);

    // Set Bishops
    set_pos_value(0, 2, BISHOP_W);
    set_pos_value(0, 5, BISHOP_W);
    set_pos_value(7, 2, BISHOP_B);
    set_pos_value(7, 5, BISHOP_B);

    // Set Queens
    set_pos_value(0, 4, QUEEN_W);
    set_pos_value(7, 3, QUEEN_B);

    // Set Kings
    set_pos_value(0, 3, KING_W);
    set_pos_value(7, 4, KING_B);
}

void Board::set_pos_value(const int row, const int column, const int piece) {
    // Set the position to NONE
    board[row] = board[row] & (~(15 << (column << 2)));
    // Set the position to the actual piece
    board[row] = board[row] | (piece << (column << 2));
}

unsigned int Board::get_piece(const int row, const int column) {
    return ((board[row] & (15 << (column << 2))) >> (column << 2));
}

void Board::print() {
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j <= 7; j++) {
            std::cout << get_piece(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
