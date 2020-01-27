#pragma once
#include <list>
#include <atomic>
#include <thread>
#include "Command.hpp"
#include "PipelineError.hpp"
class PipelineContext {
	Pipeline pipes;
	std::unique_ptr<PipeInputStream> input; //nasz input, ale output pipeline'u
	std::unique_ptr<PipeOutputStream> output; //nasz output, ale input pipeline'u
	bool inputAccessible;
	bool outputAccessible;
	
	std::unique_ptr<std::thread> joining;
	PipelineError error;
	public:
	std::atomic<bool> exited;
	PipelineContext(CommandParseContext & cont, const std::string & path) {
		create(cont, path);
	}
	
	PipelineError check() {
		return error;
	}
		
			
	void create(CommandParseContext & cont, const std::string & path);
	
	void spawnItself() {
		pipes.spawn();
	}	
	
	void wait() {
		pipes.join();
		exited = true;
	}
	
	void spawnWaiting() {
		joining.reset(new std::thread(&PipelineContext::wait, this));
	}
		
	
	
	void putChar(const char i) {
		if(outputAccessible) output->writeChar(i);
	}
	
	void getChar(char & i) {
		if(inputAccessible) input->readChar(i);
	}
	
};
	
