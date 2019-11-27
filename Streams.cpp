#include "Streams.hpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void WriteStream::child() {
	int fd[2];
	pipe(fd);
	dup2(fd[0], 0);
	close(fd[0]);
	
	write(fd[1], output.c_str(), output.size() + 1);
	close(fd[1]);
}


void PipeInputStream::child() {
	dup2(fd, 0);
	close(fd);
}


void PipeOutputStream::child() {
	dup2(fd, 1);
	close(fd);
}

void FileInputStream::child() {
	int fd = open(filename.c_str(), O_RDONLY);
	dup2(fd, 0);
	close(fd);
}



void FileOutputStream::child() {
	int fd = open(filename.c_str(), O_WRONLY);
	dup2(fd, 1);
	close(fd);
}
