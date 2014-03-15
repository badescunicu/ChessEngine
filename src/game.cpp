#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <game.hpp>

using namespace std;

void think_and_move(const string &last_move_received)
{
    /* here we can resign like this: cout << "resign\n"; */

    if (last_move_received.size() == 0) {
        /* the first move */
        cout << "move c2c3\n";
    } else {
        /* creating a mirrored move */
        string temp(last_move_received);
        temp[1] = '0' + '9' - temp[1];
        temp[3] = '0' + '9' - temp[3];
        cout << "move " << temp << "\n";
    }
}

int main() {
    bool force;
    Color my_color, color_on_move;
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
            my_color = BLACK;
            color_on_move = WHITE;
            last_move_received = string();
            g = new Game(my_color);
            log << "Created new game\n";
            log.flush();
        } else if (x_command ==  "quit") {
            return 0;
        } else if (x_command ==  "force") {
            force = true;
            my_color = NO_COLOR;
        } else if (x_command ==  "go") {
            /* swap colors */
            force = false;
            my_color = color_on_move;
            g->set_color(my_color);
            if(last_move_received.size() > 0)
              g->get_move(last_move_received);
            else
              cout << g->send_best_move() << '\n';
            if(color_on_move == WHITE)
              color_on_move = BLACK;
            else
              color_on_move = WHITE;
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
                if(color_on_move == WHITE)
                  color_on_move = BLACK;
                else
                  color_on_move = WHITE;
            } else {

              if(color_on_move == WHITE)
                color_on_move = BLACK;
              else
                color_on_move = WHITE;

              g->get_move(last_move_received);
              cout << g->send_best_move() << '\n';

              if(color_on_move == WHITE)
                color_on_move = BLACK;
              else
                color_on_move = WHITE;
            }

        } else if (x_command.find("protover") != string::npos) {
          cout << "feature done=1 sigint=0 sigterm=0 usermove=1\n";
          cout << "feature myname=\"Carlsen's Apprentices\"\n";
        }
    }
    delete g;
    return 0;
}
