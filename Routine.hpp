#pragma once
#include "Streams.hpp"
#include "Access.hpp"

#include <vector>
#include <list>

class Routine {
	public:
	virtual char spawn() = 0;
	virtual int join() = 0;
	virtual void setInput(std::unique_ptr<InputStream> stream) = 0;
	virtual void setOutput(std::unique_ptr<OutputStream> stream) = 0;
	void blockInput() {
		inputFile("/dev/null");
	}
	void blockOutput() {
		outputFile("/dev/null", false);
	}
	
	void write(const std::string & output) {
		setInput(std::unique_ptr<InputStream>(new WriteStream(output)));
	}
	
	char inputFile(const std::string & filename) {
		char accessError = checkAccess(filename, 0);
		if(accessError) return accessError;
		setInput(std::unique_ptr<InputStream>(new FileInputStream(filename)));
	}
	char outputFile(const std::string & filename, bool append) {
		char accessError = checkAccess(filename, 1 + append);
		if(accessError) return accessError;
		setOutput(std::unique_ptr<OutputStream>(new FileOutputStream(filename, append)));
	}
	
	std::unique_ptr<PipeOutputStream> regularInput() {
		StreamConnector pair;
		setInput(pair.getInput());
		return std::unique_ptr<PipeOutputStream>((PipeOutputStream *)pair.getOutput().get());

	}
	
	std::unique_ptr<PipeInputStream> regularOutput() {
		StreamConnector pair;
		setOutput(pair.getOutput());
		return std::unique_ptr<PipeInputStream>((PipeInputStream *)pair.getInput().get());
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
	
	std::string getName() {
		return name;
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

	char check(const std::string & path);
	
	private:
	
	std::vector<char *> prepare_exec();
   
   public:
   
   char spawn();
	
	int join();
	
};
	
	
	

class Pipeline : public Routine {
	
	std::list<std::unique_ptr<Process>> processes;
	
	public:
	
	void setProcesses(std::list<std::unique_ptr<Process>> & process_list) {
		processes = std::move(process_list);
	}
	
	void addProcess(std::unique_ptr<Process> process) {
		processes.push_back(std::move(process));
	}
	
	//minimalna długość pipelin'u to 2 procesy i o to trzeba zadbać gdzieś indziej
	void setInput(std::unique_ptr<InputStream> stream) {
		(*processes.begin())->setInput(std::move(stream));
	}
	
	void setOutput(std::unique_ptr<OutputStream> stream) {
		auto end = processes.end();
		end--;
		(*end)->setOutput(std::move(stream));
	}
	
	char spawn();
	
	int join();
	
	char check(const std::string & path);
	
};
	
	
		 
