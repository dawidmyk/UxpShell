#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
//#include "pch.h"
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
	string ret = getEnvironmentVariable(name)
	if(ret.length>0) {
		return ret;
	}
	
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

/* kiedy parser wykryje że inicjalizujemy zmienną środowiskową */
void VariablesTable::setEnvironmentVariable(string nameS, string x) { 
    char* name= new char[nameS.length() + 1]; 
    strcpy(name, nameS.c_str());  
	
	char* value= new char[x.length() + 1]; 
    strcpy(value, x.c_str());  
	
	setenv(const char *name, const char *value, int 1);
}

string VariablesTable::getEnvironmentVariable(string nameS) { 
    char* name= new char[nameS.length() + 1]; 
    strcpy(name, nameS.c_str());

	char* envVar = char *getenv(const char *name);
	if(envVar)
		return string(envVar);
	else
		return "";
}

void VariablesTable::setActualPath(string nameS) {	// funkcja do ustawiania ścieżki względnej lub bezwględnej
	char* name= new char[nameS.length() + 1]; 		// zamiana stringa na char*
    strcpy(name, nameS.c_str());	
		
	actualPWD = realpath(name, null);						// funkcja linuxowa do zamiany ścieżki na bezwzględną
	
	chdir(actualPWD);											// funkcja systemowa do ustawienia aktualnego katalogu
}

string VariablesTable::getActualPath() {					// funkcja do zwracania naszego aktualnego katalogu
	return string(get_current_dir_name(void));
}

