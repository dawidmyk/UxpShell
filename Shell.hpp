#pragma once

#include <memory>
#include <atomic>
#include <list>
#include <thread>
#include <pthread.h>
#include <iostream>
#include <cstdio>

#include "VariableContext.hpp"
#include "PipelineContext.hpp"


class Shell {
	std::unique_ptr<std::thread> outputThread;
	std::unique_ptr<std::thread> inputThread;
	std::unique_ptr<std::thread> circThread;
	std::unique_ptr<std::thread> interactThread;
	std::atomic<bool> alive;
	std::atomic<bool> exited;
	std::atomic<bool> isForeground;
	PipelineContext * foreground;
	VariableContext vars;
	std::unique_ptr<PipelineContext> exitedPipeline;
	std::list<std::unique_ptr<PipelineContext>> pipelines;
	public:
	void start();
	
	void stop();


	
	void prompt() {
		std::cout << "$";
	}
	
	void input();
	
	void interact();
	
	void output();
	
	void circ();
		
	
		
			
};
