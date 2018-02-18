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


int full_size(const map<Date, set<string>>& mp)
{
	int size = 0;
	for (const auto & item : mp)
		for (const auto & elem : item.second)
			size++;
	return size;
}

class Database {
public:
	void Add(const Date& date, const string& my_event)
	{
		db[date].insert(my_event);
		last_add_event_for_date[date] = my_event;
	}
	
	template <typename F>
	int RemoveIf(const F& func)
	{
		int size1 = 0;
		int size2 = 0;

		size1 = full_size(db);

		map<Date, set<string>> for_delete;

		for (const auto& date : db)
			for (const string& my_event : date.second)
			{
				if (func(date.first, my_event))
				{
					for_delete[date.first].insert(my_event);
				}
			}

		for (const auto& date : for_delete)
			for (const string& my_event : date.second)
			{
					db[date.first].erase(my_event);
			}

		size2 = full_size(db);

		return size1 - size2;
	}

	template <typename F>
	set<pair<Date, string>> FindIf(const F& func)
	{
		set<pair<Date, string>> found_db;
		for (const auto& date : db)
			for (const string& my_event : date.second)
			{
				if (func(date.first, my_event))
				{
					found_db.insert(make_pair(date.first, my_event));
				}
			}
		return found_db;
	}

	pair<Date, string> Last(const Date& date)
	{
		map<Date, set<string>>::iterator it;
		it = db.upper_bound(date);
		if (it == db.begin()) throw invalid_argument("");
		else
		{
			it = prev(it);
			return pair<Date, string>(it->first, last_add_event_for_date[it->first]);
		}

	}

	void Print(ostream& stream) const
	{
		stream << setfill('0');
		for (const auto& item : db)
			for (const string& str : item.second)
				stream << setw(4) << item.first.GetYear() << "-"
				<< setw(2) << item.first.GetMonth() << "-"
				<< setw(2) << item.first.GetDay() << " " << str << endl;
	}
private:
	map<Date,set<string>> db;
	map<Date, string> last_add_event_for_date;
};


bool is_a_letter(int val)
{
	if ((char(val) >= 'A' && char(val) <= 'Z') || (char(val) >= 'a' && char(val) <= 'z')) return true;
	return false;
}
