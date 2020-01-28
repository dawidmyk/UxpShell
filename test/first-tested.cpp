#include <cstdio>
#include <unistd.h>
int main() {
	FILE * plik = fopen("Nowy plik", "w");
	sleep(10);
	char linia[10];
	fgets(linia, 10, stdin);
	fputs(linia, plik);
}
