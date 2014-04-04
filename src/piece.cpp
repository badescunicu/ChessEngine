#include <piece.hpp>

Piece::Piece() {}

Piece::~Piece() {}

PieceType Piece::char_to_piece(char c, const Color& color) {
    int piece_code;
    switch (c) {
        case 'P': case 'p': piece_code = 1; break;
        case 'N': case 'n': piece_code = 2; break;
        case 'B': case 'b': piece_code = 3; break;
        case 'R': case 'r': piece_code = 4; break;
        case 'Q': case 'q': piece_code = 5; break;
        case 'K': case 'k': piece_code = 6;
    }
    if (color == BLACK)
        piece_code |= 8;
    return static_cast<PieceType>(piece_code);
}

std::string Piece::move_to_string(unsigned short move) {
    std::string ret(4, 0);
    ret[1] = (move & 7) + '0' + 1;
    ret[0] = ((move & (7 << 3)) >> 3) + 'a';
    ret[3] = ((move & (7 << 6)) >> 6) + '0' + 1; 
    ret[2] = ((move & (7 << 9)) >> 9) + 'a';
    if (move & 0xF000)
        switch ((move & 0x7000) >> 12) {
            case 2: ret += 'n'; break;
            case 3: ret += 'b'; break;
            case 4: ret += 'r'; break;
            case 5: ret += 'q';
        }
    return ret;
}

unsigned short Piece::string_to_move(const std::string& move_str,
                                     const Color& piece_color) {
    if (move_str.length() == 5)
        return build_move(move_str[1] - 1 - '0',
                          move_str[0] - 'a',
                          move_str[3] - 1 - '0',
                          move_str[2] - 'a',
                          char_to_piece(move_str[4], piece_color));
    return build_move(move_str[1] - 1 - '0',
                      move_str[0] - 'a',
                      move_str[3] - 1 - '0',
                      move_str[2] - 'a');
}

unsigned short Piece::build_move(const int initial_row,
                                 const int initial_column,
                                 const int destination_row,
                                 const int destination_column) {
    unsigned short result = 0;
    result |= initial_row;
    result |= (initial_column << 3);
    result |= (destination_row << 6);
    result |= (destination_column << 9);
    return result;
}

unsigned short Piece::build_move(const int initial_row,
                                 const int initial_column,
                                 const int destination_row,
                                 const int destination_column,
                                 const PieceType promoted) {
    unsigned short result = 0;
    result |= initial_row;
    result |= (initial_column << 3);
    result |= (destination_row << 6);
    result |= (destination_column << 9);
    result |= (promoted << 12);
    return result;
}
