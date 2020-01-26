#include "Routine.cpp"
#include "Streams.cpp"
#include "Access.cpp"

int main() {
	Process i("tested");
	
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
