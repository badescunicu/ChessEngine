#include <piece.hpp>

class Queen : public Piece {
public:
    Queen();
    ~Queen();

    std::vector<unsigned short>
    get_available_moves(const int row, const int col,
                        const Board& board);
};
