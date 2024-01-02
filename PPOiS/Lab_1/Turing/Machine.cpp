#include "Machine.h"

Machine::Machine() {
	tape;
	rules;
	log = false;
	int rule_id = 0;
}

void Machine::enable_logs() {
	log = true;
}

void print_machine(Machine& machine);

void Machine::head_move(Direction direction) {
	tape.head_move(direction);
}

std::vector<char> Machine::get_tape() {
	return tape.get_tape();
}

int Machine::get_head_position() { return tape.get_head_position(); }

void Machine::write(char& symbol) {
	tape.write(char_to_Alphabet(symbol));
}

void Machine::rewrite(Alphabet symbol) {
	tape.rewrite(symbol);
}

void Machine::new_rule(std::string current_state, char current_symbol, std::string new_state, char new_symbol, char direction) {
	for (auto rule : rules) {
		if (rule.current_state_() == stoi(current_state)) {
			std::cout << "Rule with this id already exist. \n";
			return;
		}
	}
	Rule new_r(current_state, current_symbol, new_state, new_symbol, direction);
	rules.push_back(new_r);
}

void Machine::delete_rule(int id) {
	int counter=0;
	for (auto rule : rules) {
		if (id == rule.get_state()[0]-'0') {
			id = counter;
		}else counter++;
	}
	rules.erase(rules.begin() + counter);
}

std::vector<std::vector<char>> Machine::get_rules() {
	std::vector<std::vector<char>> rules_;
	for (int i = 0; i < rules.size(); i++) {
		rules_.push_back(rules[i].get_state());
	}
	return rules_;
}

void Machine::do_step(Machine& machine) {
	if (rules[rule_id].current_symbol_() == char_to_Alphabet(tape.get_tape()[tape.get_head_position()])) {
		rewrite(rules[rule_id].new_symbol_());
	}
	tape.head_move(rules[rule_id].direction_());
	if (log) {
		std::cout << "rule " << rule_id << " ->\n";
		print_machine(machine);
	}
}

void Machine::run_machine(Machine& machine) {
	while (rule_id != -1) {
		do_step(machine);
		rule_id = rules[rule_id].new_state_();
	}
	//std::cout << "Work finished.\n";
}