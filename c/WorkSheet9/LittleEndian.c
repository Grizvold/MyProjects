#include <stdio.h>
#define endian (*(&"1")) ? "little" : "big"

int main()
{
	int x = 1;
	char *c = (char*) &x;
	
	printf("%s\n", endian);
	
	if (*c == 1)
		printf("Little\n");
	else 
		printf("big\n");
	return 0;
	
}

