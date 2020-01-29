#pragma once

#include <memory>
#include <list>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <exception>

#include "Parser.hpp"
#include "VariablesTable.h"
#include "Pipeline.hpp"


class Shell {
	VariablesTable vars;

	public:


	Shell()
		{}
	
	void prompt() {
		fputs("$", stdout);
	}
	
	void interact();
	

};
