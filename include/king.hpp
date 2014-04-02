#include <piece.hpp>

class King : public Piece {
public:
    King();
    ~King();

    std::vector<unsigned short>
    get_available_moves(const int initial_row, const int initial_column,
                        const Board& board);
};
