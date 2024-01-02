#pragma once

#include <string>
#include <Windows.h>
#include "Machine.h"

void ask_file() {
	std::string file_name;
	std::cout << "Enter file name(path): ";
	std::getline(std::cin, file_name);
}

void add_tape_symbol(Machine& machine) {
	std::string tape_str;
	std::cout << "Enter Tape (ex.:100101): ";
	std::cin >> tape_str;
	for (char symbol : tape_str)
		machine.write(symbol);
}

void print_machine(Machine& machine) {
	std::vector<char> tape_vec = machine.get_tape();
	std::cout << std::string((tape_vec.size() * 2 - 1), '-') << std::endl;
	machine_color();
	for (int i = 0; i < tape_vec.size(); i++) {
		if (i == machine.get_head_position())
			active_head_color();
		std::cout << machine.get_tape()[i] << " ";
		machine_color();
	}
	default_color();
	std::cout <<std::endl<< std::string((tape_vec.size() * 2 - 1), '-') << std::endl;
}

void add_rule(Machine& machine) {
	std::cout << "Enter rule \n[current_rule] [current_state]\n[new_rule] [new_state] [direction]\n";
	char input[3];
	std::string new_rule[2];
	std::cin >> new_rule[0] >> input[0];
	std::cin >> new_rule[1] >> input[1] >> input[2];
	machine.new_rule(new_rule[0], input[0], new_rule[1], input[1], input[2]);
}

void print_rules(Machine& machine) {
	std::vector<std::vector<char>> to_print = machine.get_rules();
	/*std::cout << std::endl;
	for (int i = 0; i < to_print.size(); i++) {
		std::cout << to_print[i][0] << " " << to_print[i][1]<<std::endl;
		for (int j = 2; j < 5; j++) {
			std::cout << to_print[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	for (int i = 0; i < to_print.size(); i++) {
		for (int j = 0; j < 5; j++) {
			std::cout << to_print[i][j] << " ";
		}
	}
	//std::cout << std::endl;
}

void active_head_color() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
void machine_color() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}
void default_color() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_BLUE |
		FOREGROUND_INTENSITY);
}