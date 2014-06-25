#include <piece.hpp>

class Knight : public Piece {
public:
    Knight();
    ~Knight();

    std::vector<unsigned short>
    get_available_moves(const int row, const int col,
                        const Board& board);
};
