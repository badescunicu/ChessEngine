#include <cassert>
#include <iostream>
#include <fstream>
#include <functional>
#include <ctime>
#include <vector>
#include "game.hpp"
#include "piece.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"

using std::string;
using std::make_pair;
using std::vector;
using std::ofstream;

Game::Game(const Color& my_color, const Color& color_on_move, GameType type) :
        board(type, color_on_move), my_color(my_color), pieces(7) {
    pieces[1] = new Pawn();
    pieces[2] = new Knight();
    pieces[3] = new Bishop();
    pieces[4] = new Rook();
    pieces[5] = new Queen();
    pieces[6] = new King();
}

Game::~Game() {
    for (int i = 1; i < 7; ++i)
        delete pieces[i];
}

bool Game::checked(const Color& color) {
    return board.check_for_chess(color);
}

void Game::set_color(const Color& my_color) {
    this->my_color = my_color;
}

void Game::set_color_on_move(const Color& color_on_move) {
    board.set_color_on_move(color_on_move);
}

Color Game::get_color() {
    return my_color;
}

Color Game::get_color_on_move() {
    return board.get_color_on_move();
}

string Game::send_best_move() {
    int size = BOARD_SIZE;
    vector<unsigned short> moves;
    if (checked(board.get_color_on_move()))
        return "resign";

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            PieceType piece = static_cast<PieceType>(board.get_piece(i, j));
            if (piece && !(COLOR_OF(piece) ^ my_color)) {
                vector<unsigned short> valid_moves = pieces[piece & 7]->get_available_moves(i, j, board);
                moves.insert(moves.end(), valid_moves.begin(), valid_moves.end());
            }
        }

    srand(time(NULL));
    if (moves.size() == 0)
        return "resign";
    unsigned short move = moves[rand() % moves.size()];
    board.apply_move(move);
    return "move " + Piece::move_to_string(move);
} 

void Game::get_move(const string& move_str) {
    board.apply_move(Piece::string_to_move(move_str, board.get_color_on_move()));
}

void Game::add_piece(string piece, Color color) {
    // piece looks like this: "Pc3"
    board.set_pos_value(piece[2] - 1 - '0', piece[1] - 'a', Piece::char_to_piece(piece[0], color));
}

// Tries to deduce which castlings are available (used in Edit Mode only)
void Game::guess_castlings() {
    board.guess_castlings();
}
