#pragma once
#include "Streams.hpp"
#include <vector>

class Routine {
	public:
	virtual char spawn() = 0;
	virtual int join() = 0;
	virtual void setInput(std::unique_ptr<InputStream> stream) = 0;
	virtual void setOutput(std::unique_ptr<OutputStream> stream) = 0;
	
	void write(const std::string & output) {
		setInput(std::unique_ptr<InputStream>(new WriteStream(output)));
	}
	
	void inputFile(const std::string & filename) {
		setInput(std::unique_ptr<InputStream>(new FileInputStream(filename)));
	}
	void outputFile(const std::string & filename, bool append) {
		setOutput(std::unique_ptr<OutputStream>(new FileOutputStream(filename, append)));
	}
	//background / foreground nie dodaje bo to działka kogoś innego
};

class Process : public Routine {
	
	pid_t id;
	std::string name;
	std::vector<std::string> args;
	std::unique_ptr<InputStream> input;
	std::unique_ptr<OutputStream> output;
	
	public:
	
	Process(): id(-1) {}
	Process(const std::string & name): id(-1), name(name) {}
	
	void setName(const std::string & name) {
		this->name = name;
	}
	
	void addArg(const std::string & arg) {
		args.push_back(arg);
	}
	
	void setInput(std::unique_ptr<InputStream> stream) {
		input = std::move(stream);
	}
	
	void setOutput(std::unique_ptr<OutputStream> stream) {
		output = std::move(stream);
	}
	
	private:
	
	std::vector<char *> prepare_exec();
   
   public:
   
   char spawn();
	
	int join();
	
};
	
	
	

class Pipeline : public Routine {
	
	std::vector<std::unique_ptr<Process>> processes;
	
	public:
	
	void addProcess(std::unique_ptr<Process> process) {
		processes.push_back(std::move(process));
	}
	
	//minimalna długość pipelin'u to 2 procesy i o to trzeba zadbać gdzieś indziej
	void setInput(std::unique_ptr<InputStream> stream) {
		processes.at(0)->setInput(std::move(stream));
	}
	
	void setOutput(std::unique_ptr<OutputStream> stream) {
		processes.at(processes.size() - 1)->setOutput(std::move(stream));
	}
	
	char spawn();
	
	int join();
		
};
	
	
		 
