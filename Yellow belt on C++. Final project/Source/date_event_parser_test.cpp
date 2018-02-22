#include "lib.h"
#include "test_runner.h"
#include "date.h"
#include "date_event_parser.h"

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
