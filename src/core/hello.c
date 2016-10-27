#include <stdio.h>

int main()
{
	FILE *fout;
	fout = fopen("hello.txt", "w");
	printf("The test file is written by Wang Huan\n");
	fprintf(fout, "The test file is written by Wang Huan\n");
	fclose(fout);
	return 0;
}
