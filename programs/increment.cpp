#include <cstdio>


int main(int count, char * args[]) {
	
	int i;
	int j = scanf("%d", &i);
	
	fprintf(stderr, "Odebrano taką liczbę: %d\n", i);
	fprintf(stderr, "Liczba argumentów: %d\n", count);
	
	if(count > 2) fprintf(stderr, "%s\n", args[2]);
	fprintf(stderr, "nazwa: %s\n", args[0]);

	printf("%d\n", i + 1);
	return 0;
	
}
