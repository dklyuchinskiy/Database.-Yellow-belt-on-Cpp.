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
#include <deque>

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
		if (db.count(date) == 0)
		{
			db_pr_last[date].push_back(my_event);
		}
		else
		{
			if (db[date].count(my_event) == 0) db_pr_last[date].push_back(my_event);
		}
		db[date].insert(my_event);
	}
	
	template <typename F>
	int RemoveIf(const F& func)
	{
		int size1 = 0;
		int size2 = 0;

		size1 = full_size(db);

		map<Date, deque<string>> for_delete;

		for (const auto& date : db_pr_last)
			for (const string& my_event : date.second)
			{
				if (func(date.first, my_event))
				{
					for_delete[date.first].push_back(my_event);
				}
			}

		for (const auto& date : for_delete)
		{
			for (const string& my_event : date.second)
			{
				db[date.first].erase(my_event);
				db_pr_last[date.first].pop_front();
			}
			if (db[date.first].size() == 0)
			{
				db.erase(date.first);
				db_pr_last.erase(date.first);
			}
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
			deque<string> &work = db_pr_last[it->first];
			return pair<Date, string>(it->first, work[work.size() - 1]);
		}

	}

	void Print(ostream& stream) const
	{
		stream << setfill('0');
		for (const auto& item : db_pr_last)
			for (const string& str : item.second)
				stream << setw(4) << item.first.GetYear() << "-"
				<< setw(2) << item.first.GetMonth() << "-"
				<< setw(2) << item.first.GetDay() << " " << str << endl;
	}
private:
	map<Date, set<string>> db;
	map<Date, deque<string>> db_pr_last;
};


bool is_a_letter(int val)
{
	if ((char(val) >= 'A' && char(val) <= 'Z') || (char(val) >= 'a' && char(val) <= 'z')) return true;
	return false;
}
