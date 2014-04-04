#ifndef __BOARD__HPP
#define __BOARD__HPP
#include <piece_type.hpp>
#include <logger.hpp>

#define BOARD_SIZE 8
#define COLOR_OF(piece) ((piece & 8) >> 3)

enum Color { WHITE, BLACK, NO_COLOR };
enum GameType { DEFAULT, CUSTOM };
enum CastlingType { QUEENSIDE, KINGSIDE };

inline bool inside(int i) {
    return i >= 0 && i < BOARD_SIZE;
}

inline bool inside(int i, int j) {
    return inside(i) && inside(j);
}

class Board {
public:
    Board(GameType type, const Color& color_on_move);
    unsigned int get_piece(const int pos_x, const int pos_y) const;
    void get_king_position(const Color& color, int& row, int& column);
    bool valid_castling(const Color& color, CastlingType type) const;
    void set_castling(const Color& color, CastlingType type, bool enabled);
    Color get_color_on_move() const;
    void set_color_on_move(const Color& color_on_move);
    bool valid_en_passant(int& row, int& column) const;
    void change_turn();
    void guess_castlings();
    bool apply_move(const unsigned short move);
    // Puts the piece on the given position
    void set_pos_value(const int row, const int column, const PieceType piece);
    bool check_for_chess(const Color& color);
    void print();
    ~Board();
private:
    unsigned int board[9];
    Logger logger;
};

#endif
