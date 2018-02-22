#pragma once
#include "lib.h"

using namespace std;

#include "date.h"

bool is_a_letter(int val);
int full_size(const map<Date, set<string>>& mp);

class Database {
public:
	void Add(const Date& date, const string& my_event);

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

	pair<Date, string> Last(const Date& date);
	void Print(ostream& stream) const;

private:
	map<Date, set<string>> db;
	map<Date, deque<string>> db_pr_last;
};
