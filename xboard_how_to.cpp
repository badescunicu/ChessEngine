#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#define WHITE 0
#define BLACK 1
#define NO_COLOR 2
#define COMMAND_LENGTH 50

using namespace std;

void think_and_move(char *last_move_received)
{
    /* here we can resign like this: cout << "resign\n"; */

    if (!strlen(last_move_received)) {
        /* the first move */
        cout << "move c2c3\n";
    } else {
        /* creating a mirrored move */
        char *temp = strdup(last_move_received);
        temp[1] = '0' + '9' - temp[1];
        temp[3] = '0' + '9' - temp[3];
        cout << "move " << temp << "\n";
        free(temp);
    }
}

int main() {
    bool force;
    int my_color, color_on_move;
    char x_command[COMMAND_LENGTH], last_move_received[COMMAND_LENGTH] = {0};

    // Make the input unbuffered
    cin.rdbuf()->pubsetbuf(0, 0);
    cout.rdbuf()->pubsetbuf(0, 0);

    while (1) {
        cin.getline(x_command, COMMAND_LENGTH);
        if (!strcmp(x_command, "xboard")) {
            cout << "\n";
        } else if (!strcmp(x_command, "new")) {
            force = false;
            my_color = BLACK;
            color_on_move = WHITE;
	    last_move_received[0] = 0;
        } else if (!strcmp(x_command, "quit")) {
            return 0;
        } else if (!strcmp(x_command, "force")) {
            force = true;
            my_color = NO_COLOR;
        } else if (!strcmp(x_command, "go")) {
            /* swap colors */
            force = false;
            my_color = color_on_move;
            think_and_move(last_move_received);
            color_on_move = 1 - color_on_move;
        } else if (strstr(x_command, "usermove") == x_command) {

            /* x_command is like this: "usermove c8h3" */
            strcpy(last_move_received, x_command + 9);
            if (force) {

                /* This happens when the engine is loaded after several moves
                 * were made. Xboards tells what the moves were. We have to
                 * simulate them without giving any response.
                 */
                color_on_move = 1 - color_on_move;
            } else {
                color_on_move = 1 - color_on_move;
                think_and_move(last_move_received);
                color_on_move = 1 - color_on_move;
            }

        } else if (strstr(x_command, "protover")) {
            cout << "feature done=1 sigint=0 sigterm=0 usermove=1\n";
            cout << "feature myname=\"Carlsen's Apprentices\"\n";
        }
    }

    return 0;
}
