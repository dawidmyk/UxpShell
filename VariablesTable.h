/*
	Tutaj nie ma wi�kszej filozofii. Tablica trzymaj�ca hashmap� i interfejs dost�pu. 
	
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
		getStringVariable() - wraca zmienn� �rodowiska, a jak nie ma to lokaln�
		setStringValue() - ustawnianie zmiennej lokalnej
		setEnvironmentVariable() - ustawianie zmienneh �rodowiskowej



*/



#pragma once
#include <string>
#include <iostream>
#include <map>
#include "Variable.h"

using namespace std;

class VariablesTable
{
private:

	map<string, Variable*> idToVariable;
	char* actualPWD;
	void exsist(string);
	string getEnvironmentVariable(string);
	

public:
	VariablesTable();
	~VariablesTable();

	void addNewVariable(string);

	//int getIntVariable(string);
	//double getDoubleVariable(string);
	string getStringVariable(string);

	//void setIntValue(string, int);
	//void setDoubleValue(string, double);
	void setStringValue(string, string);
	
	void setEnvironmentVariable(string, string)	//ustawianie zmiennej
	
	void setActualPath(string name); // �cie�ka albo pe�na albo wzgl�dna typu ./local
	string getActualPath();			//zwraca lokalizacj� aktualnego katalogu
};

