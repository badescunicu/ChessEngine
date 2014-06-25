#include <piece.hpp>

class Bishop : public Piece {
public:
    Bishop();
    ~Bishop();

    std::vector<unsigned short>
    get_available_moves(const int row, const int col,
                        const Board& board);
};
