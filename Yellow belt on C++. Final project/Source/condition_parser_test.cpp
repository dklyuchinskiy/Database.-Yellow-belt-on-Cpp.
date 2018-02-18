#include "condition_parser.h"
#include "test_runner.h"
#include "node.h"

#include <sstream>
using namespace std;

void TestParseCondition() {
  {
	cout << "Tests 1 - 2" << endl;
    istringstream is("date != 2017-11-18");
    shared_ptr<Node> root = ParseCondition(is);
	Assert(root->Evaluate({ Year(2017), Month(1), Day{1} }, ""), "Parse condition 1");
	Assert(!root->Evaluate({ Year{2017}, Month{11}, Day{18} }, ""), "Parse condition 2");
  }
  {
	cout << "\nTests 3 - 4" << endl;
    istringstream is(R"(event == "sport event")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 3");
    Assert(!root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 4");
  }
  {
	cout << "\nTests 5 - 9" << endl;
    istringstream is("date >= 2017-01-01 AND date < 2017-07-01");
    shared_ptr<Node> root = ParseCondition(is);
	Assert(root->Evaluate({ Year{2017}, Month{1}, Day{1} }, ""), "Parse condition 5");
    Assert(root->Evaluate({2017, 3, 1}, ""), "Parse condition 6");
    Assert(root->Evaluate({2017, 6, 30}, ""), "Parse condition 7");
    Assert(!root->Evaluate({2017, 7, 1}, ""), "Parse condition 8");
    Assert(!root->Evaluate({2016, 12, 31}, ""), "Parse condition 9");
  }
  {
	cout << "\nTests 10 - 12" << endl;
    istringstream is(R"(event != "sport event" AND event != "Wednesday")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({2017, 1, 1}, "holiday"), "Parse condition 10");
    Assert(!root->Evaluate({2017, 1, 1}, "sport event"), "Parse condition 11");
    Assert(!root->Evaluate({2017, 1, 1}, "Wednesday"), "Parse condition 12");
  }
  {
	cout << "\nTests 13 - 15" << endl;
    istringstream is(R"(event == "holiday AND date == 2017-11-18")");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(!root->Evaluate({2017, 11, 18}, "holiday"), "Parse condition 13");
    Assert(!root->Evaluate({2017, 11, 18}, "work day"), "Parse condition 14");
    Assert(root->Evaluate({1, 1, 1}, "holiday AND date == 2017-11-18"), "Parse condition 15");
  }
  {
	cout << "\nTests 16 - 17" << endl;
	istringstream is(R"(((event == "holiday" AND date == 2017-01-01)))");
	shared_ptr<Node> root = ParseCondition(is);
	Assert(root->Evaluate({ 2017, 1, 1 }, "holiday"), "Parse condition 16");
	Assert(!root->Evaluate({ 2017, 1, 2 }, "holiday"), "Parse condition 17");
  }
  {
	cout << "\nTests 18 - 21" << endl;
    istringstream is(R"(date > 2017-01-01 AND (event == "holiday" OR date < 2017-07-01))");
    shared_ptr<Node> root = ParseCondition(is);
	Assert(!root->Evaluate({ 2016, 1, 1 }, "holiday"), "Parse condition 18");
	Assert(root->Evaluate({ 2017, 1, 2 }, "holiday"), "Parse condition 19");
	Assert(root->Evaluate({ 2017, 1, 2 }, "workday"), "Parse condition 20");
	Assert(!root->Evaluate({ 2018, 1, 2 }, "workday"), "Parse condition 21");
  }
  {
	cout << "\nTests 22 - 25" << endl;
    istringstream is(R"(date > 2017-01-01 AND event == "holiday" OR date < 2017-07-01)");
    shared_ptr<Node> root = ParseCondition(is);
	Assert(root->Evaluate({ 2016, 1, 1 }, "event"), "Parse condition 22");
	Assert(root->Evaluate({ 2017, 1, 2 }, "holiday"), "Parse condition 23");
	Assert(root->Evaluate({ 2017, 1, 2 }, "workday"), "Parse condition 24");
	Assert(!root->Evaluate({ 2018, 1, 2 }, "workday"), "Parse condition 25");
  }
  {
	cout << "\nTests 26 - 27" << endl;
    istringstream is(R"(((date == 2017-01-01 AND event == "holiday")))");
    shared_ptr<Node> root = ParseCondition(is);
	Assert(root->Evaluate({ 2017, 1, 1 }, "holiday"), "Parse condition 26");
	Assert(!root->Evaluate({ 2017, 1, 2 }, "holiday"), "Parse condition 27");
  }
  {
	cout << "\nTests 28 - 30" << endl;
    istringstream is(R"(((event == "2017-01-01" OR date > 2016-01-01)))");
    shared_ptr<Node> root = ParseCondition(is);
    Assert(root->Evaluate({1, 1, 1}, "2017-01-01"), "Parse condition 28");
    Assert(!root->Evaluate({2016, 1, 1}, "event"), "Parse condition 29");
    Assert(root->Evaluate({2016, 1, 2}, "event"), "Parse condition 30");
  }
}
