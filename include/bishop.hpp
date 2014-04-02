#include <piece.hpp>

class Bishop : public Piece {
public:
    Bishop();
    ~Bishop();

    std::vector<unsigned short>
    get_available_moves(const int initial_row, const int initial_column,
                        const Board& board);
};
