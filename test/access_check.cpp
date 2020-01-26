#include "Access.cpp"
#include <iostream>

int main() {
	std::cout << std::string(getenv("PATH")) << std::endl;
	std::pair<std::string, char> score1 = checkExecAccess("gitkrake", std::string(getenv("PATH")));
	std::cout << score1.first << " - " <<(int)score1.second << std::endl;
	
	char score2 = checkAccess("destiny", 0);
	std::cout << (int)score2 << std::endl;

	return 0;
}
