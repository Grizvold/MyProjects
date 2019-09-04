#include <stdio.h>
#include <string.h>

char *Strcat(char *s1, char *s2)
{
	char buffer[100];
	sprintf(buffer, "%s%s", s1, s2);
	return (buffer);
}

int main()
{
	char str1[] = "Almog";
	char str2[] = "Ruslan";
	
	printf("\n after func: %s \n", Strcat(str1, str2));
	

	unsigned int *ip = 0;

	float f = 3;

	printf("\n add of f %p  \n add of ip %p \n add that ip points to %p\n", &f, &ip, ip);
	float *fp = &f;

	printf("\n HASAMA \n add of fp %p \n add of f %p \n", fp, &f);

	ip = (unsigned int *)fp;

	ip = fp;

	printf("\n CASTiNG  add of ip%p, \n", ip);
	printf("%u\n", *ip);


	return 0;
}
