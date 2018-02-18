#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <exception>
#include <vector>
#include <iomanip>
#include <sstream>
#include <tuple>

using namespace std;

#include "test_runner.h"

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
	cout << endl;
}