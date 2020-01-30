#include "PipelineError.hpp"
void PipelineError::present() {
		fprintf(stderr, "Wystąpił błąd\n");
		switch(which) {
			case 0:
			fprintf(stderr, "W pliku wejściowym:\n"); break;
			case 1:
			case 2:
			fprintf(stderr, "W pliku wyjściowym:\n"); break;
			case 3:
			fprintf(stderr, "W pliku przeznaczonym do wykonania:\n"); break;
			default:
			fprintf(stderr, "Nieokreślony\n"); return;
		}
		fprintf(stderr, "%s\n", filename.c_str());
		if(which == 3) {
			fprintf(stderr, "Który jest %d. stopniem potoku\n", nume);
		}
		if(effect == 1) { 
			fprintf(stderr, "Plik nie istnieje\n");
		}
		else if(effect == 2)
			fprintf(stderr, "Nie masz uprawnień do otwarcia tego pliku\n");
		
	}
