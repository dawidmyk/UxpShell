#include "Pipeline.hpp"
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
	
	(*begin)->realiseOutput();
	(*prev_end)->realiseInput();
	
	return i;
	
}

std::pair<std::string, int> Pipeline::join() {
	std::pair<std::string, int> ret;
	auto it = processes.begin();
	auto end = processes.end();
	while(it != end) {
		ret = (*it)->join();
		it++;
	}
	return ret;
}


PipelineError Pipeline::create
	(CommandParseContext & cont, const std::string & path) {
	PipelineError error;
	error.occur = false;
	
	char fileEffect[3] = {0};
	std::string filenames[3];
	filenames[0] = cont.inputFile;
	filenames[1] = cont.outputFile;
	filenames[2] = cont.outputFile;
	if(cont.hasInput) {
		fileEffect[0] = checkAccess(filenames[0], 0);
	}
	if(cont.hasDirectOutput) {
		fileEffect[1] = checkAccess(filenames[1], 1);
	}
	if(cont.hasAppend) {
		fileEffect[2] = checkAccess(filenames[2], 2);
	}
	for(char i = 0; i != 3; ++i) {
		if(fileEffect[i] != 0) {
			error.occur = true;
			error.effect = fileEffect[i];
			error.which = i;
			error.nume = 0;
			error.filename = filenames[i];
			return error;
		}
	}
	auto it = cont.processes.begin();
	auto end = cont.processes.end();
	int nume = 1;
	for(; it != end; ++it) {
		char effect = (*it)->check(path);
		if(effect != 0) {
			error.occur = true;
			error.effect = effect;
			error.which = 3;
			error.filename = (*it)->getName();
			error.nume = nume;
			return error;
		}
		++nume;
	}
	setProcesses(cont.processes);
	if(cont.hasInput) {
		inputFile(cont.inputFile);
	}
	
	if(cont.hasDirectOutput || cont.hasAppend) {
		outputFile(cont.outputFile, cont.hasAppend);
	}
	
	return error;
	
}
