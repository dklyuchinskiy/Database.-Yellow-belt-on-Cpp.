#include "node.h"

bool DateComparisonNode::Evaluate(const Date& date, const string& my_event)
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
	else
	{
		throw invalid_argument("Invalid argument in DateComparisonNode");
	}
}

bool EventComparisonNode::Evaluate(const Date& date, const string& my_event)
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
	else
	{
		throw invalid_argument("Invalid argument in EventComparisonNode");
	}
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& my_event)
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
	else
	{
		throw invalid_argument("Invalid argument in LogicalOperationNode");
	}
}

bool EmptyNode::Evaluate(const Date& date, const string& my_event)
{
	return true;
}