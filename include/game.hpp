#ifndef _GAME_
#define _GAME_
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <functional>
#include "board.hpp"

using std::string;
using std::make_pair;
using std::vector;
using std::ofstream;

class Game {
private:
  Board board;
  Color color;
  ofstream log;
public:
  Game(const Color& color) : board(), color(color), log("game.log") {
  }

  void start() {
  }

  bool checked() {
    return false;
  }

  void set_color(const Color& color) {
    this->color = color;
  }

  string send_best_move() {
    int size = Board::BOARD_SIZE;
    vector<Move> moves;
    if(checked())
      return "resign\n";
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

      log << ret << '\n';
      log.flush();
      board.apply_move(move); 
      return ret;
  } 

  void get_move(string moveStr) {
    Move move = make_pair(make_pair(moveStr[1] - 1 - '0', moveStr[0] - 'a'),
                          make_pair(moveStr[3] - 1 - '0', moveStr[2] - 'a'));
    board.apply_move(move);
  }
};
#endif
