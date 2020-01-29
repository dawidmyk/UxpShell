/*
	Tutaj nie ma większej filozofii. Tablica trzymająca hashmapę i interfejs dostępu. 
	
	Struktura zawierająca zmienne systemowe w postaci hasmapy identyfikowanej przez nazwę zmiennej
	Każda zmienna reprezentowana jest przez klasę Variable
	zmienne nie mają typu jako takiego. Można je inicjować intem, double i stringiem używając odpowiednich metod set...()
	kiedy będziemy chcieli dobrać się do danej wartości używamy metod get...()
	dane są spójne i jeżeli zapiszemy string do zmiennej a będziemy chcieli odczytać używając getIntVariable to otrzymamy długość zmiennej
	jeśli zapiszemy inta np. 42 a będziemy chcieli odczytać stringa to otrzymamy łańcuch: "42" itp.


	Instrukcja:
		Tworzymy w dogodnym miejscu VariablesTable

	Interfejs:
		addNewVariable(string) - jawne stworzenie zmiennej zainicjowanej wartościami domyślnymi

		get...() - zwraca daną wartość. Jeżeli zmienna była niezainicjowana to stworzy nową i zwróci wartości domyślne czyli int 0, double 0.0, string ""

		set...() - inicjowanie zmiennej. Jeżeli nie istniała to zostanie utworzona z podanymi wartościami.

	W rezultacie wystarczą same:
		getStringVariable() - wraca zmienną środowiska, a jak nie ma to lokalną
		setStringValue() - ustawnianie zmiennej lokalnej
		setEnvironmentVariable() - ustawianie zmienneh środowiskowej



*/



#pragma once
#include <string>
#include <iostream>
#include <map>
#include "Variable.h"

using std::string;

class VariablesTable
{
private:

	map<string, Variable*> idToVariable;
	char* actualPWD;
	int lastResult;
	void exsist(string);
	string getEnvironmentVariable(string);
	

public:
	VariablesTable();
	~VariablesTable();

	void addNewVariable(string);

	int getIntVariable(string);
	double getDoubleVariable(string);
	string getStringVariable(string);

	void setIntValue(string, int);
	void setDoubleValue(string, double);
	void setStringValue(string, string);
	
	void setEnvironmentVariable(string, string);	//ustawianie zmiennej
	
	void setActualPath(string name); // ścieżka albo pełna albo względna typu ./local
	string getActualPath();			//zwraca lokalizację aktualnego katalogu
	
	void setLastResult(int);
	int getLastResult();
	
	string getSystemPath();
	
};

