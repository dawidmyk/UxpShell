#pragma once
#include <unistd.h>
#include <memory>

class AbstractStream {
	public:
	virtual char child() = 0;
	virtual void parent() = 0;
};

class InputStream : public AbstractStream {
};

class OutputStream : public AbstractStream {
};

class WriteStream : public InputStream {
	std::string output;
	
	public:
	WriteStream(const std::string & output): output(output) {}
	
	char child();
	
	void parent() {
	}
	
};

class PipeInputStream : public InputStream {
	
	int fd;
	
	public:
	
	PipeInputStream(int fd): fd(fd) {}
	
	char child();
	
	void parent() {
		close(fd);
	}
	
	void readChar(char & i) {
		read(fd, &i, 1);
	}
	
};

class PipeOutputStream : public OutputStream {
	
	int fd;
	
	public:
	
	PipeOutputStream(int fd): fd(fd) {}
	
	char child();
	
	void parent() {
		close(fd);
	}
	
	void writeChar(char i) {
		write(fd, &i, 1);
	}
	
};

class FileInputStream : public InputStream {
	 std::string filename;
	
	 public:
	 
	 FileInputStream(const std::string & filename): filename(filename) {}
	 
	 char child();
	 
	 void parent() {
	 }
	 
}; 

class FileOutputStream : public OutputStream {
	 std::string filename;
	 bool append;
	
	 public:
	 
	 FileOutputStream(const std::string & filename, bool append): filename(filename), append(append) {}
	 
	 char child();
	 
	 void parent() {
	 }
	 
}; 

class StreamConnector {
	
	int fd[2];
	
	public:
	
	StreamConnector() {
		pipe(fd);
	}
	
	std::unique_ptr<InputStream> getInput() {
		return std::unique_ptr<InputStream>(new PipeInputStream(fd[0]));
	}
	
	std::unique_ptr<OutputStream> getOutput() {
		return std::unique_ptr<OutputStream>(new PipeOutputStream(fd[1]));
	}
	
};
