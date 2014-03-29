#include <iostream>
#include <board.hpp>
#include <piece.hpp>



int main() {
    Board b;
    b.set_pos_value(6, 7, PAWN_B);
    b.print();
    return 0;
}
