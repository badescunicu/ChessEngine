#include <piece.hpp>

class Pawn : public Piece {
public:
    Pawn();
    ~Pawn();

    std::vector<unsigned short>
    get_available_moves(const int i, const int j,
                        const Board& board);
};
