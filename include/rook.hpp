#include <piece.hpp>

class Rook : public Piece {
public:
    Rook();
    ~Rook();

    std::vector<unsigned short>
    get_available_moves(const int row, const int col,
                        const Board& board);
};
