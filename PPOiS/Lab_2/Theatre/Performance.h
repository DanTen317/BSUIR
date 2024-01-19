#pragma once

#include "Place.h"
#include "Theatre.h"
#include "Date.h"
#include "Role.h"

class Performance
{
private:
	std::vector<Role> roles;
	std::vector<Place> places;		//все места на представлении
	friend class Ticket;
	std::string name;
	Date date;
	double price;
	Theatre theatre;
	void create_places(int& rows, int& places_in_row);
public:
	Performance() {};
	Performance(std::string name, std::string date, double price, Theatre theatre);
	bool place_is_taken(std::vector<int> place);
	void new_role(std::string name,Actor actor);
	std::string info();
	Role get_role(int number);
	void take_place(int place[2]);
};

