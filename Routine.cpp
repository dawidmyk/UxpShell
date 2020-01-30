#include "Routine.hpp"
#include <cstring>
#include <sys/wait.h>

//Zastosowano rozwiązanie bałaganowe
//w budowaniu potoków

	
std::vector<char *> RealProcess::prepare_exec() {
	std::vector<char *> clear_args;
	{
		int len = name.length();
		char * loc = (char*)malloc(len + 1);
		memcpy(loc, name.data(), len);
		loc[len] = '\0';
		clear_args.push_back(loc);
	}
	for (auto arg: args) {
		int len = arg.length();
		char * loc = (char*)malloc(len + 1);
		memcpy(loc, arg.data(), len);
		loc[len] = '\0';
		clear_args.push_back(loc);
	}
	clear_args.push_back(nullptr);
	return clear_args;
}


char RealProcess::spawn() {
	id = fork();
	if(id < 0) return 0;
	if(input) {
		if(id == 0) {
			if(!input->child()) {
				fprintf(stderr, "Nie można otworzyć inputu (fork-exec)");
				exit(1);
			}
		}
		else {
			input->parent();
		}
	}
	if(output) {
		if(id == 0) {
			if(!output->child()) {
				fprintf(stderr, "Nie można otworzyć outputu (fork-exec)");
				exit(1);
			}
		}
		else {
			output->parent();
		}
	}
	if(id == 0) {
		execv(name.c_str(), prepare_exec().data());
		fprintf(stderr, "Nie można otworzyć pliku wykonywalnego\n");
		fprintf(stderr, "Błąd funkcji execv\n");
		fprintf(stderr, "Może plik ma zły format\n");

		exit(1);
	}

	return 1;
}

std::pair<std::string, int> RealProcess::join() {
	int status;
	waitpid(id, &status, 0);
	return std::make_pair<std::string, int>(std::string(""), (int)status);
}

char RealProcess::check(const std::string & path) {
		std::pair<std::string, char> result = checkExecAccess(name, path);
		if(result.second == 0) name = result.first;
		return result.second;
}







	
		 
