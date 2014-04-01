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
using std::cerr;
using std::make_pair;
using std::vector;
using std::ofstream;

class Game {
private:
  vector<Piece*> pieces;
  Board board;
  Color color;
public:

  Game(const Color& color, GameType type) : board(type), color(color), pieces(16) {
      pieces[1] = new Pawn();
      pieces[2] = new Knight();
      pieces[3] = new Bishop();
      pieces[4] = new Rook();
      pieces[5] = new Queen();
      pieces[6] = new King();

      pieces[9] = new Pawn();
      pieces[10] = new Knight();
      pieces[11] = new Bishop();
      pieces[12] = new Rook();
      pieces[13] = new Queen();
      pieces[14] = new King();
  } 

  void start() {
  }

  void set_color(const Color& color) {
      this->color = color;
  }

  Color get_color() {
      return this->color;
  }


  string send_best_move() {
      int size = Board::BOARD_SIZE;
      vector<short> moves;
      char** char_board = board.getBoard();

      for(char i = 0; i < size; ++i)
          for(char j = 0; j < size; ++j)
              if(char_board[i][j] != 0 && !(COLOR_OF(char_board[i][j]) ^ color)) {
                  //cerr << COLOR_OF(char_board[i][j]) << ' ' << color << '\n';
                  vector<short> valid_moves = pieces[char_board[i][j]]->get_all_moves(char_board, i, j);
                  moves.insert(moves.end(), valid_moves.begin(), valid_moves.end());
                } 

      srand(time(0));
      if(moves.size() == 0)
          return "resign";
      short move = moves[rand() % moves.size()];
      string ret = to_string(move); 
      board.apply_move(ret); 
      return "move " + ret;
  } 

 
  void get_move(const string& move) {
      board.apply_move(move);
  }

  /*
  void add_piece(string piece, Color color) {
      board.add_piece(piece, color);
  }*/
};
#endif
