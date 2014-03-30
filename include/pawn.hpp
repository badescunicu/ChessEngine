#include <piece.hpp>

class Pawn : public Piece {
public:
    Pawn();
    ~Pawn();

    std::vector<unsigned short>
    get_available_moves(const int initial_row, const int initial_column,
                        const Board& board);
};
