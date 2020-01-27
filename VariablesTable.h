/*
	Struktura zawieraj�ca zmienne systemowe w postaci hasmapy identyfikowanej przez nazw� zmiennej
	Ka�da zmienna reprezentowana jest przez klas� Variable
	zmienne nie maj� typu jako takiego. Mo�na je inicjowa� intem, double i stringiem u�ywaj�c odpowiednich metod set...()
	kiedy b�dziemy chcieli dobra� si� do danej warto�ci u�ywamy metod get...()
	dane s� sp�jne i je�eli zapiszemy string do zmiennej a b�dziemy chcieli odczyta� u�ywaj�c getIntVariable to otrzymamy d�ugo�� zmiennej
	je�li zapiszemy inta np. 42 a b�dziemy chcieli odczyta� stringa to otrzymamy �a�cuch: "42" itp.


	Instrukcja:
		Tworzymy w dogodnym miejscu VariablesTable

	Interfejs:
		addNewVariable(string) - jawne stworzenie zmiennej zainicjowanej warto�ciami domy�lnymi

		get...() - zwraca dan� warto��. Je�eli zmienna by�a niezainicjowana to stworzy now� i zwr�ci warto�ci domy�lne czyli int 0, double 0.0, string ""

		set...() - inicjowanie zmiennej. Je�eli nie istnia�a to zostanie utworzona z podanymi warto�ciami.

	W rezultacie wystarcz� same:
		get...()
		set...()


*/



#pragma once
#include <string>
#include <iostream>
#include <map>
#include "Variable.h"

using namespace std;

class VariablesTable
{
public:
	enum env {LOCAL, GLOBAL};	

	map<string, Variable*> idToVariableGlobal;
	map<string, Variable*> idToVariableLocal;
	bool isExsist(string, map<string, Variable*>);

public:
	VariablesTable();
	~VariablesTable();

	void addNewVariable(string, env);

	int getIntVariable(string);
	double getDoubleVariable(string);
	string getStringVariable(string);

	void setIntValue(string, int, env);
	void setDoubleValue(string, double, env);
	void setStringValue(string, string, env);


	char** getGlobalEnvironment();
	char** getLocalEnvironment();
};

