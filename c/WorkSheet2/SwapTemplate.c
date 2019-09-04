#include <stdio.h> /* prifntf */

#define const_int_ptr  const int*
#define int_ptr int*
#define SWAP_DEF(T) 		\
void Swap_##T(T* aptr, T* bptr)	\
{				\
	T temp = *aptr;		\
	*aptr = *bptr;		\
	*bptr = temp;		\
}				\

SWAP_DEF(int_ptr)

SWAP_DEF(int)

int main()
{
	int x = 1, y = 2;
	int *s = &x;
	int *t = &y;
	printf("\n first var %d second var %d\n", x, y);
	Swap_int(&x, &y);
	printf("\n first var %d second var %d\n", x, y);
		
	printf("\n first var %p second var %p\n", (void*)s, (void*)t);	
	printf("\n first var %d second var %d\n", *s, *t);
	Swap_int_ptr(&s, &t);
	printf("\n first var %p second var %p\n", (void*)s, (void*)t);
	return 0;
}
