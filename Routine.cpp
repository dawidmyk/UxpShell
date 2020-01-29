#include "Routine.hpp"
#include <cstring>
#include <sys/wait.h>

//Zastosowano rozwiązanie bałaganowe
//w budowaniu potoków

	
std::vector<char *> Process::prepare_exec() {
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


char Process::spawn() {
	id = fork();
	if(id < 0) return 0;
	if(input) {
		if(id == 0) {
			if(!input->child()) {
				fprintf(stderr, "Dzieciak wyskakuje w input\n");
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
				fprintf(stderr, "Dzieciak wyskakuje w output\n");
				exit(1);
			}
		}
		else {
			output->parent();
		}
	}
	if(id == 0) {
		execv(name.c_str(), prepare_exec().data());
		fprintf(stderr, "Dzieciak wyskakuje w exec\n");
		exit(1);
	}

	return 1;
}

int Process::join() {
	int status;
	waitpid(id, &status, 0);
	return status;
}








	
		 
