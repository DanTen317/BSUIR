#pragma once


class Place
{
private:
	int row;
	int place;
	bool taken;
public:
	Place(int row, int place) :row(row), place(place), taken(false) {}
	void take_place();
	bool is_taken() const;
	int row_() const;
	int place_() const;
};

