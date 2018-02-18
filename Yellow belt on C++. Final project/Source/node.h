#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <exception>
#include <vector>
#include <iomanip>
#include <sstream>
#include <memory>
#include <tuple>

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
	bool Evaluate(const Date& date, const string& my_event)
	{
		//cout << "DateComparisonNode" << endl;
		//cout << "In constructor: " << _date << endl;
		//cout << "To evaluate input: " << date << endl;
		if (_op == Comparison::Less)
		{
			return (date < _date);
		}
		else if (_op == Comparison::LessOrEqual)
		{
			return (date <= _date);
		}
		else if (_op == Comparison::Greater)
		{
			return (date > _date);
		}
		else if (_op == Comparison::GreaterOrEqual)
		{
			return (date >= _date);
		}
		else if (_op == Comparison::Equal)
		{
			return (date == _date);
		}
		else if (_op == Comparison::NotEqual)
		{
			return (date != _date);
		}
	}

private:
	const Date _date;
	Comparison _op;
};

class EventComparisonNode : public Node
{
public:
	EventComparisonNode(Comparison op, string my_event) : _op(op), _event(my_event) {}
	bool Evaluate(const Date& date, const string& my_event)
	{
		//cout << "EventComparisonNode" << endl;
		//cout << "In constructor: " << _event << endl;
		//cout << "To evaluate input: " << my_event << endl;
		if (_op == Comparison::Equal)
		{
			return (_event == my_event);
		}
		else if (_op == Comparison::NotEqual)
		{
			return (_event != my_event);
		}
	}
private:
	const string _event;
	Comparison _op;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(LogicalOperation operation, shared_ptr<Node> left, shared_ptr<Node> right) :
		_lop(operation), _left(left), _right(right) {}
	bool Evaluate(const Date& date, const string& my_event)
	{
		//cout << "LogicalOperationNode" << endl;
		if (_lop == LogicalOperation::And)
		{
			//cout << "And" << endl;
			return (_left->Evaluate(date, my_event) && _right->Evaluate(date, my_event));
		}
		else if (_lop == LogicalOperation::Or)
		{
			//cout << "Or" << endl;
			return (_left->Evaluate(date, my_event) || _right->Evaluate(date, my_event));
		}
		else return true;
	}
private:
	LogicalOperation _lop;
	shared_ptr<Node> _left;
	shared_ptr<Node> _right;
};

class EmptyNode : public Node
{
public:
	bool Evaluate(const Date& date, const string& my_event)
	{
		return true;
	}
};