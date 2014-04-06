#include <iostream>
#include <fstream>
#include <game.hpp>

void input(Logger& logger, std::string& text) {
    std::getline(std::cin, text);
    logger.log(std::string("Received: ") + text);
}

void output(Logger& logger, const std::string text) {
    std::cout << text << "\n";
    logger.log(std::string("Sent:     ") + text);
}

void print_status(Logger& logger, const bool force, const Color my_color,
                  const Color on_move) {
    logger.log(std::string("Status:   I'm ")
               + (my_color == WHITE ? " WHITE" :
                 (my_color == BLACK ? " BLACK" : "NOBODY"))
               + ". It's "
               + (on_move == WHITE ? " WHITE" :
                 (on_move == BLACK ? " BLACK" : "NOBODY"))
               + "'s turn. Force mode: "
               + (force ? " On." : "Off."));
}

int main(int argc, char *argv[]) {
    bool force = false;
    Color last_color_received = NO_COLOR;
    std::string x_command, last_move_received;
    Game *g = NULL;
    Logger logger(argc > 1 ? argv[1] : "low_level_log.txt");

    srand(time(NULL));

    // Make the input unbuffered
    std::cin.rdbuf()->pubsetbuf(0, 0);
    std::cout.rdbuf()->pubsetbuf(0, 0);

    while (1) {
        input(logger, x_command);
        if (x_command == "xboard") {
            output(logger, "");
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
            output(logger, g->send_best_move());
        } else if (x_command.find("usermove") == 0) {
            last_move_received = x_command.substr(9);
            if (!g->get_move(last_move_received))
                output(logger, "Illegal move: " + last_move_received);
            else if (!force)
                output(logger, g->send_best_move());
            else {
                std::string game_result;
                if (!g->get_all_moves(game_result).size())
                    output(logger, game_result);
            }
        } else if (x_command.find("protover") != std::string::npos) {
            output(logger, "feature done=1 sigint=0 sigterm=0 usermove=1");
            output(logger, "feature myname=\"Carlsen's Apprentices\"");
        } else if (x_command == "white") {
            last_color_received = WHITE;
        } else if (x_command == "black") {
            last_color_received = BLACK;
        } else if (x_command == "edit") {
            if (g)
                delete g;
            g = new Game(NO_COLOR, NO_COLOR, CUSTOM);
            last_move_received = std::string();
            input(logger, x_command); // skipping '#'
            input(logger, x_command);
            while (x_command != "c") {
                g->add_piece(x_command, WHITE);
                input(logger, x_command);
            }
            input(logger, x_command);
            while (x_command != ".") {
                g->add_piece(x_command, BLACK);
                input(logger, x_command);
            }
            g->guess_castlings();
        }
        print_status(logger, force, (g ? g->get_color() : NO_COLOR),
                                    (g ? g->get_color_on_move() : NO_COLOR));
    }
    delete g;
    return 0;
}
