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
	std::list<CommandParseContext> subcommands;
	std::list<std::string> results;
	std::string text;
	std::string inputFile;
	std::string outputFile;
	bool hasInput;
	bool hasDirectOutput;
	bool hasAppend;
	bool inBackground;
	bool embedded;
	
	void parse() {
		}//pierwsze parsowanie
	void reparse() {
		}//podstawienie stringów z listy results za `...`
	
};
