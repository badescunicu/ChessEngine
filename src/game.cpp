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

Game::Game(const Color my_color, const Color color_on_move, const GameType type) :
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

bool Game::checked(const Color color) const {
    return board.checked(color);
}

void Game::set_color(const Color my_color) {
    this->my_color = my_color;
}

void Game::set_color_on_move(const Color color_on_move) {
    board.set_color_on_move(color_on_move);
}

Color Game::get_color() const {
    return my_color;
}

Color Game::get_color_on_move() const {
    return board.get_color_on_move();
}

bool Game::insuf_material(const int knights[], const int bishops[][2],
                          const int anything_else[]) const {
    if (anything_else[0] || anything_else[1])
        return false;

    // King vs King
    if (!knights[0] && !knights[1] &&
        !bishops[0][0] && !bishops[0][1] && !bishops[1][0] && !bishops[1][1])
        return true;

    // King and Bishop vs King
    if (!knights[0] && !knights[1] &&
        (bishops[0][0] + bishops[0][1] + bishops[1][0] + bishops[1][1] == 1))
        return true;

    // King and Knight vs King
    if (knights[0] + knights[1] == 1 &&
        !bishops[0][0] && !bishops[0][1] && !bishops[1][0] && !bishops[1][1])
        return true;

    // King and Bishops vs King and Bishops, all the Bishops of the same color
    if ((!knights[0] && !knights[1]) &&
        ((!bishops[0][0] && !bishops[0][1]) || (!bishops[1][0] && !bishops[1][1])))
        return true;

    return false;
}

vector<unsigned short> Game::get_all_moves(string& game_result) const { 
    vector<unsigned short> moves;
    int size = BOARD_SIZE;

    int knights[2] = {};
    int bishops[2][2] = {}; // Dimension signification: [square_color][piece_color]
    int anything_else[2] = {};

    Color on_move = board.get_color_on_move();
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            PieceType piece = static_cast<PieceType>(board.get_piece(i, j));
            if (piece) {
                if (!(COLOR_OF(piece) ^ on_move)) {
                    vector<unsigned short> valid_moves = pieces[piece & 7]->get_available_moves(i, j, board);
                    moves.insert(moves.end(), valid_moves.begin(), valid_moves.end());
                }
                if (piece == KNIGHT_W || piece == KNIGHT_B)
                    ++knights[COLOR_OF(piece)];
                else if (piece == BISHOP_W || piece == BISHOP_B)
                    ++bishops[(i & 1) ^ (j & 1)][COLOR_OF(piece)];
                else if (piece != KING_W && piece != KING_B)
                    ++anything_else[COLOR_OF(piece)];
            }
        }
    if (insuf_material(knights, bishops, anything_else)) {
        game_result = "1/2-1/2 {Insufficient mating material}";
        moves.clear();
    } else if (!moves.size()) {
        if (board.checked(board.get_color_on_move())) {
            if (board.get_color_on_move() == WHITE)
                game_result = "0-1 {Black mates}";
            else
                game_result = "1-0 {White mates}";
        } else
            game_result = "1/2-1/2 {Stalemate}";
    } else
        game_result = "";
    return moves;
}

string Game::send_best_move() {
    string game_result;
    vector<unsigned short> moves = get_all_moves(game_result);
    if (!moves.size())
        return game_result;
    unsigned short move = moves[rand() % moves.size()];
    board.apply_move(move);
    string ret = "move " + Piece::move_to_string(move);

    // Check if the opponent can move
    moves = get_all_moves(game_result);
    if (!moves.size())
        return ret + "\n" + game_result;

    return ret;
} 

bool Game::get_move(const string& move_str) {
    return board.apply_move(Piece::string_to_move(move_str, board.get_color_on_move()));
}

void Game::add_piece(const string& piece, const Color color) {
    // piece looks like this: "Pc3"
    board.set_pos_value(piece[2] - 1 - '0', piece[1] - 'a', Piece::char_to_piece(piece[0], color));
}

// Tries to deduce which castlings are available (used in Edit Mode only)
void Game::guess_castlings() {
    board.guess_castlings();
}
