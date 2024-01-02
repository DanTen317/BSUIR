#include "Tape.h"

Tape::Tape() : head_position(0) {

}
int Tape::get_head_position() { return head_position; }

void Tape::write(Alphabet symbol) {
    tape.push_back(symbol);
}

void Tape::rewrite(Alphabet symbol) {
    tape[head_position] = symbol;
}

std::vector<char> Tape::get_tape() {
    std::vector<char> vec_tape;
    for (int symbol : tape) {
        switch (symbol) {       // преобразуем символ из Alphabet в char
        case ZERO:
            vec_tape.push_back('0');
            break;
        case ONE:
            vec_tape.push_back('1');
            break;
        default:
            vec_tape.push_back('E');
            break;
        }
    }
    return vec_tape;
}

void Tape::head_move(Direction direction) {
    switch (direction) {
    case LEFT:
        head_position--;
        if (head_position <= 0) {
            tape.insert(tape.begin(), BLANK);
            head_position = 0;
        }
        break;
    case RIGHT:
        head_position++;
        if (head_position >= tape.size())
            tape.push_back(BLANK);
        break;
    default:
        break;
    }
}

Alphabet char_to_Alphabet(char& symbol) {
    switch (symbol) {       // преобразуем символ из файла в тип Alphabet
    case '0':
        return ZERO;
        break;
    case '1':
        return ONE;
        break;
    default:
        return BLANK;
        break;
    }
}

Direction char_to_Direction(char& symbol) {
    switch (symbol)
    {
    case '>':
        return RIGHT;
        break;
    case '<':
        return LEFT;
        break;
    default:
        return WAIT;
        break;
    }
}