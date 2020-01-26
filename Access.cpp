#include <unistd.h>
char checkAccess(const std::string & filename, char dir) {
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
		if(errno == EACCESS) return 2;
		if(errno == ENOENT) return 1;
	}
	return 0; 
}
