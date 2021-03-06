#pragma once
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






char Pipeline::spawn() {
	auto begin = processes.begin();
	auto end = processes.end();
	auto it = begin;
	auto prev_end = end;
	prev_end--;
	while(it != prev_end) {
		StreamConnector pair;
		(*it)->setOutput(pair.getOutput());
		it++;
		(*it)->setInput(pair.getInput());
	}
	it = begin;
	char i = 1;
	while(it != end) {
		char now_i;
		now_i = (*it)->spawn();
		if(now_i == 0) i = 0;
		it++;
	}
	return i;
	
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

char Process::check() {
		std::string path(getenv("PATH")); //ona może być też przekazana jako argument
		std::pair<std::string, char> result = checkExecAccess(name, path);
		if(result.second == 0) name = result.first;
		return result.second;
}

char Pipeline::check() {
	for(auto & proc : processes) {
		char i = proc->check();
		if(i != 0) return i;
	}
}

	
		 
