#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <game.hpp>

#define change_turn(color) (color == WHITE ? color = BLACK : color = WHITE)

using namespace std;

int main() {
    bool force;
    Color color_on_move;
    std::string x_command, last_move_received;
    Game *g = NULL;

    ofstream log("log");
    // Make the input unbuffered
    cin.rdbuf()->pubsetbuf(0, 0);
    cout.rdbuf()->pubsetbuf(0, 0);

    while (1) {
        std::getline(std::cin, x_command);
        log << x_command << '\n';
        log.flush();
        if (x_command == "xboard") {
            cout << "\n";
        } else if (x_command == "new") {
            force = false;
            color_on_move = WHITE;
            last_move_received = string();
            g = new Game(BLACK);
            log << "Created new game\n";
            log.flush();
        } else if (x_command ==  "quit") {
            return 0;
        } else if (x_command ==  "force") {
            force = true;
            g->set_color(NO_COLOR);
        } else if (x_command ==  "go") {
            /* swap colors */
            force = false;
            g->set_color(color_on_move);
            cout << g->send_best_move() << '\n';
	    change_turn(color_on_move);
        } else if (x_command.find("usermove") == 0) {

            /* x_command is like this: "usermove c8h3" */
            
            log << "Receveid move " << x_command << '\n';
            log.flush();
            last_move_received = x_command.substr(9);
            if (force) {

                /* This happens when the engine is loaded after several moves
                 * were made. Xboards tells what the moves were. We have to
                 * simulate them without giving any response.
                 */
                g->get_move(last_move_received);
		change_turn(color_on_move);
            } else {
              change_turn(color_on_move);

              g->get_move(last_move_received);
              cout << g->send_best_move() << '\n';
              
	      change_turn(color_on_move);
            }

        } else if (x_command.find("protover") != string::npos) {
          cout << "feature done=1 sigint=0 sigterm=0 usermove=1\n";
          cout << "feature myname=\"Carlsen's Apprentices\"\n";
        }
    }
    delete g;
    return 0;
}
