#include "Performance.h"


Performance::Performance(std::string name, std::string date, double price, Theatre theatre)
	: name(name), date(date), price(price), theatre(theatre)
{
	create_places(theatre.get_theatre_hall_size()[0], theatre.get_theatre_hall_size()[1]);
}

void Performance::create_places(int& rows, int& places_in_row)
{
	for (size_t i = 1; i <= rows; i++)
	{
		for (size_t j = 1; j <= places_in_row; j++)
		{
			Place place(i, j);
			places.push_back(place);
		}
	}
}

bool Performance::place_is_taken(std::vector<int> place)
{
	for (Place curret_place : places)
	{
		if (curret_place.row_() == place[0] && curret_place.place_() == place[1])
			return curret_place.is_taken();
	}
	return true;
}

void Performance::new_role(std::string name, Actor actor)
{
	Role new_role(name, actor);
	roles.push_back(new_role);
}

std::string Performance::info()
{
	return theatre.get_name() + "\n" + name + "\n" +
		std::to_string(date.get_time().get_hours()) + ":" +
		std::to_string(date.get_time().get_minutes()) + " " +
		std::to_string(date.get_day()) + "." +
		std::to_string(date.get_month()) + "." +
		std::to_string(date.get_year()) + "\n" +
		std::to_string(price);
}

Role Performance::get_role(int number)
{
	return roles[number - 1];
}

void Performance::take_place(int place[2])
{
	for (Place curret_place : places)
	{
		if (curret_place.row_() == place[0] && curret_place.place_() == place[1]);
			
	}
	for (size_t i = 0; i < places.size(); i++)
	{
		if (places[i].row_() == place[0] && places[i].place_() == place[1])
			places[i].take_place();
	}
}
