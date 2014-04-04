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
    Game(const Color& my_color, const Color& color_on_move, GameType type);
    ~Game();
    bool checked(const Color& color);
    void set_color(const Color& my_color);
    void set_color_on_move(const Color& color_on_move);
    Color get_color();
    Color get_color_on_move();
    std::string send_best_move();
    void get_move(const std::string& moveStr);
    void add_piece(std::string piece, Color color);
    void guess_castlings();
};

#endif
