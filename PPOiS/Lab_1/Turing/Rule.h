#pragma once
#include "Tape.h"

class Rule
{
private:
	int current_state;
	Alphabet current_symbol;
	int new_state;
	Alphabet new_symbol;
	Direction direction;
public:
	Rule(std::string, char, std::string, char, char);
	std::vector<char> get_state();
	int current_state_();
	Alphabet current_symbol_();
	Alphabet new_symbol_();
	Direction direction_();
	int new_state_();

};

