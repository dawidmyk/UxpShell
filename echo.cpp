#include "Routine.hpp"
#include <iostream>
void echo(const std::string & output, Routine * routine) {
	if(routine == nullptr) std::cout << output;
	else routine->write(output);
}
