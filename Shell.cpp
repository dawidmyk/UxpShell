#include "Shell.hpp"

void Shell::interact() {
	while(true) {
		CommandParseContext uttermost;
		/*
		CommandParseContext real_command;
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
		*/
		
		prompt();
		std::string line;
		std::getline(std::cin, line);
		uttermost.text = line;
		uttermost.parse();
		
		auto middleIt = uttermost.subcommands.begin();
		auto middleEnd = uttermost.subcommands.end();
		while(middleIt != middleEnd) {
			CommandParseContext middlemost = std::move(*middleIt);
			middlemost.parse();
			auto innerIt = middlemost.subcommands.begin();
			auto innerEnd = middlemost.subcommands.end();
			
			bool last = false;
			if(middlemost.subcommands.empty()) last = true;
		
			while(innerIt != innerEnd || last) {
				CommandParseContext innermost;
				if(last) {
					innermost = std::move(middlemost);
					innermost.reparse();
				}
				else innermost = std::move(*innerIt);
				
				/*
				CommandParseContext real_command;
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
				*/
		//tutaj można zbudować komendę
		//próbujemy wczytać komendę
		//parsujemy ją
		
		CommandParseContext command;
		std::unique_ptr<Process> beg(EmbeddedProcess::makeMessage("44\n"));
		std::unique_ptr<Process> middle1(new RealProcess("lsl"));
		//std::unique_ptr<Process> middle2(new RealProcess("debug/increment"));

		std::unique_ptr<Process> end(EmbeddedProcess::makeVidmo());
		command.processes.push_back(std::move(beg));
		command.processes.push_back(std::move(middle1));
		//command.processes.push_back(std::move(middle2));

		command.processes.push_back(std::move(end));
		
		command.type = CommandType::new_pipeline;
		command.hasInput = false;
		command.hasDirectOutput = false;
		command.hasAppend = false;
		command.inBackground = false;
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
					std::pair<std::string, int> result = pipe.join();
					vars.setReturn(result.second);
					if(!last) middlemost.results.push_back(result.first);
					std::cout << "Oto co nam powiedział potok: " << result.first << std::endl;
				}
		
			}
			else if(command.type == CommandType::exit) {
				break;
			}
		}
		if(last) last = false;
		if(!last) ++innerIt;
	}
	++middleIt;
	}		
	}
}
