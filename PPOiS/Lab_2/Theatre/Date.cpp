#include "Date.h"


Time::Time(std::string time)
{
	std::string number;
	for (char symbol : time) {
		if (symbol == ':') {
			hours = stoi(number);
			number = "";
		}
		else
			number += symbol;
	}
	minutes = stoi(number);

	if (!is_correct_time()) {
		hours = DEFAULT_DATE_HOURS;
		minutes = DEFAULT_DATE_MINUTES;
		std::cerr << "Uncorrect time. Default time applied.\n";
	}
}

int Time::get_hours() const {
	return hours;
}

int Time::get_minutes() const {
	return minutes;
}

bool Time::is_correct_time() const {
	return get_hours() <= 23 && get_hours() >= 0 && get_minutes() <= 59 && get_minutes() >= 0;
}

int Date::get_days_in_feb(int year) {			//проверка "високосности" года
	if ((!(year % 4) && (year % 100)) || !(year % 400)) {
		return 29;
	}
	return 28;
}

int Date::get_days_in_month(int month, int year) {
	switch (month)
	{
	case 2:
		return get_days_in_feb(year);
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	default:
		return 30;
	}
}

bool Date::is_correct_date() {
	if (get_month() <= 12 && get_month() >= 1)
		if (get_day() <= get_days_in_month(get_month(), get_year()) && get_day() >= 1)
			return true;
		else return false;
	else return false;
}


int Date::get_day() const {
	return day;
}
int Date::get_month() const {
	return month;
}
int Date::get_year() const {
	return year;
}
Time Date::get_time() const {
	return time;
}
Date::Date(std::string date) //12:00 1.1.1970
	:time(string_rebuider(date))
{
	std::string number;
	int category = 0;
	for (char symbol : date) {
		if (symbol == '.') {
			switch (category)
			{
			case 0:
				day = stoi(number);
				number = ""; break;
			case 1:
				month = stoi(number);
				number = ""; break;
			default: break;
			}
			category = (category == 0) ? 1 : 2;
		}
		else number += symbol;

	}
	year = stoi(number);

	if (!is_correct_date()) {
		day = DEFAULT_DATE_DAY;
		month = DEFAULT_DATE_MONTH;
		year = DEFAULT_DATE_YEAR;
		std::cerr << "Uncorrect date. Default date applied.\n";
	}
}

std::string Date::string_rebuider(std::string& str)
{
	int count_time_symbols = 0;
	std::string new_str;
	for (char symbol : str) {
		if (symbol != ' ') {
			new_str += symbol;
			count_time_symbols++;
		}
		else break;
	}
	str.erase(0, count_time_symbols + 1);
	
	return new_str;
}
