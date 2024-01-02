#pragma once
#include <vector>
#include <string>
#include <iostream>
enum Alphabet : int
{
	ONE = 1, ZERO = 0, BLANK = -1
};
enum Direction : char {
	LEFT = '<', RIGHT = '>', WAIT = '_'
};

class Tape
{
private:
	int head_position;
	std::vector<Alphabet> tape;
public:
	Tape();
	void write(Alphabet);
	void rewrite(Alphabet);
	void head_move(Direction);
	std::vector<char> get_tape();
	int get_head_position();

};

Alphabet char_to_Alphabet(char&);
Direction char_to_Direction(char&);