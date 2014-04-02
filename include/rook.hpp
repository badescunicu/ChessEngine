#include <piece.hpp>

class Rook : public Piece {
public:
    Rook();
    ~Rook();

    std::vector<unsigned short>
    get_available_moves(const int initial_row, const int initial_column,
                        const Board& board);
};
