#ifndef H_DATE
#define H_DATE

#include <iostream>
#include <string>




const int DEFAULT_DATE_DAY = 1;
const int DEFAULT_DATE_MONTH = 1;
const int DEFAULT_DATE_YEAR = 1970;
const int DEFAULT_DATE_HOURS = 12;
const int DEFAULT_DATE_MINUTES = 0;

class Time
{
private:
	int hours;
	int minutes;

	bool is_correct_time() const;

public:
	Time() {};
	Time(std::string);

	int get_hours() const;
	int get_minutes() const;
	friend class Date;
};

class Date
{
private:
	Time time;
	int day, month, year;

	int get_days_in_feb(int);
	int get_days_in_month(int, int);

	bool is_correct_date();
	std::string string_rebuider(std::string& str);

public:
	Date() {};
	Date(std::string);

	int get_day() const;
	int get_month() const;
	int get_year() const;
	Time get_time() const;
	
};

#endif //H_DATE