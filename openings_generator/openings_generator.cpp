#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
#include <vector>
#include <queue>

// the maximum number of moves for each game (the rest will be ignored)
#define MAX_DEPTH 35

class GameTree {
public:
    GameTree() : games(0), move(0) { };
    unsigned short get_move() const;
    std::vector<GameTree *> get_children() const;
    void set_move(const unsigned short move);
    void add(const std::vector<unsigned short>& moves, const unsigned int pos);
    void sort(const int depth, const bool white, const bool black);
    void print();
private:
    int games;           // how many games include this node
    unsigned short move; // the move from the parent node
    std::vector<GameTree *> children;
};

// information associated with a nodes during BFS
class NodeInfo {
public:
    NodeInfo(GameTree *node, const int id, const int dad, const int depth, const bool white,
        const bool black) : node(node), id(id), dad(dad), depth(depth), white(white), black(black) { };
    GameTree *node;
    int id, dad, depth;
    bool white, black;
};

class NodeRecord {
public:
    NodeRecord(const unsigned int dad, const unsigned short move) : dad(dad), move(move) { };
    unsigned int dad :20;
    unsigned short move :12;
};

unsigned short GameTree::get_move() const {
    return move;
}

std::vector<GameTree *> GameTree::get_children() const {
    return children;
}

void GameTree::set_move(const unsigned short move) {
    this -> move = move;
}

void GameTree::add(const std::vector<unsigned short>& moves, const unsigned int pos) {
    ++games;
    if (pos < moves.size()) {
        for (unsigned int i = 0; i < children.size(); ++i)
            if (children[i] -> get_move() == moves[pos]) {
                children[i] -> add(moves, pos + 1);
                return;
            }
        children.push_back(new GameTree);
        children[children.size() - 1] -> set_move(moves[pos]);
        children[children.size() - 1] -> add(moves, pos + 1);
    }
}

/* For every node, the first son will be the one that the most used move leads to.
 * white = true, if the node is useful if we play by white or false, otherwise
 * black = true, if the node is useful if we play by black or false, otherwise
 */
void GameTree::sort(const int depth, const bool white, const bool black) {
    if (children.size() > 0) {
        int max_games = 0, pos;
        for (unsigned int i = 0; i < children.size(); ++i)
            if (children[i] -> games > max_games) {
                max_games = children[i] -> games;
                pos = i;
            }
        GameTree *aux = children[0];
        children[0] = children[pos];
        children[pos] = aux;
        children[0] -> sort(depth + 1, white, black);
        bool useful_if_white, useful_if_black;
        useful_if_white = white && depth % 2 == 1;
        useful_if_black = black && depth % 2 == 0;
        if (useful_if_white || useful_if_black)
            for (unsigned int i = 1; i < children.size(); ++i)
                children[i] -> sort(depth + 1, useful_if_white, useful_if_black);
    }
}

void GameTree::print() {
    std::ofstream g("output", std::ofstream::out | std::ofstream::binary);
    // using BFS to count the nodes
    int node_number = 0;
    std::queue<NodeInfo> Q;
    Q.push(NodeInfo(this, 0, -1, 0, true, true));
    while (!Q.empty()) {
        NodeInfo first = Q.front();
        GameTree *node = first.node;
        Q.pop();
        if (first.dad != -1) {
            NodeRecord to_write(first.dad, node -> get_move());
            g.write((char *)&to_write, sizeof(NodeRecord));
        }
        if (node -> get_children().size() > 0) {
            ++node_number;
            Q.push(NodeInfo(node -> get_children()[0], node_number, first.id, first.depth + 1,
                   first.white, first.black));
            bool useful_if_white, useful_if_black;
            useful_if_white = first.white && first.depth % 2 == 1;
            useful_if_black = first.black && first.depth % 2 == 0;
            if ((useful_if_white || useful_if_black) && first.depth < MAX_DEPTH - 1)
                for (unsigned int i = 1; i < node -> get_children().size(); ++i) {
                    ++node_number;
                    Q.push(NodeInfo(node -> get_children()[i], node_number, first.id,
                           first.depth + 1, useful_if_white, useful_if_black));
                }
        }
    }
    g.close();
}

inline unsigned short string_to_move(const std::string& move) {
    int initial_row = move[1] - 1 - '0';
    int initial_column = move[0] - 'a';
    int destination_row = move[3] - 1 - '0';
    int destination_column = move[2] - 'a';
    
    unsigned short result = 0;
    result |= initial_row;
    result |= initial_column << 3;
    result |= destination_row << 6;
    result |= destination_column << 9;

    return result;
}

int main() {
    std::string game;
    GameTree tree;
    bool ignore_next = false;
    while (std::getline(std::cin, game)) {
        if (game.find("[FEN") == 0)
            ignore_next = true; // ignore games that start from a particular position

        // if the line starts with a lowercase letter, then it represents a game
        if (game.length() > 0 && islower(game[0])) {
            if (!ignore_next) {
                std::vector<unsigned short> moves;
                std::stringstream ss(game);
                std::string move;
                int moves_no = 0;
                while (ss >> move && moves_no < MAX_DEPTH)
                    if (islower(move[0])) {
                        moves.push_back(string_to_move(move));
                        ++moves_no;
                    }
                tree.add(moves, 0);
            } else
                ignore_next = false;
        }
    }
    tree.sort(0, true, true);
    tree.print();
    return 0;
}
