#include "database.h"

void Database::Add(const Date& date, const string& my_event)
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

pair<Date, string> Database::Last(const Date& date)
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

void Database::Print(ostream& stream) const
{
	stream << setfill('0');
	for (const auto& item : db_pr_last)
		for (const string& str : item.second)
			stream << setw(4) << item.first.GetYear() << "-"
			<< setw(2) << item.first.GetMonth() << "-"
			<< setw(2) << item.first.GetDay() << " " << str << endl;
}


bool is_a_letter(int val)
{
	if ((char(val) >= 'A' && char(val) <= 'Z') || (char(val) >= 'a' && char(val) <= 'z')) return true;
	return false;
}

int full_size(const map<Date, set<string>>& mp)
{
	int size = 0;
	for (const auto & item : mp)
		for (const auto & elem : item.second)
			size++;
	return size;
}
