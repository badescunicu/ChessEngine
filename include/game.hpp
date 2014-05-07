#ifndef _GAME_
#define _GAME_
#include <vector>
#include "piece.hpp"

class Game {
private:
    Board board;
    Color my_color;
    std::vector<Piece *> pieces;
public:
    Game(const Color my_color, const Color color_on_move, const GameType type);
    ~Game();
    bool checked(const Color color) const;
    void set_color(const Color my_color);
    void set_color_on_move(const Color color_on_move);
    Color get_color() const;
    Color get_color_on_move() const;
    bool insuf_material(const int knights[], const int bishops[][2],
                        const int anything_else[]) const;
    std::vector<unsigned short> get_all_moves(std::string& game_result) const;
    std::vector<unsigned short> get_all_moves(const Board& board, std::string& game_result) const;
    std::string send_best_move();
    float eval(const Board& board) const;
    std::pair<float, unsigned short> alpha_beta(const Board& init, const int depth, float alpha,
                                                float beta) const;
    bool get_move(const std::string& move_str);
    void add_piece(const std::string& piece, const Color color);
    void guess_castlings();
};

#endif
