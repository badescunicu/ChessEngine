#ifndef __PIECE__HPP
#define __PIECE__HPP
#include <vector>
#include <board.hpp>

class Piece {
public:
    Piece();
    static PieceType char_to_piece(char c, const Color color);
    static std::string move_to_string(const unsigned short move);
    static unsigned short string_to_move(const std::string& moveStr,
                                         const Color piece_color);

    // regular move
    static unsigned short build_move(const int initial_row,
                              const int initial_column,
                              const int destination_row,
                              const int destination_column);
    // pawn promotion
    static unsigned short build_move(const int initial_row,
                              const int initial_column,
                              const int destination_row,
                              const int destination_column,
                              const PieceType promoted);

    // checks if not in check after making a move
    static bool safe(const unsigned short move, const Board& board);

    // retains a move if it is safe
    static void update_moves(std::vector<unsigned short>& result,
                             const unsigned short move,
                             const Board& board);

    virtual std::vector<unsigned short>
    get_available_moves(const int row, const int col,
                            const Board& board) = 0;
    virtual ~Piece();
};

#endif
