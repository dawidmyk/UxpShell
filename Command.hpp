#pragma once
#include <list>
#include <string>
#include "Routine.hpp"
enum class CommandType {
	no_type,
	new_pipeline,
	exit,
	bg,
	fg,
	jobs,
	echo,
	pwd,
	cd,
	var_set
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
	bool accepted;
	bool inBackground;
	
	void parse() {
		}//pierwsze parsowanie
	void reparse() {
		}//podstawienie stringów z listy results za `...`
	
	void hardcode();
	
	CommandParseContext(): hasInput(false), hasDirectOutput(false), 
		hasAppend(false), accepted(false), type(CommandType::no_type)
		{
		}
};
