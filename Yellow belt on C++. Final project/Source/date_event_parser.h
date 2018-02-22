#pragma once
#include "lib.h"
#include "date.h"

using namespace std;

void TestParseEvent();
void TestParseDate();

string ParseEvent(istream& is);
Date ParseDate(istream& is);