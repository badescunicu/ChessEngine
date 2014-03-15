#include <game.hpp>
#include <cstdio>

int main()
{ 
  Game game(WHITE);
  int a;
  while(1) {
    game.send_best_move();
    getchar();
  }
  return 0;
}

