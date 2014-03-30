#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <game.hpp>

void change_turn(Color &color) {
    if (color == WHITE)
      color = BLACK;
    else if (color == BLACK)
      color = WHITE;
}

void output(std::ofstream &log, std::string text) {
    log << "Sent:     " << text << "\n";
    log.flush();
    std::cout << text << "\n";
}

void print_status(std::ofstream &log, bool force, Color me, Color on_move)
{
    log << "Status:   I'm ";
    switch (me) {
      case WHITE: log << " WHITE"; break;
      case BLACK: log << " BLACK"; break;
      default:    log << "NOBODY";
    }
    log << ". It's ";
    switch (on_move) {
      case WHITE: log << " WHITE"; break;
      case BLACK: log << " BLACK"; break;
      default:    log << "NOBODY";
    }
    log << "'s turn. Force mode: " << (force ? " On." : "Off.") << "\n";
    log.flush();
}

int main() {
    bool force = false;
    Color color_on_move = NO_COLOR, last_color_received = NO_COLOR;
    std::string x_command, last_move_received;
    Game *g = NULL;

    std::ofstream log("log");
    // Make the input unbuffered
    std::cin.rdbuf()->pubsetbuf(0, 0);
    std::cout.rdbuf()->pubsetbuf(0, 0);

    while (1) {
      std::getline(std::cin, x_command);
      log << "Received: " << x_command << '\n';
      log.flush();
      if (x_command == "xboard") {
        output(log, "");
      } else if (x_command == "new") {
        force = false;
        color_on_move = WHITE;
        last_move_received = string();
        if (g)
          delete g;
        g = new Game(BLACK, DEFAULT);
      } else if (x_command ==  "quit") {
        return 0;
      } else if (x_command ==  "force") {
        force = true;
        if (g)
          g->set_color(NO_COLOR);
      } else if (x_command ==  "go") {
        force = false;
        if (color_on_move == NO_COLOR)
           color_on_move = last_color_received;
        g->set_color(color_on_move);
        output(log, g->send_best_move());
        change_turn(color_on_move);
      } else if (x_command.find("usermove") == 0) {
        last_move_received = x_command.substr(9);
        if (force) {
          g->get_move(last_move_received);
          change_turn(color_on_move);
        } else {
          change_turn(color_on_move);
          g->get_move(last_move_received);
          output(log, g->send_best_move());
          change_turn(color_on_move);
        }
      } else if (x_command.find("protover") != string::npos) {
        output(log, "feature done=1 sigint=0 sigterm=0 usermove=1");
        output(log, "feature myname=\"Carlsen's Apprentices\"");
      } else if (x_command ==  "white") {
        last_color_received = WHITE;
      } else if (x_command ==  "black") {
        last_color_received = BLACK;
      } else if (x_command ==  "edit") {
        if (g)
          delete g;
        g = new Game(NO_COLOR, CUSTOM);
        last_move_received = string();
        color_on_move = NO_COLOR;
        std::getline(std::cin, x_command); // skipping '#'
        std::getline(std::cin, x_command);
        while (x_command != "c") {
          g->add_piece(x_command, WHITE);
          std::getline(std::cin, x_command);
        }
        std::getline(std::cin, x_command);
        while (x_command != ".") {
          g->add_piece(x_command, BLACK);
          std::getline(std::cin, x_command);
        }
      }
      print_status(log, force, (g ? g->get_color() : NO_COLOR), color_on_move);
    }
    delete g;
    return 0;
}
