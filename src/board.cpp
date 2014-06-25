#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <board.hpp>
#include <piece_type.hpp>
#include <logger.hpp>

Board::Board(GameType type, const Color color_on_move) : logger("board_log.txt",
                                                                 "[Board] ") {
    // Initialize the board to 0
    for (int i = 0; i < 9; i++) {
        board[i] = 0;
    }
    // Set castlings as possible
    board[8] |= 0xF000;

    set_color_on_move(color_on_move);
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

Board::Board(const Board& initial_board) : logger() {
    for (int i = 0; i < 9; ++i)
        board[i] = initial_board.board[i];
}

Board::~Board() {}

void Board::set_pos_value(const int row, const int column, const PieceType piece) {
    // Set the position to NONE
    board[row] = board[row] & (~(15 << (column << 2)));
    // Set the position to the actual piece
    board[row] = board[row] | (piece << (column << 2));

    // King positions must be accessed quickly
    if (piece == KING_W || piece == KING_B) {
        Color king_color = static_cast<Color>(COLOR_OF(piece));
        board[8] &= ~(63 << (6 * king_color));
        board[8] |= row << (6 * king_color);
        board[8] |= column << (3 + 6 * king_color);
    }
}

unsigned int Board::get_piece(const int row, const int column) const {
    return ((board[row] & (15 << (column << 2))) >> (column << 2));
}

void Board::get_king_position(const Color color, int& row, int& column) const {
    row = (board[8] & (7 << (6 * color))) >> (6 * color);
    column = (board[8] & (7 << (3 + 6 * color))) >> (3 + 6 * color);
}

bool Board::valid_castling(const Color color, const CastlingType type) const {
    return board[8] & (((1 << type) << (color << 1)) << 12);
}

void Board::set_castling(const Color color, const CastlingType type, const bool enabled) {
    if (enabled)
        board[8] |= ((1 << type) << (color << 1)) << 12;
    else
        board[8] &= ~(((1 << type) << (color << 1)) << 12);
}

Color Board::get_color_on_move() const {
    return static_cast<Color>((board[8] & (3 << 16)) >> 16);
}

void Board::set_color_on_move(const Color color_on_move) {
    board[8] &= ~(3 << 16);
    board[8] |= color_on_move << 16;
}

bool Board::valid_en_passant(int& row, int& column) const {
    if (board[8] & (1 << 17))
        return false;  // Edit Mode
    if (board[8] & (1 << 18)) {
        row = get_color_on_move() == WHITE ? 4 : 3;
        column = (board[8] & (7 << 19)) >> 19;
        return true;
    }
    return false;
}

void Board::change_turn() {
    if (!(board[8] & (1 << 17))) // if color_on_move != NO_COLOR
        board[8] ^= 1 << 16;
}

// Used in Force Mode only, after reading all the piece positions
void Board::guess_castlings() {
    // At this point, all the castlings are enabled by default
    if (get_piece(0, 0) != ROOK_W || get_piece(0, 4) != KING_W)
        set_castling(WHITE, QUEENSIDE, false);
    if (get_piece(0, 7) != ROOK_W || get_piece(0, 4) != KING_W)
        set_castling(WHITE, KINGSIDE, false);
    if (get_piece(7, 0) != ROOK_B || get_piece(7, 4) != KING_B)
        set_castling(BLACK, QUEENSIDE, false);
    if (get_piece(7, 7) != ROOK_B || get_piece(7, 4) != KING_B)
        set_castling(BLACK, KINGSIDE, false);
}

bool Board::apply_move(const unsigned short move) {
    //logger.log("Entered in apply_move. Decoding move");
    //logger.log_binary(&move, sizeof(unsigned short));

    int initial_row = move & 7;
    int initial_column = (move & 56) >> 3;
    int destination_row = (move & 448) >> 6;
    int destination_column = (move & 3584) >> 9;
    int promoted = (move & 0xF000) >> 12;

    /*logger.out << "initial_row:"  << initial_row << " initial_column:"
               << initial_column << " destination_row:" << destination_row
               << " destination_column:" << destination_column;
    if (promoted)
        logger.out << " promoted into: " << promoted;
    logger.out << std::endl;*/

    PieceType piece_moved = static_cast<PieceType>(get_piece(initial_row,
                                                   initial_column));
    PieceType after_promotion = static_cast<PieceType>(promoted);

    if (piece_moved != NONE) {
        //logger.log("Making move");
        set_pos_value(initial_row, initial_column, NONE);

        // Check for en passant, possibly taking the opponent's pawn
        if ((piece_moved == PAWN_B || piece_moved == PAWN_W) &&
               (destination_column != initial_column) &&
               (!get_piece(destination_row, destination_column))) {
            int victim_row, victim_column;
            if (valid_en_passant(victim_row, victim_column) &&
                    victim_column == destination_column)
                set_pos_value(initial_row, destination_column, NONE);
            else {
                // Restore to the initial board and reject the move
                //logger.log("Move rejected");
                set_pos_value(initial_row, initial_column, piece_moved);
                return false;
            }
        }

        // Check for pawn promotion and realize the move
        if (after_promotion == NONE)
            set_pos_value(destination_row, destination_column, piece_moved);
        else
            set_pos_value(destination_row, destination_column, after_promotion);

        // Check for pawn two-squares advance
        board[8] &= ~(1 << 18); // en passant initially supposed unavailable
        if ((piece_moved == PAWN_B || piece_moved == PAWN_W) &&
               (abs(initial_row - destination_row) == 2)) {
            int dir[] = {-1, 1};
            for (int i = 0; i < 2; ++i)
                if (inside(initial_column + dir[i])) {
                    PieceType neighbor = static_cast<PieceType>(get_piece(destination_row,
                                                                initial_column + dir[i]));
                    if ((neighbor == PAWN_B || neighbor == PAWN_W) &&
                            (COLOR_OF(neighbor) != COLOR_OF(piece_moved))) {
                        // set en passant as available
                        board[8] |= 1 << 18;
                        board[8] &= ~(7 << 19);
                        board[8] |= initial_column << 19;
                        break;
                    }
                }
            }

        // Update the rook position if castling
        if ((piece_moved == KING_B || piece_moved == KING_W) &&
               (abs(initial_column - destination_column) == 2)) {
            if (valid_castling(static_cast<Color>(COLOR_OF(piece_moved)),
                    (initial_column > destination_column ? QUEENSIDE : KINGSIDE))) {
                int rook_column = (destination_column << 1) - initial_column;
                if (rook_column == -1)
                    rook_column = 0;
                else if (rook_column == 8)
                    rook_column = 7;
                set_pos_value(initial_row, rook_column, NONE);
                set_pos_value(initial_row, (initial_column + destination_column) >> 1,
                                           (piece_moved == KING_B ? ROOK_B : ROOK_W));
            } else {
                // Restore to the initial board and reject the move
                //logger.log("Invalid move.");
                set_pos_value(initial_row, initial_column, piece_moved);
                set_pos_value(destination_row, destination_column, NONE);
                return false;
            }
        }

        // Updating castlings availability: if a king is moved, the player's both
        // castlings become unavailable.
        Color piece_color = static_cast<Color>(COLOR_OF(piece_moved));
        if (piece_moved == KING_W || piece_moved == KING_B) {
            if (valid_castling(piece_color, QUEENSIDE))
                set_castling(piece_color, QUEENSIDE, false);
            if (valid_castling(piece_color, KINGSIDE))
                set_castling(piece_color, KINGSIDE, false);
        }
        // If a piece has been moved from the corner, castling in that corner
        // becomes impossible.
        if ((initial_row == 0 || initial_row == BOARD_SIZE - 1) &&
                (initial_column == 0 || initial_column == BOARD_SIZE - 1)) {
            Color color = initial_row == 0 ? WHITE : BLACK;
            CastlingType side = initial_column == 0 ? QUEENSIDE : KINGSIDE;
            if (valid_castling(color, side))
                set_castling(color, side, false);
        }
    } else {
        //logger.log("No piece is on the given position");
    }
    change_turn();
    return true;
}

bool Board::checked(const Color color) const {
    int king_row, king_column;
    get_king_position(color, king_row, king_column);

    // check from queen, rook or bishop
    int line_inc[]   = {-1, -1, -1,  0, 0,  1, 1, 1};
    int column_inc[] = {-1,  0,  1, -1, 1, -1, 0, 1};
    for (int dir = 0; dir < 8; ++dir) {
        int i = king_row + line_inc[dir];
        int j = king_column + column_inc[dir];
        while (inside(i, j)) {
            int piece = get_piece(i, j);
            if (piece) {
                if (COLOR_OF(piece) == color)
                    break;
                else if (piece == QUEEN_W || piece == QUEEN_B ||
                            ((!line_inc[dir] || !column_inc[dir]) &&
                             (piece == ROOK_W || piece == ROOK_B)) ||
                            ((line_inc[dir] && column_inc[dir]) &&
                             (piece == BISHOP_W || piece == BISHOP_B)))
                    return true;
                else
                    break;
            }
            i += line_inc[dir];
            j += column_inc[dir];
        }
    }

    // check from knight
    int line_jmp[]   = {-1, -2, -2, -1, 1, 2,  2,  1};
    int column_jmp[] = {-2, -1,  1,  2, 2, 1, -1, -2};
    for (int dir = 0; dir < 8; ++dir) {
        int i = king_row + line_jmp[dir];
        int j = king_column + column_jmp[dir];
        if (inside(i, j)) {
            int piece = get_piece(i, j);
            if (piece && (COLOR_OF(piece) != color) && (piece == KNIGHT_W || piece == KNIGHT_B))
                return true;
        }
    }

    // check from pawn
    int pawn_dir = color == WHITE ? 1 : -1;
    if (inside(king_row + pawn_dir)) {
        if (king_column > 0) {
            int piece = get_piece(king_row + pawn_dir, king_column - 1);
            if ((COLOR_OF(piece) != color) && (piece == PAWN_W || piece == PAWN_B))
                return true;
        }
        if (king_column + 1 < BOARD_SIZE) {
            int piece = get_piece(king_row + pawn_dir, king_column + 1);
            if ((COLOR_OF(piece) != color) && (piece == PAWN_W || piece == PAWN_B))
                return true;
        }
    }

    // check from the other king (possible when simulating a move)
    int boss_row, boss_column;
    get_king_position(static_cast<Color>(1 - color), boss_row, boss_column);
    if (abs(king_row - boss_row) <= 1 && abs(king_column - boss_column) <= 1)
        return true;

    return false;
}

void Board::print() {
    logger.log("Printing current board state: ");
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j <= 7; j++) {
            logger.out << std::setw(2) << get_piece(i, j) << " ";
        }
        logger.out << std::endl;
    }
    logger.out << "Additional bit-board info:\n";

    // Printing king positions
    int white_king_row, white_king_column, black_king_row, black_king_column;
    get_king_position(WHITE, white_king_row, white_king_column);
    get_king_position(BLACK, black_king_row, black_king_column);
    logger.out << "White king: ("
               << white_king_row << ", " << white_king_column
               << "), Black king: ("
               << black_king_row << ", " << black_king_column << ")\n";

    // Printing castling availability
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            logger.out << (i ? "Black " : "White ")
                       << (valid_castling(i ? BLACK : WHITE,
                              j ? KINGSIDE : QUEENSIDE) ? "can" : "cannot")
                       << " castle "
                       << (j ? "kingside." : "queenside.")
                       << std::endl;
        }
    }

    // Printing en passant availability
    int pawn_row, pawn_column;
    if (valid_en_passant(pawn_row, pawn_column)) {
        logger.out << "En passant available: "
                   << (get_color_on_move() == WHITE ? "White" : "Black")
                   << " can take the pawn at ("
                   << pawn_row << ", " << pawn_column << ").";
        logger.out << std::endl;
    }
}
