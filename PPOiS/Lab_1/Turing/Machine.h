#pragma once
#include "Tape.h"
#include "Rule.h"

void active_head_color();
void machine_color();
void default_color();

class Machine
{
private:
	Tape tape;
	std::vector<Rule> rules;
	bool log;
	int rule_id;
public:
	Machine();
	//~Machine();
	void enable_logs();
	std::vector<char> get_tape();
	int get_head_position();
	void write(char& symbol);
	void rewrite(Alphabet symbol);
	void new_rule(std::string, char, std::string, char, char);
	void delete_rule(int id);
	std::vector<std::vector<char>> get_rules();
	void do_step(Machine& machine);
	void run_machine(Machine&);
	void head_move(Direction direction);
};

