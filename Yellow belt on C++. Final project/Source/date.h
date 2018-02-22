#pragma once
#include "lib.h"

struct Day {
	Day(int d) : value(d) { }
	Day & operator=(const Day& right)
	{
		value = right.value;
		return *this;
	}
	int value;
};

struct Month {
	Month(int m) : value(m) { }
	Month & operator=(const Month& right)
	{
		value = right.value;
		return *this;
	}
	int value;
};

struct Year {
	Year(int y) : value(y) { }
	Year & operator=(const Year& right)
	{
		value = right.value;
		return *this;
	}
	int value;
};

class Date {
public:
	Date() : year(0), month(0), day(0) {}
	Date(Year y, Month m, Day d) : year(y), month(m), day(d) { }

	Date & operator=(const Date& right);
	
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

private:
	Year year;
	Month month;
	Day day;
};

Date ParseDate(istream& is);


bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);


ostream& operator<<(ostream& os, const Date& date);
ostream& operator<<(ostream& os, const pair<Date, string>& p);
ostream& operator<<(ostream& os, const pair<Date, set<string>>& p);