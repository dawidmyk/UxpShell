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
	map<string, Variable*>::iterator it = idToVariableLocal.begin();
	for (; it != idToVariableLocal.end(); it++) {
		delete(it->second);
	}
	idToVariableLocal.clear();

	it = idToVariableGlobal.begin();
	for (; it != idToVariableGlobal.end(); it++) {
		delete(it->second);
	}
	idToVariableGlobal.clear();
}

void VariablesTable::addNewVariable(string name, env e) {
	if (e == LOCAL) {
		if (isExsist(name, idToVariableLocal) == false) {
			idToVariableLocal.insert(make_pair(name, new Variable(name)));
		}
	}else
		if (isExsist(name, idToVariableGlobal) == false)
			idToVariableGlobal.insert(make_pair(name, new Variable(name)));
}

int VariablesTable::getIntVariable(string name) {
	if (isExsist(name, idToVariableLocal)) 
		return idToVariableLocal[name]->getIntValue();
	else if (isExsist(name, idToVariableGlobal))
		return idToVariableGlobal[name]->getIntValue();
	else return 0;
}
double VariablesTable::getDoubleVariable(string name) {
	if (isExsist(name, idToVariableLocal))
		return idToVariableLocal[name]->getDoubleValue();
	else if (isExsist(name, idToVariableGlobal))
		return idToVariableGlobal[name]->getDoubleValue();
	else return 0;
}
string VariablesTable::getStringVariable(string name) {
	if (isExsist(name, idToVariableLocal))
		return idToVariableLocal[name]->getStringValue();
	else if (isExsist(name, idToVariableGlobal))
		return idToVariableGlobal[name]->getStringValue();
	else return 0;
}

void VariablesTable::setIntValue(string name, int x, env tab) {
	if (tab == LOCAL) {
		if (isExsist(name, idToVariableLocal) == false) {
			addNewVariable(name, tab);
		}
		idToVariableLocal[name]->setIntValue(x);
	}
	else {
		if (isExsist(name, idToVariableGlobal) == false) {
			addNewVariable(name, tab);
		}
		idToVariableGlobal[name]->setIntValue(x);
	}
}
void VariablesTable::setDoubleValue(string name, double x, env tab) {
	if (tab == LOCAL) {
		if (isExsist(name, idToVariableLocal) == false) {
			addNewVariable(name, tab);
		}
		idToVariableLocal[name]->setDoubleValue(x);
	}
	else {
		if (isExsist(name, idToVariableGlobal) == false) {
			addNewVariable(name, tab);
		}
		idToVariableGlobal[name]->setDoubleValue(x);
	}
}
void VariablesTable::setStringValue(string name, string x, env tab) {
	if (tab == LOCAL) {
		if (isExsist(name, idToVariableLocal) == false) {
			addNewVariable(name, tab);
		}
		idToVariableLocal[name]->setStringValue(x);
	}
	else {
		if (isExsist(name, idToVariableGlobal) == false) {
			addNewVariable(name, tab);
		}
		idToVariableGlobal[name]->setStringValue(x);
	}
}

bool VariablesTable::isExsist(string name, map<string, Variable*> tab) {
	if (tab.count(name) > 0) {
		return true;
	}
	return false;
}

char** VariablesTable::getGlobalEnvironment() {
	char ** tab = new char*[idToVariableGlobal.size() + 1];

	map<string, Variable*>::iterator it = idToVariableGlobal.begin();
	for (int i = 0; it != idToVariableGlobal.end(); i++, it++) {
		string s = it->first + "=" + it->second->getStringValue() + '\0';
		char* cstr = new char[s.size() + 1];
		copy(s.begin(), s.end(), cstr);
		tab[i] = cstr;
	}
	tab[idToVariableLocal.size()] = nullptr;
	return tab;

}
char** VariablesTable::getLocalEnvironment() {
	char ** tab = new char*[idToVariableLocal.size() + 1];

	map<string, Variable*>::iterator it = idToVariableLocal.begin();
	for (int i=0; it != idToVariableLocal.end(); i++, it++) {	
		string s = it->first + "=" + it->second->getStringValue() + '\0';
		char* cstr = new char[s.size() + 1];
		copy(s.begin(), s.end(), cstr);
		tab[i] = cstr;
	}
	tab[idToVariableLocal.size()] = nullptr;
	return tab;
}