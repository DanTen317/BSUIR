#include "Rule.h"
#include <iostream>

Rule::Rule(std::string current_state_, char current_symbol_, std::string new_state_, char new_symbol_, char direction_) {
	current_state = std::stoi(current_state_);
	current_symbol = char_to_Alphabet(current_symbol_);
	new_state = std::stoi(new_state_) ;
	new_symbol = char_to_Alphabet(new_symbol_);
	direction = char_to_Direction(direction_);
}
std::vector<char> Rule::get_state() {
	std::vector<char> rule_to_return;
	rule_to_return.push_back(current_state + '0');
	rule_to_return.push_back(current_symbol + '0');
	rule_to_return.push_back(new_state + '0');
	rule_to_return.push_back(new_symbol + '0');
	rule_to_return.push_back(direction);
	return rule_to_return;
}
int Rule::current_state_() {
	return current_state;
}

Alphabet Rule::current_symbol_() {
	return current_symbol;
}

Alphabet Rule::new_symbol_() {
	return new_symbol;
}

Direction Rule::direction_() {
	return direction;
}
int Rule::new_state_() {
	return new_state;
}