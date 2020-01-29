#include "Routine.hpp"
#include "PipelineError.hpp"
#include "Command.hpp"
#include <string>
class Pipeline : public Routine {
	
	std::list<std::unique_ptr<Process>> processes;
	
	public:
	
	void setProcesses(std::list<std::unique_ptr<Process>> & process_list) {
		processes = std::move(process_list);
	}
	
	void addProcess(std::unique_ptr<Process> process) {
		processes.push_back(std::move(process));
	}
	
	void setInput(std::unique_ptr<InputStream> stream) {
		(*processes.begin())->setInput(std::move(stream));
	}
	
	void setOutput(std::unique_ptr<OutputStream> stream) {
		auto end = processes.end();
		end--;
		(*end)->setOutput(std::move(stream));
	}
	
	char spawn();
	
	std::pair<std::string, int> join();
	
	char check(const std::string & path);
	
	PipelineError create(CommandParseContext & cont, const std::string & path);
	
	std::string read() {
		auto end = processes.end();
		end--;
		return (*end)->read();
	}

	
};
