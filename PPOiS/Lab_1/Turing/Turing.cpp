#include <iostream>
#include "console.h"

int main()
{
	default_color();
	std::string log;
	Machine turing_machine;
	std::cout << "If you need logs print \"-log\"\n";
	std::getline(std::cin, log);
	if (log == "-log") {
		turing_machine.enable_logs();
		std::cout << "Logs enabled.\n";
	}
	char symbol[3] = { '1','1','0' };
	for (char one_symbol : symbol) {
		turing_machine.write(one_symbol);
	}
	turing_machine.new_rule("0", '1', "1", '0', '>');
	turing_machine.new_rule("1", '1', "-1", '1', '_');
	turing_machine.do_step(turing_machine);
	
	system("pause");
}
