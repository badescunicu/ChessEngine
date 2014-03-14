#include <iostream>
#include <fstream>
#include <cstring>

#define WHITE 0
#define BLACK 1

using namespace std;

bool force;
int color;

int main() {
    ofstream out("log.out");
    char x_command[50];

    // Make the input unbuffered
    cin.rdbuf()->pubsetbuf(0, 0);
    cout.rdbuf()->pubsetbuf(0, 0);

    while(1) {
        cin.getline(x_command, 40);
        out << x_command << '\n';
        out.flush();
        if (strcmp(x_command, "xboard") == 0) {
            cout << "\n";
        } else if (strcmp(x_command, "new") == 0) {
            //
        } else if (!strcmp(x_command, "quit")) {
            goto exit;
        } else if (!strcmp(x_command, "force")) {
            force = true;
        } else if (!strcmp(x_command, "go")) {
            force = false;
        } else if (!strcmp(x_command, "white")) {
            color = WHITE;
        } else if (!strcmp(x_command, "black")) {
            color = BLACK;
        } else if (!strcmp(x_command, "resign")) {
            //
        } else if (strlen(x_command) == 4 && x_command[0] <= 'h' &&
                x_command[0] >= 'a' && x_command[1] >= '1' &&
                x_command[1] <= '8' && x_command[2] <= 'h' &&
                x_command[2] >= 'a'&& x_command[3] >= '1' &&
                x_command[3] <= '8') {
            x_command[1] = '0' + '9' - x_command[1];
            x_command[3] = '0' + '9' - x_command[3];
            cout << "move " << x_command << '\n';

            //cout << "resign\n";
            //out << "resign\n";
        } else if (!strcmp(x_command, "post")) {
            cout << "9 156 1084 48000 Nf3 Nc6 Nc3 Nf6\n";
            out << "9 156 1084 48000 Nf3 Nc6 Nc3 Nf6\n";
        } else if (strstr(x_command, "protover")) {
            cout << "feature done=1 sigint=0 sigterm=0\n";
        }
        
        out << "--->SENT\n";
        //cout << "\n";
    }

    exit:
    out.close();

    return 0;
}

