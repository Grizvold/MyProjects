#include <stdio.h>

void SetEcho()
{
    size_t i = 0;
    size_t *ptr = __builtin_frame_address(0);

    for(i = 0; i < 10; i++)
    {
        /* printf("\n %p \n", *(ptr + 1)); */
        printf("\n %p\n", (void *)*(ptr + i));
    }

    *(ptr + 1) = 0x400acb;
}