#pragma once
#include "Human.h"

class Actor : virtual private Human
{
private:
	std::string rank;
public:
	Actor(std::string, int, std::string);
	void print() const;
	bool operator ==(const Actor&)const;
};

