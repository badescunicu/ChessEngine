#include <iostream>
#include <board.hpp>
#include <piece.hpp>

int main() {
    Board b;
    b.print();
    // Test moves
    b.apply_move(Piece::build_move(6, 0, 3, 0));
    b.apply_move(Piece::build_move(6, 0, 3, 0));
    b.print();
    return 0;
}
