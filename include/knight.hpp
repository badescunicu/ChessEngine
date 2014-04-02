#include <piece.hpp>

class Knight : public Piece {
public:
    Knight();
    ~Knight();

    std::vector<unsigned short>
    get_available_moves(const int initial_row, const int initial_column,
                        const Board& board);
};
