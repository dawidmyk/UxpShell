#include "pch.h"
#include <iostream>
#include "VariablesTable.h"


int main()
{
	VariablesTable table;

	table.setDoubleValue("zmienna1", 2321.321);
	table.setDoubleValue("zmienna2", 2321.3223534234);
	table.setDoubleValue("zmienna3", 2321343424324231);
	table.setIntValue("zmienna4", 232342.432);
	table.setIntValue("zmienna5", 232342);
	table.setStringValue("zmienna6", "232342");
	table.setStringValue("zmienna1", "dassadsaas  dwwqddw");
	table.setStringValue("plik1", "/etc/passwd");

	map<string, Variable*>::iterator it = table.idToVariable.begin();
	for (; it != table.idToVariable.end(); it++) {
		cout << "=====================" << endl;
		cout <<"nazwa zmiennej: "<< it->first << endl;
		cout <<"double: "<< it->second->getDoubleValue() << endl;
		cout << "int: " << it->second->getIntValue() << endl;
		cout << "string: " << it->second->getStringValue() << endl;
		cout << endl;
	}


	return 0;
}
