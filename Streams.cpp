#include "Streams.hpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

char WriteStream::child() {
	int fd[2];
	pipe(fd);
	dup2(fd[0], 0);
	close(fd[0]);
	
	write(fd[1], output.c_str(), output.size() + 1);
	close(fd[1]);
	return 1;
}


char PipeInputStream::child() {
	dup2(fd, 0);
	close(fd);
	return 1;
}


char PipeOutputStream::child() {
	dup2(fd, 1);
	close(fd);
	return 1;
}

char FileInputStream::child() {
	int fd = open(filename.c_str(), O_RDONLY);
	if(fd == -1) return 0;
	dup2(fd, 0);
	close(fd);
	return 1;
}



char FileOutputStream::child() {
	int fd = open(filename.c_str(), O_WRONLY | O_CREAT | append * O_APPEND, 0664);
	//trzeba będzie pomyśleć o truncat'ach
	if(fd == -1) return 0;
	dup2(fd, 1);
	close(fd);
	return 1;
}
