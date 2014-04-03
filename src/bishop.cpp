#include <bishop.hpp>

Bishop::Bishop() {}

Bishop::~Bishop() {}


std::vector<unsigned short>
Bishop::get_available_moves(const int row, const int col,
                          const Board& board) {
    std::vector<unsigned short> result;
    int dir_row[] = {1, 1, -1, -1};
    int dir_col[] = {-1, 1, 1, -1};
    const int DIR_SIZE = 4;
    for (int i = 0; i < DIR_SIZE; i++) {
        int tmp_row = row + dir_row[i];
        int tmp_col = col + dir_col[i];
        while (inside(tmp_row, tmp_col) && !board.get_piece(tmp_row, tmp_col)) {
            result.push_back(Piece::build_move(row, col, tmp_row, tmp_col));
            tmp_row += dir_row[i];
            tmp_col += dir_col[i];
        }

        // Check if the bishop can take oponent's piece
        if (inside(tmp_row, tmp_col) &&
            (COLOR_OF(board.get_piece(tmp_row, tmp_col)) ^
             COLOR_OF(board.get_piece(row, col)))) {
            result.push_back(Piece::build_move(row, col, tmp_row, tmp_col));
        }
    }
    return result;
}
