/*
	Tutaj nie ma wiêkszej filozofii. Tablica trzymaj¹ca hashmapê i interfejs dostêpu. 
	
	Struktura zawieraj¹ca zmienne systemowe w postaci hasmapy identyfikowanej przez nazwê zmiennej
	Ka¿da zmienna reprezentowana jest przez klasê Variable
	zmienne nie maj¹ typu jako takiego. Mo¿na je inicjowaæ intem, double i stringiem u¿ywaj¹c odpowiednich metod set...()
	kiedy bêdziemy chcieli dobraæ siê do danej wartoœci u¿ywamy metod get...()
	dane s¹ spójne i je¿eli zapiszemy string do zmiennej a bêdziemy chcieli odczytaæ u¿ywaj¹c getIntVariable to otrzymamy d³ugoœæ zmiennej
	jeœli zapiszemy inta np. 42 a bêdziemy chcieli odczytaæ stringa to otrzymamy ³añcuch: "42" itp.


	Instrukcja:
		Tworzymy w dogodnym miejscu VariablesTable

	Interfejs:
		addNewVariable(string) - jawne stworzenie zmiennej zainicjowanej wartoœciami domyœlnymi

		get...() - zwraca dan¹ wartoœæ. Je¿eli zmienna by³a niezainicjowana to stworzy now¹ i zwróci wartoœci domyœlne czyli int 0, double 0.0, string ""

		set...() - inicjowanie zmiennej. Je¿eli nie istnia³a to zostanie utworzona z podanymi wartoœciami.

	W rezultacie wystarcz¹ same:
		getStringVariable() - wraca zmienn¹ œrodowiska, a jak nie ma to lokaln¹
		setStringValue() - ustawnianie zmiennej lokalnej
		setEnvironmentVariable() - ustawianie zmienneh œrodowiskowej



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
	
	void setActualPath(string name); // œcie¿ka albo pe³na albo wzglêdna typu ./local
	string getActualPath();			//zwraca lokalizacjê aktualnego katalogu
};

