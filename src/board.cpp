#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <board.hpp>
#include <piece_type.hpp>
#include <logger.hpp>

Board::Board(GameType type) : logger("board_log.txt", "[Board] ") {
    // Initialize the board to 0
    for (int i = 0; i < 8; i++) {
        board[i] = 0;
    }

    if (type == DEFAULT) {
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
        set_pos_value(0, 3, QUEEN_W);
        set_pos_value(7, 3, QUEEN_B);

        // Set Kings
        set_pos_value(0, 4, KING_W);
        set_pos_value(7, 4, KING_B);
    }
}

Board::~Board() {}

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
    logger.log("Entered in apply_move. Decoding move");
    logger.log_binary(&move, sizeof(unsigned short));

    int initial_row = move & 7;
    int initial_column = (move & 56) >> 3;
    int destination_row = (move & 448) >> 6;
    int destination_column = (move & 3584) >> 9;
    int promoted = (move & 0xF000) >> 12;

    logger.out << "initial_row:"  << initial_row << " initial_column:" <<
                  initial_column << " destination_row:" << destination_row <<
                  " destination_column:" << destination_column;
    if (promoted)
        logger.out << " promoted into: " << promoted;
    logger.out << std::endl;

    PieceType piece_moved = static_cast<PieceType>(get_piece(initial_row,
                                                   initial_column));
    PieceType after_promotion = static_cast<PieceType>(promoted);
    if (piece_moved != NONE) {
        logger.log("Making move");
        set_pos_value(initial_row, initial_column, NONE);
        if (after_promotion == NONE) {

            // Check for en passant
            if ((piece_moved == PAWN_B || piece_moved == PAWN_W) &&
                (destination_column != initial_column) &&
                (!get_piece(destination_row, destination_column)))
                set_pos_value(initial_row, destination_column, NONE);

            set_pos_value(destination_row, destination_column, piece_moved);

            // Check for castling
            if ((piece_moved == KING_B || piece_moved == KING_W) &&
                   (abs(initial_column - destination_column) == 2)) {
                int rook_column = (destination_column << 1) - initial_column;
                if (rook_column == -1)
                    rook_column = 0;
                else if (rook_column == 8)
                    rook_column = 7;
                set_pos_value(initial_row, rook_column, NONE);
                set_pos_value(initial_row, (initial_column + destination_column) >> 1,
                                           (piece_moved == KING_B ? ROOK_B : ROOK_W));
            }

        } else
            set_pos_value(destination_row, destination_column, after_promotion);
    } else {
        logger.log("No piece is on the given position");
    }
    print();
}

bool Board::check_for_chess() {
    return false;
}

void Board::print() {
    logger.log("Printing current board state");
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j <= 7; j++) {
            logger.out << std::setw(2) << get_piece(i, j) << " ";
        }
        logger.out << std::endl;
    }
}
