#include <knight.hpp>

Knight::Knight() {}

Knight::~Knight() {}


std::vector<unsigned short>
Knight::get_available_moves(const int row, const int col,
                          const Board& board) {
    int dir_row[] = {1, 2, 2, 1, -1, -2, -2, 1};
    int dir_col[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    std::vector<unsigned short> result;
    for(int i = 0; i < 8; i++) {
        short dest_row = row + dir_row[i];
        short dest_col = col + dir_col[i];
        if(inside(dest_row, dest_col) &&
           (!board.get_piece(dest_row, dest_col) ||
            (COLOR_OF(board.get_piece(dest_row, dest_col)) ^
             COLOR_OF(board.get_piece(row, col))))) {
            result.push_back(Piece::build_move(row, col, dest_row, dest_col)); 
        }
    } 
    return result;
}
