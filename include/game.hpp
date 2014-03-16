#ifndef _GAME_
#define _GAME_
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <functional>
#include <ctime>
#include "board.hpp"

using std::string;
using std::make_pair;
using std::vector;
using std::ofstream;

class Game {
private:
  Board board;
  Color color;
public:
  Game(const Color& color, GameType type) : board(type), color(color) {}

  void start() {
  }

  bool check_value(int row, int col, int value) {
    if(board[row][col] == NULL)
      return false;
    return (board[row][col]->getValue() == value);
  }

  bool checked() {
    Position pos = make_pair((color == WHITE) ? 0 : 7, 4);
    int line_inc = (color == WHITE) ? 1 : -1;
    int row, column;
    for(int i = 1; i < 8; i++) {
      row = pos.first + i * line_inc;
      column = pos.second;
      if(board[row][column] && board[row][column]->color == color)
        break;
      if(check_value(row, column, QUEEN_VALUE) || check_value(row, column, ROOK_VALUE))
        return true;
      if(board[row][column] && board[row][column]->color != color)
        break;
    }

    for(int i = 1; i <= 3; i++) {
      row = pos.first;
      column = pos.second + i; 
      if(board[row][column] && board[row][column]->color == color)
        break;
      if(check_value(row, column, QUEEN_VALUE) || check_value(row, column, ROOK_VALUE))
        return true;
      if(board[row][column] && board[row][column]->color != color)
        break;
    }

    for(int i = 1; i <= 4; i++) {
      row = pos.first;
      column = pos.second - i; 
      if(board[row][column] && board[row][column]->color == color)
        break;
      if(check_value(row, column, QUEEN_VALUE) || check_value(row, column, ROOK_VALUE))
        return true;
      if(board[row][column] && board[row][column]->color != color)
        break;
    }
    
    for(int i = 1; i <= 3; i++) {
      row = pos.first + i * line_inc;
      column = pos.second + i;
      if(board[row][column] && board[row][column]->color == color)
        break;
      if(check_value(row, column, QUEEN_VALUE) || check_value(row, column, BISHOP_VALUE))
        return true;
      if(board[row][column] && board[row][column]->color != color)
        break;
    }

    for(int i = 1; i <= 4; i++) {
      row = pos.first + i * line_inc;
      column = pos.second - i;
      if(board[row][column] && board[row][column]->color == color)
        break;
      if(check_value(row, column, QUEEN_VALUE) || check_value(row, column, BISHOP_VALUE))
        return true;
      if(board[row][column] && board[row][column]->color != color)
        break;
    }

    int dl[] = {1, 2, 2, 1};
    int dc[] = {2, 1, -1, 2};

    for(int i = 0; i < 4; i++) {
      row = pos.first + dl[i] * line_inc;
      column = pos.second + dc[i];
      if(check_value(row, column, KNIGHT_VALUE) && board[row][column]->color != color) 
        return true;
    }

    row = pos.first + line_inc;
    column = pos.second - 1;
    if(check_value(row, column, PAWN_VALUE) && board[row][column]->color != color)
      return true;
    column = pos.second + 1;
    if(check_value(row, column, PAWN_VALUE) && board[row][column]->color != color)
      return true;

    return false;
  }



  void set_color(const Color& color) {
    this->color = color;
  }

  Color get_color() {
    return this->color;
  }

  string send_best_move() {
    int size = Board::BOARD_SIZE;
    vector<Move> moves;
    if(checked())
      return "resign";
    string ret("move ");  

    for(int i = 0; i < size; i++)
      for(int j = 0; j < size; j++)
        if(board[i][j] != NULL && board[i][j]->color == color) {
          vector<Move> valid_moves = board[i][j]->get_all_moves(
              [&](int row, int column) -> bool
              {
              return ((row >= 0 && row < 8) && (column >= 0 && column < 8) &&
                      (board[row][column] == NULL || board[row][column]->color != color));
              });
          moves.insert(moves.end(), valid_moves.begin(), valid_moves.end());
        }        
    srand(time(0));
    if(moves.size() == 0)
      return "resign";
    Move move = moves[rand() % moves.size()];

    ret.push_back(move.first.second + 'a'); 
    ret.push_back(move.first.first + 1 + '0');
    ret.push_back(move.second.second + 'a');
    ret.push_back(move.second.first + 1 + '0');

    board.apply_move(move); 
    return ret;
  } 

  void get_move(string moveStr) {
    Move move = make_pair(make_pair(moveStr[1] - 1 - '0', moveStr[0] - 'a'),
                          make_pair(moveStr[3] - 1 - '0', moveStr[2] - 'a'));
    board.apply_move(move);
  }

  void add_piece(string piece, Color color) {
    board.add_piece(piece, color);
  }
};
#endif
