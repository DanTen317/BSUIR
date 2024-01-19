#pragma once

#include <vector>
#include <string>

class Theatre
{
private:
	std::string name;
	std::string address;
	std::vector<int> theatre_hall;	//<rows, places in row>
public:
	Theatre();
	Theatre(std::string, std::string, std::vector<int>);
	std::vector<int> get_theatre_hall_size();
	std::string get_name();
	std::string info();
};

