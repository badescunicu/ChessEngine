#ifndef __BOARD__HPP
#define __BOARD__HPP

class Board {
public:
    Board();
    unsigned int get_piece(int pos_x, int pos_y);
    void apply_move(short move);
    void set_pos_value(int pos_x, int pos_y, int piece);
    bool check_for_chess();
    void print();
private:
    unsigned int board[7];
};

#endif
