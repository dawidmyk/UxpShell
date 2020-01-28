#pragma once

#include <memory>
#include <atomic>
#include <list>
#include <thread>
#include <iostream>
#include <cstdio>
#include <sstream>

#include "Parser/Parser.hpp"
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
	
	void shell_exit() {
		alive = false;
	}

	Shell():
		alive(false), exited(false), isForeground(false),
		foreground(nullptr)
		{}
	
	void prompt() {
		std::cout << "$";
	}
	
	void input();
	
	void interact();
	
	void output();
	
	void circ();
		
	
		
			
};
