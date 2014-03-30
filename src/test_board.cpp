#include <iostream>
#include <board.hpp>
#include <piece.hpp>

int main() {
    Board b;
    b.print();
    b.apply_move(1745);
    b.print();
    return 0;
}
