#include <utility>
#include "Command.hpp"
void CommandParseContext::hardcode() {
	// args-add `echo 44 | increment` `echo 23 | increment` ; args-increment `echo 55 | increment`
	
	CommandParseContext middlemost1;
	CommandParseContext middlemost2;

	CommandParseContext innermost1;
	CommandParseContext innermost2;
	
	innermost1.processes.push_back(EmbeddedProcess::makeMessage("44\n"));
	innermost1.processes.push_back(std::unique_ptr<Process>(new RealProcess("debug/increment")));
	innermost1.processes.push_back(EmbeddedProcess::makeVidmo());
	
	middlemost1.subcommands.push_back(std::move(innermost1));
	middlemost1.processes.push_back(std::unique_ptr<Process>(new RealProcess("debug/args_increment")));
	subcommands.push_back(std::move(middlemost1));
	
	innermost2.processes.push_back(EmbeddedProcess::makeMessage("55\n"));
	innermost2.processes.push_back(std::unique_ptr<Process>(new RealProcess("debug/increment")));
	innermost2.processes.push_back(EmbeddedProcess::makeVidmo());
	
	middlemost2.subcommands.push_back(std::move(innermost2));
	middlemost2.processes.push_back(std::unique_ptr<Process>(new RealProcess("debug/args_increment")));
	subcommands.push_back(std::move(middlemost2));
	
}
	
