#include <king.hpp>

King::King() {}

King::~King() {}


std::vector<unsigned short>
King::get_available_moves(const int row, const int col,
                          const Board& board) {
    std::vector<unsigned short> result;
    int dir_row[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int dir_col[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    const int DIR_SIZE = 8;

    for (int i = 0; i < DIR_SIZE; i++) {
        if (inside(row + dir_row[i], col + dir_col[i]) &&
            (!board.get_piece(row + dir_row[i], col + dir_col[i]) ||
             (COLOR_OF(board.get_piece(row, col)) ^
              COLOR_OF(board.get_piece(row + dir_row[i], col + dir_col[i]))))) {

            Piece::update_moves(result, Piece::build_move(row, col, row + dir_row[i],
                                                          col + dir_col[i]), board);
        }
    }

    // Castlings
    Color king_color = static_cast<Color>(COLOR_OF(board.get_piece(row, col)));
    if (board.valid_castling(king_color, QUEENSIDE)) {
        if (!board.get_piece(row, col - 1) &&
                !board.get_piece(row, col - 2) &&
                !board.get_piece(row, col - 3) &&
                !board.checked(king_color) &&
                Piece::safe(Piece::build_move(row, col, row, col - 1), board))
            Piece::update_moves(result, Piece::build_move(row, col, row, col - 2), board);
    }
    if (board.valid_castling(king_color, KINGSIDE)) {
        if (!board.get_piece(row, col + 1) &&
                !board.get_piece(row, col + 2) &&
                !board.checked(king_color) &&
                Piece::safe(Piece::build_move(row, col, row, col + 1), board))
            Piece::update_moves(result, Piece::build_move(row, col, row, col + 2), board);
    }

    return result;
}
