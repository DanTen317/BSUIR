#include "Human.h"

Human::Human(std::string name, int age) : name(name), age(age) {}

void Human::print() const
{
	std::cout << name << std::endl;
}
