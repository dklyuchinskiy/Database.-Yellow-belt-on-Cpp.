#include "lib.h"
#include "date_event_parser.h"

using namespace std;

string ParseEvent(istream& is)
{
	string my_event;
	getline(is, my_event);

	string::iterator new_it = unique(begin(my_event), end(my_event), [](const char& c, const char& l)
	{ return (isspace(c) && isspace(l) && c == l); });

	my_event.erase(new_it, end(my_event));

	if (my_event[0] == ' ') my_event.erase(my_event.begin());
	return my_event;
}
