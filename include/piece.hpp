#ifndef __PIECE__HPP
#define __PIECE__HPP
#include <vector>
#include <board.hpp>

enum Color { WHITE, BLACK, NO_COLOR };

class Piece {
public:
    Piece();
    static PieceType char_to_piece(char c, const Color& color);
    static std::string move_to_string(unsigned short move);
    static unsigned short string_to_move(const std::string& moveStr,
                                         const Color& piece_color);

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

    virtual std::vector<unsigned short>
    get_available_moves(const int initial_row, const int initial_column,
                            const Board& board) = 0;
    virtual ~Piece();
};

#endif
