#pragma once
#include <string>

using namespace std;

class Variable
{
private:
	string name;

	int intValue;
	double doubleValue;
	string stringValue;

public:
	Variable(string);
	~Variable();

	void setIntValue(int);
	void setDoubleValue(double);
	void setStringValue(string);

	int getIntValue();
	double getDoubleValue();
	string getStringValue();
};

