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
#include "Pipeline.hpp"


class Shell {
	VariableContext vars;

	public:


	Shell()
		{}
	
	void prompt() {
		fputs("$", stdout);
	}
	
	void interact();
	

};
