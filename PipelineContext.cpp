#include "PipelineContext.hpp"
void PipelineContext::create
	(CommandParseContext & cont, const std::string & path) {
	exited = false;
	error.occur = false;
	pipes.setProcesses(cont.processes);
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
			return;
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
			return;
		}
		++nume;
	}
	if(cont.hasInput) {
		pipes.inputFile(cont.inputFile);
	}
	else {
		output = pipes.regularInput();
		outputAccessible = true;
	}
	
	if(cont.hasDirectOutput || cont.hasAppend) {
		pipes.outputFile(cont.outputFile, cont.hasAppend);
	}
	
	else {
		input = pipes.regularOutput();
		inputAccessible = false;
	}
	
	
		
	
}
