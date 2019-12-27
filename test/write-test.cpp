#include "Routine.cpp"
#include "Streams.cpp"
#include "echo.cpp"

int main() {
	Process i("./tested");
	
	echo("34\n", &i);
	
	char effect = i.spawn();
	if(effect == 0) {
		fprintf(stderr, "Wystąpił błąd\n");
		exit(1);
	}
	if(effect == -1) fprintf(stderr, "Wystąpił błąd w potomku\n");

	i.join();
}
