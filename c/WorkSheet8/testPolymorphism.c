#include "Polymorphism.h" 
#include <stdio.h> /* printf */

int main()
{
	static data_s_t elements[3];
	int i_int = 12;
	float f_float = 13.4;
	char *s_string = "ruslan";
	int i_to_add = 10;

	
	SetVal(&elements[0], INT, &i_int);
	SetVal(&elements[1], FLOAT, &f_float);
	SetVal(&elements[2], STRING, s_string);
	
	PrintVal(&elements[0]);
	PrintVal(&elements[1]);
	PrintVal(&elements[2]);

	AddVal(&elements[0], i_to_add);
	AddVal(&elements[1], i_to_add);
	/*AddVal(&elements[2], i_to_add);*/

	printf("\n %d \n", *(int *)GetVal(&elements[0]));
	printf("\n %f \n", *(float *)GetVal(&elements[1]));
	printf("\n %s \n", (char *)GetVal(&elements[2]));	

	return 0;

}
