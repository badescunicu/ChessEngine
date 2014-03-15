#ifndef _GAME_
#define _GAME_
#include <cassert>
#include <iostream>
#include <functional>
#include "board.hpp"

class Game {
private:
  Board board;
  Color color;
public:
  Game(const Color& color) : board(), color(color) {}

  void start() {
  }

  void send_best_move() {
    int size = Board::BOARD_SIZE;
    std::vector<Move> ret;
    for(int i = 0; i < size; i++)
      for(int j = 0; j < size; j++)
        if(board[i][j] != NULL && board[i][j]->color == color) {
          std::vector<Move> moves = board[i][j]->get_all_moves(
          [&](int row, int column) -> bool
          {
            return ((row >= 0 && row < 8) && (column >= 0 && column < 8) &&
                    (board[row][column] == NULL || board[row][column]->color != color));
          });
          ret.insert(ret.end(), moves.begin(), moves.end());
        }      
      board.apply_move(ret[0]); 
  } 

};
#endif
