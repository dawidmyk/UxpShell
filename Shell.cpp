#include "Shell.hpp"
void Shell::start() {
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
				char i = getchar();
				//albo jakaś inna funkcja powyżej
				foreground->putChar(i);
			}
		}
}

void Shell::interact() {
		while(alive) {
			while(!isForeground) {
				prompt();
				//tutaj można zbudować komendę
				//próbujemy wczytać komendę
				//parsujemy ją
				bool commandAccepted = true;
				CommandParseContext command;
				if(commandAccepted) { //ta zmienna tak umownie
					if(command.type == CommandType::new_pipeline) {
						std::unique_ptr<PipelineContext> pipe(new PipelineContext(command, vars.getPath()));
						PipelineError error = pipe->check();
						if(error.occur) {
							//wyświetl informacje o błędzie
						}
						else {
							pipe->spawnItself();
							pipe->spawnWaiting();
							pipelines.push_back(std::move(pipe));
						}
							
					}
					else if(command.type == CommandType::exit) {
						stop();
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
				if(exitedPipeline.get() == foreground) {
					isForeground = false;
					foreground = nullptr;
				}
				it = pipelines.erase(it);
			}
		}
	}
}
