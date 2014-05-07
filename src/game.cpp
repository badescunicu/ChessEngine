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
    return get_all_moves(board, game_result);
}

vector<unsigned short> Game::get_all_moves(const Board& board, string& game_result) const { 
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
    vector<unsigned short> moves = get_all_moves(board, game_result);
    if (!moves.size())
        return game_result;
    //unsigned short move = moves[rand() % moves.size()];
    unsigned short move = alpha_beta(board, 4, -INF, INF).second;
    board.apply_move(move);
    string ret = "move " + Piece::move_to_string(move);

    // Check if the opponent can move
    moves = get_all_moves(board, game_result);
    if (!moves.size())
        return ret + "\n" + game_result;

    return ret;
}

// evaluation function for Alpha-Beta
float Game::eval(const Board& board) const {
    int score = 0;
    Color on_move = board.get_color_on_move();

    // for each color, bits are set whether there are pawns on that column or not
    unsigned char pawns_on_file[2];
    // keeps the line of the most backward pawn on the file
    char pawn_line[2][BOARD_SIZE];
    // for each player, keeps a list with the columns of pawns
    std::vector<char> pawn_files[2];

    pawn_files[0].reserve(BOARD_SIZE);
    pawn_files[1].reserve(BOARD_SIZE);
    pawns_on_file[0] = pawns_on_file[1] = 0;

    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j) {
            PieceType piece = static_cast<PieceType>(board.get_piece(i, j));
            float value;
            switch (piece) {
                case PAWN_W: case PAWN_B: {
                    Color color = static_cast<Color>(COLOR_OF(piece));
                    value = 1;
                    pawn_files[color].push_back(j);
                    if (pawns_on_file[color] & (1 << j))
                        value -= 0.5; // doubled pawn
                    else
                        pawns_on_file[color] |= 1 << j;
                    if (color == WHITE)
                        pawn_line[color][j] = i < pawn_line[color][j] ? i : pawn_line[color][j];
                    else
                        pawn_line[color][j] = i > pawn_line[color][j] ? i : pawn_line[color][j];
                }
                break;
                case KNIGHT_W: case KNIGHT_B: value = 3; break;
                case BISHOP_W: case BISHOP_B: value = 3; break;
                case ROOK_W: case ROOK_B: value = 5; break;
                case QUEEN_W: case QUEEN_B: value = 9; break;
                default: value = 0;
            }
            if (!(COLOR_OF(piece) ^ on_move))
                score += value;
            else
                score -= value;
        }
    // count isolated pawns
    for (int color = 0; color <= 1; ++color)
        for (unsigned int i = 0; i < pawn_files[color].size(); ++i) {
            char column = pawn_files[color][i];
            if ((!column || ((pawns_on_file[color] & (1 << (column - 1))) == 0)) &&
                ((column == BOARD_SIZE - 1) || ((pawns_on_file[color] & (1 << (column + 1))) == 0))) {
                if (color == on_move)
                    score -= 0.5;
                else
                    score += 0.5;
            }
        }
    // count backward pawns
    for (int color = 0; color <= 1; ++color)
        for (int file = 0; file < BOARD_SIZE; ++file)
            if (pawns_on_file[color] & (1 << file)) {
                // if there is a pawn behind on the left
                if (file > 0 && (pawns_on_file[color] & (1 << (file - 1))))
                    if ((color == WHITE && pawn_line[color][file - 1] <= pawn_line[color][file]) ||
                        (color == BLACK && pawn_line[color][file - 1] >= pawn_line[color][file]))
                        continue;
                bool backward = true;
                // if there is a pawn behind on the right
                if (file < BOARD_SIZE - 1 && (pawns_on_file[color] & (1 << (file + 1)))) {
                    if ((color == WHITE && pawn_line[color][file + 1] <= pawn_line[color][file]) ||
                        (color == BLACK && pawn_line[color][file + 1] >= pawn_line[color][file]))
                        backward = false;
                    else
                        backward = true;
                }
                if (backward) {
                    if (color == on_move)
                        score -= 0.5;
                    else
                        score += 0.5;
                }
            }
    return score;
}

std::pair<float, unsigned short> Game::alpha_beta(const Board& init, const int depth,
                                                  float alpha, float beta) const {
    if (!depth)
        return std::pair<int, unsigned short>(eval(init), 0); 

    string game_result;
    vector<unsigned short> moves = get_all_moves(init, game_result);
    if (!moves.size()) {
        Color winner = NO_COLOR;
        if (game_result.substr(0, 3) == "0-1")
            winner = BLACK;
        else if (game_result.substr(0, 3) == "1-0")
            winner = WHITE;
        float score = init.get_color_on_move() == winner ? INF : -INF;
        return std::pair<int, unsigned short>(score, 0);
    }

    int move_index = 0;

    for (unsigned int i = 0; i < moves.size(); ++i) {
        Board next = Board(init);
        next.apply_move(moves[i]);
        float score = -alpha_beta(next, depth - 1, -beta, -alpha).first;

        if (score > alpha) {
            alpha = score;
            move_index = i;
        }

        if(alpha >= beta)
            break;
    }

    return std::pair<float, unsigned short>(alpha, moves[move_index]);
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
