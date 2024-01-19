#include "Place.h"

void Place::take_place()
{
	taken = true;
}

bool Place::is_taken() const
{
	return taken;
}

int Place::row_() const
{
	return row;
}

int Place::place_() const
{
	return place;
}
