#pragma once
#include "Performance.h"

class Ticket 
{
private:
	std::string id;
	std::vector<int> place;
	Performance performance;
	double price;

	void create_id();
public:
	Ticket(Performance& performance, int place[2]);
	void print_ticket();
	void make_discount(int discount);
};