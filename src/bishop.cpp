#include <bishop.hpp>

Bishop::Bishop() {}

Bishop::~Bishop() {}


std::vector<unsigned short>
Bishop::get_available_moves(const int initial_row, const int initial_column,
                          const Board& board) {
    return std::vector<unsigned short>();
}
