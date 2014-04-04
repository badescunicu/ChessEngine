#include <iostream>
#include <fstream>
#include <cstring>
#include <game.hpp>

enum Mode { SENT, RECEIVED };

void input_output(Logger& logger, Mode direction, std::string text) {
    logger.log(std::string(direction == SENT ? "Sent:     " : "Received: ")
               + text);
    if (direction == SENT)
        std::cout << text << "\n";
}

void print_status(Logger& logger, bool force, Color my_color, Color on_move)
{
    logger.log(std::string("Status:   I'm ")
               + (my_color == WHITE ? " WHITE" :
                 (my_color == BLACK ? " BLACK" : "NOBODY"))
               + ". It's "
               + (on_move == WHITE ? " WHITE" :
                 (on_move == BLACK ? " BLACK" : "NOBODY"))
               + "'s turn. Force mode: "
               + (force ? " On." : "Off."));
}

int main() {
    bool force = false;
    Color last_color_received = NO_COLOR;
    std::string x_command, last_move_received;
    Game *g = NULL;
    Logger logger("low_level_log.txt");

    // Make the input unbuffered
    std::cin.rdbuf()->pubsetbuf(0, 0);
    std::cout.rdbuf()->pubsetbuf(0, 0);

    while (1) {
        std::getline(std::cin, x_command);
        input_output(logger, RECEIVED, x_command);
        if (x_command == "xboard") {
            input_output(logger, SENT, "");
        } else if (x_command == "new") {
            force = false;
            last_move_received = std::string();
            if (g)
                delete g;
            g = new Game(BLACK, WHITE, DEFAULT);
        } else if (x_command == "quit") {
            return 0;
        } else if (x_command == "force") {
            force = true;
            if (g)
                g->set_color(NO_COLOR);
        } else if (x_command == "go") {
            force = false;
            if (g->get_color_on_move() == NO_COLOR)
                g->set_color_on_move(last_color_received);
            g->set_color(g->get_color_on_move());
            input_output(logger, SENT, g->send_best_move());
        } else if (x_command.find("usermove") == 0) {
            last_move_received = x_command.substr(9);
            g->get_move(last_move_received);
            if (!force)
                input_output(logger, SENT, g->send_best_move());
        } else if (x_command.find("protover") != std::string::npos) {
            input_output(logger, SENT, "feature done=1 sigint=0 sigterm=0 usermove=1");
            input_output(logger, SENT, "feature myname=\"Carlsen's Apprentices\"");
        } else if (x_command == "white") {
            last_color_received = WHITE;
        } else if (x_command == "black") {
            last_color_received = BLACK;
        } else if (x_command == "edit") {
            if (g)
                delete g;
            g = new Game(NO_COLOR, NO_COLOR, CUSTOM);
            last_move_received = std::string();
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
            g->guess_castlings();
        }
        print_status(logger, force, (g ? g->get_color() : NO_COLOR),
                                    (g ? g->get_color_on_move() : NO_COLOR));
    }
    delete g;
    return 0;
}
