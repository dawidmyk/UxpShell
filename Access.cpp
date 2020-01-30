#include "Access.hpp"
#include <unistd.h>
#include <errno.h>
#include <string.h>
std::pair<std::string, char> checkExecAccess(const std::string & filename, const std::string & path) {
	if(filename.empty()) return std::pair<std::string, char>(std::string(""), -1);
	if(filename.find('/') != std::string::npos)
	{
		return std::pair<std::string, char>(filename, checkAccess(filename, 3));
	}
	char * dup = strdup(path.c_str());
	char * rest = dup;
	char * result;
	char globalCond = 1;
	while((result = strtok_r(rest, ":", &rest)) != nullptr) {
		std::string str_result(result);
		str_result += "/" + filename;
		char cond = checkAccess(str_result, 3);
		if(cond == 0) {
			//można tam też dodać 2
			free(dup);
			return std::pair<std::string, char>(str_result, cond);
		}
		if(cond == 2) globalCond = 2;
	}
	free(dup);
	return std::pair<std::string, char>(std::string(""), globalCond);
}
	
		
		//chyba nie trzeba zdejmować




char checkAccess(const std::string & filename, char dir) {
	if(filename.empty()) return -1;
	//dir:
	//0 - read
	//1 - write
	//2 - append
	//3 - execute
	int flag;
	switch(dir) {
		case 0: flag = R_OK; break;
		case 1: flag = W_OK; break;
		case 2: flag = W_OK; break;
		//tutaj to nie ma różnicy ale mogłoby mieć
		case 3: flag = X_OK; break;
		default: return -1;
	}
	int result = access(filename.c_str(), flag);
	if(result == -1) {
		if(errno == EACCES) return 2;
		if(errno == ENOENT) {
			if((dir) == 1) return 0; 
			return 1;
		}
	}
	return 0; 
}
