#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <stdexcept>

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

void TestAll();

int main() {

  TestAll();

  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } else if (command == "Del") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      auto count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };

      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}


void TestParseEvent() {
  {
    istringstream is("event");
    AssertEqual(ParseEvent(is), "event", "Parse event1 without leading spaces");
  }
  {
    istringstream is("   sport event ");
    AssertEqual(ParseEvent(is), "sport event ", "Parse event2 with leading spaces");
  }
  {
    istringstream is("  first event  \n  second event");
    vector<string> events;
    events.push_back(ParseEvent(is));
    events.push_back(ParseEvent(is));
    AssertEqual(events, vector<string>{"first event ", "second event"}, "Parse multiple events");
  }
}

void TestParseDate() {
	{
		istringstream is("2017-01-01");
		AssertEqual(ParseDate(is), Date{ 2017, 01, 01 }, "Parse date without leading spaces");
	}
	{
		istringstream is("   2017-02-02  ");
		AssertEqual(ParseDate(is), Date{ 2017, 02, 02 }, "Parse date with leading spaces");
	}
	{
		istringstream is("  2017-03-03  \n  2017-04-04  ");
		vector<Date> events;
		events.push_back(ParseDate(is));
		events.push_back(ParseDate(is));
		AssertEqual(events, vector<Date>{Date{ 2017, 03, 03 }, Date{ 2017, 04, 04 }}, "Parse multiple dates");
	}

	{
		istringstream is("  18-1-1  \n  12-2-2  ");
		vector<Date> events;
		events.push_back(ParseDate(is));
		events.push_back(ParseDate(is));
		AssertEqual(events, vector<Date>{Date{ 18, 01, 01 }, Date{ 12, 02, 02 }}, "Parse multiple dates with zeros");
	}

	{
		istringstream is("  00018-0001-0001  \n  00012-0002-0002  ");
		vector<Date> events;
		events.push_back(ParseDate(is));
		events.push_back(ParseDate(is));
		AssertEqual(events, vector<Date>{Date{ 18, 1, 1 }, Date{ 12, 2, 2 }}, "Parse multiple dates with zeros");
	}
}

void TestAll() {
  TestRunner tr;
  tr.RunTest(TestParseDate, "TestParseDate");
  tr.RunTest(TestParseEvent, "TestParseEvent");
  tr.RunTest(TestParseCondition, "TestParseCondition");
  system("pause");
}
