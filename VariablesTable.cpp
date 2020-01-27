#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "pch.h"
#include "VariablesTable.h"

using namespace std;

VariablesTable::VariablesTable() {
}


VariablesTable::~VariablesTable() {
	map<string, Variable*>::iterator it = idToVariable.begin();
	for (; it != idToVariable.end(); it++) {
		free(it->second);
	}
	idToVariable.clear();
}

void VariablesTable::addNewVariable(string name) {
	idToVariable.insert(make_pair(name, new Variable(name)));
}

int VariablesTable::getIntVariable(string name) {
	exsist(name);
	return idToVariable[name]->getIntValue();
}
double VariablesTable::getDoubleVariable(string name) {
	exsist(name);
	return idToVariable[name]->getDoubleValue();
}
string VariablesTable::getStringVariable(string name) {
	exsist(name);
	return idToVariable[name]->getStringValue();
}

void VariablesTable::setIntValue(string name, int x) {
	exsist(name);
	idToVariable[name]->setIntValue(x);
}
void VariablesTable::setDoubleValue(string name, double x) {
	exsist(name);
	idToVariable[name]->setDoubleValue(x);
}
void VariablesTable::setStringValue(string name, string x) {
	exsist(name);
	idToVariable[name]->setStringValue(x);
}

void VariablesTable::exsist(string name) {
	if (idToVariable.count(name) > 0) {
		return;
	}
	addNewVariable(name);
}