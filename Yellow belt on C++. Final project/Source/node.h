#pragma once

#include "lib.h"

using namespace std;

#include "date.h"
#include "token.h"


bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);

ostream& operator<<(ostream& os, const Date& date);
ostream& operator<<(ostream& os, const pair<Date, string>& p);
ostream& operator<<(ostream& os, const pair<Date, set<string>>& p);

class Node
{
public:
	virtual bool Evaluate(const Date& date, const string& my_event) = 0;
private:
};

class DateComparisonNode : public Node
{
public:
	DateComparisonNode(Comparison op, Date date) : _op(op), _date(date) {}
	bool Evaluate(const Date& date, const string& my_event);

private:
	const Date _date;
	Comparison _op;
};

class EventComparisonNode : public Node
{
public:
	EventComparisonNode(Comparison op, string my_event) : _op(op), _event(my_event) {}
	bool Evaluate(const Date& date, const string& my_event);
private:
	const string _event;
	Comparison _op;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(LogicalOperation operation, shared_ptr<Node> left, shared_ptr<Node> right) :
		_lop(operation), _left(left), _right(right) {}
	bool Evaluate(const Date& date, const string& my_event);
private:
	LogicalOperation _lop;
	shared_ptr<Node> _left;
	shared_ptr<Node> _right;
};

class EmptyNode : public Node
{
public:
	bool Evaluate(const Date& date, const string& my_event);
};