#include "Routine.hpp"
#include <cstring>
#include <sys/wait.h>



	
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


void Process::spawn() {
	id = fork();
	if(id == 0) {
		input->child();
		output->child();
		execvp(name.c_str(), prepare_exec().data());
	}
	else if(id > 0) {
		input->parent();
		output->parent();
	}
	else {
		//bład
	}
}

int Process::join() {
	int status;
	waitpid(id, &status, 0);
	return status;
}






void Pipeline::spawn() {
	auto it = processes.begin();
	auto end = processes.end();
	end--;
	while(it != end) {
		StreamConnector pair;
		(*it)->setOutput(pair.getOutput());
		it++;
		(*it)->setInput(pair.getInput());
	}
}

int Pipeline::join() {
	int ret;
	auto it = processes.begin();
	auto end = processes.end();
	while(it != end) {
		ret = (*it)->join();
		it++;
	}
	return ret;
}
	
	
		 
