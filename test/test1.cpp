#include "Routine.cpp"
#include "Streams.cpp"
#include "Access.cpp"
#include <iostream>

int main() {
	Process i("tested");
	
	char k = i.check();
	std::cout << "Udało się?" << (int)k << std::endl;
	
	i.addArg("takis");
	i.addArg("niejaki");
	
	i.inputFile("source");
	i.outputFile("destiny", false);
	
	char effect = i.spawn();
	if(effect == 0) {
		fprintf(stderr, "Wystąpił błąd\n");
		exit(1);
	}
	if(effect == -1) fprintf(stderr, "Wystąpił błąd w potomku\n");

	i.join();
}
