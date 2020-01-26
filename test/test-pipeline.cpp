#include "Routine.cpp"
#include "Streams.cpp"
#include "Access.cpp"
#include <iostream>

int main() {
	Pipeline i;
	
	i.addProcess(std::unique_ptr<Process>(new Process("./tested")));
	i.addProcess(std::unique_ptr<Process>(new Process("./teste")));
	i.addProcess(std::unique_ptr<Process>(new Process("./tested")));
	i.addProcess(std::unique_ptr<Process>(new Process("./tested")));
	
	
	i.inputFile("source");
	i.outputFile("destiny", false);
	
	char effect = i.check();
	std::cout << "Udało się?" << (int)effect << std::endl;
	
	effect = i.spawn();
	if(effect == 0) {
		fprintf(stderr, "Wystąpił błąd\n");
		exit(1);
	}
	//To się narazie nie wydarzy:
	if(effect == -1) {
		fprintf(stderr, "Wystąpił błąd w potomku\n");
		exit(2); //to jest wyjście z potomka
	}

	//poniższe nie będzie pozwolone

	i.join();
}
