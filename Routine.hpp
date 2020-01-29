#pragma once
#include "Streams.hpp"
#include "Access.hpp"

#include <vector>
#include <list>

class Routine {
	public:
	virtual char spawn() = 0;
	virtual std::pair<std::string, int> join() = 0;
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

class Process: public Routine {
	protected:
	std::string name;
	public:
	
	Process() {
	}
	
	Process(const std::string & name): name(name) {
	}
	
	void setName(const std::string & name) {
		this->name = name;
	}
	
	std::string getName() {
		return name;
	}
	
	virtual std::string read() = 0;
	virtual void write(const std::string & content) = 0;
	virtual void realiseInput() = 0;
	virtual void realiseOutput() = 0;
	virtual char check(const std::string & path) = 0;
	
	
};

class RealProcess : public Process {
	
	pid_t id;
	std::vector<std::string> args;
	std::unique_ptr<InputStream> input;
	std::unique_ptr<OutputStream> output;
	
	public:
	
	RealProcess(): id(-1) {}
	RealProcess(const std::string & name): Process(name), id(-1) {
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
	
	std::pair<std::string, int> join();
	
	std::string read() {
		return std::string("");
	}
	
	void write(const std::string & content) {
	}
	
	void realiseInput() {
	}
	
	void realiseOutput() {
	}
	
};

class EmbeddedProcess: Process {
	
	EmbeddedProcess(): vidmo(false) {
	}
	
	EmbeddedProcess(const std::string & name): Process(name), vidmo(false) {
	}
	
	std::unique_ptr<PipeOutputStream> toPipeline;
	std::unique_ptr<PipeInputStream> fromPipeline;
	std::string message;
	bool vidmo;
	
	public:
	
	void setOutput(std::unique_ptr<OutputStream> stream) {
		toPipeline = PipeOutputStream::toPipe(stream);
	}
	
	void setInput(std::unique_ptr<InputStream> stream) {
		fromPipeline = PipeInputStream::toPipe(stream);
	}
	
	void realiseInput() {
		if(fromPipeline)
		fromPipeline->readMessage(message);
	}
	
	void realiseOutput() {
		if(toPipeline)
		toPipeline->writeMessage(message);
	}
	
	std::string read() {
		return message;
	}
	
	void write(const std::string & content) {
		message = content;
	}
	
	char spawn() {
		return 1;
	}
	
	static std::unique_ptr<Process> makeMessage(const std::string & message) {
		EmbeddedProcess * proc = new EmbeddedProcess;
		proc->write(message);
		proc->vidmo = true;
		return std::unique_ptr<Process>(proc);
	}
	 
	static std::unique_ptr<Process> makeVidmo() {
		EmbeddedProcess * proc = new EmbeddedProcess;
		proc->vidmo = true;
		return std::unique_ptr<Process>(proc);
	}
	
	std::pair<std::string, int> join() {
		return std::make_pair<std::string, int>(std::string(message), 0);
	}
	
	virtual char check(const std::string & path) {
		return 0;
	}

};
		
	
	
	
	


	
	
		 
