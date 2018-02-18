#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <exception>
#include <vector>
#include <iomanip>
#include <sstream>
#include <tuple>

using namespace std;

#include "date.h"


int Date::GetYear() const
{
	return year.value;
}
int Date::GetMonth() const
{
	return month.value;
}
int Date::GetDay() const
{
	return day.value;
}

bool operator<(const Date& lhs, const Date& rhs)
{
	int ly = lhs.GetYear(), lm = lhs.GetMonth(), ld = lhs.GetDay();
	int ry = rhs.GetYear(), rm = rhs.GetMonth(), rd = rhs.GetDay();
	return tie(ly, lm, ld) < tie(ry, rm, rd);
}

bool operator<=(const Date& lhs, const Date& rhs)
{
	int ly = lhs.GetYear(), lm = lhs.GetMonth(), ld = lhs.GetDay();
	int ry = rhs.GetYear(), rm = rhs.GetMonth(), rd = rhs.GetDay();
	return tie(ly, lm, ld) <= tie(ry, rm, rd);
}


bool operator>(const Date& lhs, const Date& rhs)
{
	return !(lhs <= rhs);
}

bool operator>=(const Date& lhs, const Date& rhs)
{
	return !(lhs < rhs);
}

bool operator==(const Date& lhs, const Date& rhs)
{
	int ly = lhs.GetYear(), lm = lhs.GetMonth(), ld = lhs.GetDay();
	int ry = rhs.GetYear(), rm = rhs.GetMonth(), rd = rhs.GetDay();
	return (tie(ly, lm, ld) == tie(ry, rm, rd));
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs == rhs);
}

ostream& operator<<(ostream& os, const Date& date)
{
	os << setfill('0');
	os << setw(4) << date.GetYear() << "-"
		<< setw(2) << date.GetMonth() << "-"
		<< setw(2) << date.GetDay();
	return os;
}

ostream& operator<<(ostream& os, const pair<Date, string>& p)
{
	os << setfill('0');
	os << p.first << " " << p.second;

	return os;

}

ostream& operator<<(ostream& os, const pair<Date, set<string>>& p)
{
	os << setfill('0');
	size_t i = 0;
	size_t n = p.second.size();
	for (const string& str : p.second)
	{
		os << p.first << " " << str;
		if (i < n - 1) cout << endl;
		i++;
	}
	return os;
}

bool there_is_letter(string ch_date)
{
	for (int i = 0; i < ch_date.size(); i++)
		if ((ch_date[i] >= 'A' && ch_date[i] <= 'Z') || (ch_date[i] >= 'a' && ch_date[i] <= 'z')) return true;
	return false;
}

Date ParseDate(istream& is)
{
	int d, m, y;

	// Date
	char sep1 = ' ';
	char sep2 = ' ';
	is >> y;
	is >> sep1;
	is >> m;
	is >> sep2;
	is >> d;

	
	Date date(Year{ y }, Month{ m }, Day{ d });

	return date;
}