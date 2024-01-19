#pragma once
#include "Human.h"
#include "Ticket.h"
#include "Performance.h"

class Customer : private Human
{
private:
	bool is_student;
public:
	Customer(std::string, int, bool);
	int get_discount();
	void print()const;
	Ticket buy_ticket(Performance&, int place[2]);
};

