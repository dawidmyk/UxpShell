#include "Shell.hpp"
void Shell::start() {
		alive = true;
		outputThread.reset(new std::thread(&Shell::output, this));
		inputThread.reset(new std::thread(&Shell::input, this));
		circThread.reset(new std::thread(&Shell::circ, this));
		interactThread.reset(new std::thread(&Shell::interact, this));
	}
	
void Shell::stop() {
		if(outputThread->joinable()) outputThread->join();
		if(inputThread->joinable()) inputThread->join();
		if(circThread->joinable()) circThread->join();
		if(interactThread->joinable()) interactThread->join();
}
	
void Shell::input() {
		while(alive) {
			while(isForeground) { //tu będzie aktywne oczekiwanie
				//więc warto zastosować jakiś inny mechanizm
				
				//trzeba zrobić selectem/pollem żeby wejście było nieblokujące
				while(isForeground) {
					char i = getchar();
					//albo jakaś inna funkcja powyżej
					foreground->putChar(i);
				}
			}
		}
}

void Shell::interact() {
		while(alive) {
			while(!isForeground) {
				prompt();
				char line[100];
				fgets(line, 100, stdin);
				//tutaj można zbudować komendę
				//próbujemy wczytać komendę
				//parsujemy ją
				bool commandAccepted = true;
				CommandParseContext command;
				command.type = CommandType::new_pipeline;
				command.processes.push_back(std::unique_ptr<Process>(new Process("debug/first-tested")));
				command.hasInput = false;
				command.hasDirectOutput = false;
				command.hasAppend = false;
				command.inBackground = false;
				
				if(commandAccepted) { //ta zmienna tak umownie
					if(command.type == CommandType::new_pipeline) {
						std::unique_ptr<PipelineContext> pipe(new PipelineContext(command, vars.getPath()));
						PipelineError error = pipe->check();
						if(error.occur) {
							printf("Wystąpił błąd\n");
						}
						else {
							pipe->spawnItself();
							pipe->spawnWaiting();
							PipelineContext * evForeground = pipe.get();
							pipelines.push_back(std::move(pipe));
							if(!command.inBackground) {
								isForeground = true;
								foreground = evForeground;
							}
						}
							
					}
					else if(command.type == CommandType::exit) {
						shell_exit();
					}
				}
			}
	}
}

void Shell::output() {
		while(alive) {
			while(isForeground) {
				char i;
				//albo jakaś inna funkcja powyżej
				foreground->getChar(i);
				putchar(i);
			}
		}
}

void Shell::circ() {
	while(alive) {
		auto it = pipelines.begin();
		auto end = pipelines.end();
		for(;it != end; ++it) {
			if((*it)->exited) {
				exited = true;
				exitedPipeline = std::move(*it);
				exitedPipeline->join();
				if(exitedPipeline.get() == foreground) {
					isForeground = false;
					foreground = nullptr;
				}
				it = pipelines.erase(it);
			}
		}
	}
}
