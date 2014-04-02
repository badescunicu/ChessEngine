#ifndef __BOARD__HPP
#define __BOARD__HPP
#include <piece_type.hpp>
#include <logger.hpp>

#define BOARD_SIZE 8
#define COLOR_OF(c) ((c & 8) >> 3)

enum GameType { DEFAULT, CUSTOM };

class Board {
public:
    Board(GameType type);
    unsigned int get_piece(const int pos_x, const int pos_y);
    void apply_move(const unsigned short move);
    // Puts the piece on the given position
    void set_pos_value(const int row, const int column, const PieceType piece);
    bool check_for_chess();
    void print();
    ~Board();
private:
    unsigned int board[8];
    Logger logger;
};

#endif
