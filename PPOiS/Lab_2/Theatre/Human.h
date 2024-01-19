#pragma once
#include <string>
#include <iostream>

class Human
{
protected:
	std::string name;
	int age;

	Human(std::string, int);
	virtual void print() const;
};

