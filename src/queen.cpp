#include <queen.hpp>

Queen::Queen() {}

Queen::~Queen() {}


std::vector<unsigned short>
Queen::get_available_moves(const int row, const int col,
                          const Board& board) {
    std::vector<unsigned short> result;
    // Bishop-like moves
    int dir_row_bishop[] = {1, 1, -1, -1};
    int dir_col_bishop[] = {-1, 1, 1, -1};
    const int DIR_SIZE = 4;
    for (int i = 0; i < DIR_SIZE; i++) {
        int tmp_row = row + dir_row_bishop[i];
        int tmp_col = col + dir_col_bishop[i];
        while (inside(tmp_row, tmp_col) && !board.get_piece(tmp_row, tmp_col)) {
            Piece::update_moves(result, Piece::build_move(row, col, tmp_row, tmp_col), board);
            tmp_row += dir_row_bishop[i];
            tmp_col += dir_col_bishop[i];
        }

        // Check if the queen can take oponent's piece
        if (inside(tmp_row, tmp_col) &&
            (COLOR_OF(board.get_piece(tmp_row, tmp_col)) ^
             COLOR_OF(board.get_piece(row, col)))) {
            Piece::update_moves(result, Piece::build_move(row, col, tmp_row, tmp_col), board);
        }
    }

    // Rook-like moves
    int dir_row_rook[] = {0, 1, 0, -1};
    int dir_col_rook[] = {-1, 0, 1, 0};
    for (int i = 0; i < DIR_SIZE; i++) {
        int tmp_row = row + dir_row_rook[i];
        int tmp_col = col + dir_col_rook[i];
        while (inside(tmp_row, tmp_col) && !board.get_piece(tmp_row, tmp_col)) {
            Piece::update_moves(result, Piece::build_move(row, col, tmp_row, tmp_col), board);
            tmp_row += dir_row_rook[i];
            tmp_col += dir_col_rook[i];
        }

        // Check if the queen can take oponent's piece
        if (inside(tmp_row, tmp_col) &&
            (COLOR_OF(board.get_piece(tmp_row, tmp_col)) ^
             COLOR_OF(board.get_piece(row, col)))) {
            Piece::update_moves(result, Piece::build_move(row, col, tmp_row, tmp_col), board);
        }
    }

    return result;
}
