#pragma once
#include "Streams.hpp"
#include <vector>
#include "Access.cpp"

class Routine {
	public:
	virtual char spawn() = 0;
	virtual int join() = 0;
	virtual void setInput(std::unique_ptr<InputStream> stream) = 0;
	virtual void setOutput(std::unique_ptr<OutputStream> stream) = 0;
	
	void blockInput() {
		backupInput();
		inputFile("/dev/null");
	}
	void blockOutput() {
		backupOutput();
		outputFile("/dev/null", false);
	}

	void unblockInput() {
		setInput(restoreInput());
	}

	void unblockOutput() {
		setOutput(restoreOutput());
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

	virtual void sendToBackground();

	virtual void sendToForeground();

	virtual void backupInput();

	virtual void backupOutput();

	virtual std::unique_ptr<InputStream> restoreInput();

	virtual std::unique_ptr<OutputStream> restoreOutput();

	//background / foreground nie dodaje bo to działka kogoś innego
};

class Process : public Routine {
	
	pid_t id;
	std::string name;
	std::vector<std::string> args;
	std::unique_ptr<InputStream> cur_input, org_input;
	std::unique_ptr<OutputStream> cur_output, org_output;
	
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
		cur_input = std::move(stream);
	}
	
	void setOutput(std::unique_ptr<OutputStream> stream) {
		cur_output = std::move(stream);
	}

	std::unique_ptr<InputStream> restoreInput() {
		return std::move(org_input);
	}

	std::unique_ptr<OutputStream> restoreOutput() {
		return std::move(org_output);
	}
	
	void backupInput() {
		org_input = std::move(cur_input);	
	}

	void backupOutput() {
		org_output = std::move(cur_output);
	}


	void sendToBackground() override;

	void sendToForeground() override;

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

	std::unique_ptr<InputStream> restoreInput() {
		return processes.at(0)->restoreInput();
	}

	std::unique_ptr<OutputStream> restoreOutput() {
		return processes.at(processes.size() - 1)->restoreOutput();
	}
	
	char spawn();
	
	int join();
	
	void sendToBackground() override;

	void sendToForeground() override;
};

// struct job {
//     int id;
//     struct process *root;
//     char *command;
//     pid_t pgid;
//     int mode;
// };
// std::vector<std::string> args;
