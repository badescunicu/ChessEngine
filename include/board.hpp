#ifndef __BOARD__HPP
#define __BOARD__HPP
#include <piece.hpp>
#include <logger.hpp>

class Board {
public:
    Board();
    unsigned int get_piece(const int pos_x, const int pos_y);
    void apply_move(const unsigned short move);
    // Puts the piece on the given position
    void set_pos_value(const int row, const int column, const PieceType piece);
    bool check_for_chess();
    void print();
private:
    unsigned int board[7];
    Logger logger;
};

#endif
