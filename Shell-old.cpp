#include "Shell.hpp"

void Shell::interact() {
	while(true) {
		prompt();
		char line[100];
		fgets(line, 100, stdin);
		//tutaj można zbudować komendę
		//próbujemy wczytać komendę
		//parsujemy ją
		bool commandAccepted = true;
		CommandParseContext command;
		command.type = CommandType::new_pipeline;
		command.processes.push_back(std::unique_ptr<Process>(new Process("debug/tested")));
		command.hasInput = false;
		command.hasDirectOutput = false;
		command.hasAppend = false;
		command.inBackground = false;
		
		if(commandAccepted) { //ta zmienna tak umownie
			if(command.type == CommandType::new_pipeline) {
				Pipeline pipe;
				PipelineError error = pipe.create(command, vars.getPath());
				if(error.occur) {
					printf("Wystąpił błąd\n");
				}
				else {
					pipe.spawn();
					pipe.join();
				}
					
			}
			else if(command.type == CommandType::exit) {
				break;
		}
		}
	}
}
