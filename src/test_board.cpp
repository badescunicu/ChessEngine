#include <iostream>
#include <board.hpp>
#include <piece.hpp>
#include <pawn.hpp>

int main() {
    Board b;
    Pawn p;
    b.print();
    std::vector<unsigned short> moves = p.get_available_moves(1, 0, b);
    // Test moves
    b.apply_move(moves[1]);
    b.print();
    return 0;
}
