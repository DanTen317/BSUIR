#include "Theatre.h"


Theatre::Theatre()
{
}

Theatre::Theatre(std::string name, std::string address, std::vector <int> size)
	:name(name), address(address), theatre_hall(size)
{}

std::vector<int> Theatre::get_theatre_hall_size()
{
	return theatre_hall;
}

std::string Theatre::get_name()
{
	return name;
}

std::string Theatre::info()
{
	return name + "\n" + address + "\n";
}
