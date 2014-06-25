#include <piece.hpp>

class King : public Piece {
public:
    King();
    ~King();

    std::vector<unsigned short>
    get_available_moves(const int row, const int col,
                        const Board& board);
};
