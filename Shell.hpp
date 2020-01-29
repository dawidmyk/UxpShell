#pragma once

#include <memory>
#include <list>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <exception>

#include "Parser.hpp"
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
