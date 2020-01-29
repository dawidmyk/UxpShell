#pragma once
#include <list>
#include <string>
#include "Routine.hpp"
enum class CommandType {
	new_pipeline,
	exit,
	bg,
	fg,
	jobs,
	echo,
	pwd,
	cd
	//i inne
};





struct CommandParseContext {
	CommandType type;
	std::list<std::unique_ptr<Process>> processes;
	std::string inputFile;
	std::string outputFile;
	bool hasInput;
	bool hasDirectOutput;
	bool hasAppend;
	bool inBackground;
	bool embedded;
};
