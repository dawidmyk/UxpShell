#include "pch.h"
#include "Variable.h"


Variable::Variable(string x) {
	name = x;
	intValue = 0;
	doubleValue = 0.0;
	stringValue = "";
}


Variable::~Variable() {
}

void Variable::setIntValue(int x) {
	intValue = x;
	doubleValue = (double)x;
	stringValue = to_string(x);
}
void Variable::setDoubleValue(double x) {
	intValue = (int)x;
	doubleValue = x;
	stringValue = to_string(x);
}
void Variable::setStringValue(string x) {
	intValue = x.length();
	doubleValue = (double)x.length();
	stringValue = x;
}

int Variable::getIntValue() {
	return intValue;
}
double Variable::getDoubleValue() {
	return doubleValue;
}
string Variable::getStringValue() {
	return stringValue;
}
