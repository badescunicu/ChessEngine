#include <iostream>
#include <iomanip>
#include <board.hpp>
#include <piece.hpp>
#include <logger.hpp>

Board::Board() : logger("board_log.txt", "[Board] ") {
    // Initialize the board to 0
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

void Board::set_pos_value(const int row, const int column, const PieceType piece) {
    // Set the position to NONE
    board[row] = board[row] & (~(15 << (column << 2)));
    // Set the position to the actual piece
    board[row] = board[row] | (piece << (column << 2));
}

unsigned int Board::get_piece(const int row, const int column) {
    return ((board[row] & (15 << (column << 2))) >> (column << 2));
}

void Board::apply_move(const unsigned short move) {
    int initial_row = move & 7;
    int initial_column = (move & 56) >> 3;
    int destination_row = (move & 448) >> 6;
    int destination_column = (move & 3584) >> 9;
    set_pos_value(initial_row, initial_column, NONE);
    set_pos_value(destination_row, destination_column,
                  static_cast<PieceType>(get_piece(initial_row,
                                                   initial_column)));
}

void Board::print() {
    logger.log("Printing board");
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j <= 7; j++) {
            logger.out << std::setw(2) << get_piece(i, j) << " ";
        }
        logger.out << std::endl;
    }
}
