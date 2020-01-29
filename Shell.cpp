#include "Shell.hpp"

void Shell::interact() {
	while(true) {
		
			
		//char line[100];
		//fgets(line, 100, stdin);
		CommandParseContext command;
		std::stringstream ss;
		std::string line;
		parser::Parser p(std::make_unique<Scanner>(ss));
		getline(std::cin, line);
		ss.str(line);
		std::unique_ptr<Expression> ex;
		try
		{
			ex = p.parse();
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
		ex->execute(&command);

		//tutaj można zbudować komendę
		//próbujemy wczytać komendę
		//parsujemy ją
		bool commandAccepted = true;
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

