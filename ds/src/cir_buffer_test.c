#include <stdio.h> 	/* 	printf	*/

#include "cir_buffer.h"

void PrintMsg(const char *msg);
void PrintIsEmpty(cir_buffer_t *cbuf);
void PrintCapacity(cir_buffer_t *cbuf);
void PrintFreeSpace(cir_buffer_t *cbuf);

int main(void)
{
    cir_buffer_t *cbuf = NULL;
    cir_buffer_t *ibuf = NULL; 

    /* array for char test */
    char csrc [] = {'a','b','c','d','e','f','g'} ;
    char cbuffer[20] = {0};

    /* array for integer test */ 
    int isrc[] = {0,1,2,3,4,5};
    int ibuffer[20] = {0};
    
    int i = 0;
    size_t tmp = 0;

    /*////////// TEST CHARS \\\\\\\\\\\\*/
    
    PrintMsg("TEST FOR CHARS\n");
    PrintMsg("Create circular buffer for chars");

    /* #1 Create a new circular buffer */
    cbuf = CBCreate(4);
    
    /* print capacity, IsEmpty, and freespace */
    PrintCapacity(cbuf);
    PrintIsEmpty(cbuf);
    PrintFreeSpace(cbuf);

    /* #4 check write */
    tmp = CBWrite(cbuf, csrc, 6);
    
    /* #8 number of bytes write */
    printf("Number of bytes write: %lu\n",tmp);

    /* #6 Print FreeSpace */
    PrintFreeSpace(cbuf);
    
    PrintMsg("Trying to read 5 bytes");
    tmp = CBRead(cbuf,cbuffer,5);
    printf("Number of bytes read: %lu\n",tmp);
    
    /* #2 check if empty */
    PrintIsEmpty(cbuf);

    /* #6 Print FreeSpace */
    PrintFreeSpace(cbuf);

    /* #9 printf buffer */
    printf("Buffer: %s\n",cbuffer);
    

    /*////////// TEST INT \\\\\\\\\\\\*/

    PrintMsg("TEST FOR INTEGERS");

    /* #1 Create a new circular buffer */
    ibuf = CBCreate(10 * sizeof(int));
    
    /* #2 check if empty */
    PrintIsEmpty(ibuf);
   
    /* #3 check capacity */
    PrintCapacity(ibuf);
    
    /* #4 check write */
    tmp = CBWrite(ibuf, isrc, 6 * sizeof(int));
    
    /* #5 printf number of bytes written */
    printf("Bytes written : %lu\n",tmp);

    /* #6 Check read store bytes in ibuffer */
    CBRead(ibuf,ibuffer,5 * sizeof(int));
    
    /* #7 printf buffer */
    for (i = 0; i < (int)(tmp = (sizeof(ibuffer)/sizeof(int))); i++)
    {
        printf("%d%s",ibuffer[i], (i < (int)tmp - 1) ? " " : "\n");
    }

    /* #9 Print FreeSpace */
    PrintFreeSpace(ibuf);

    /* free buffers */
    CBDestroy(cbuf);
    CBDestroy(ibuf);

    return 0;
}

void PrintMsg(const char *msg)
{
    char *hyphen = "-----";
    printf("%s%5s\n",hyphen,msg);
}

void PrintIsEmpty(cir_buffer_t *cbuf)
{
    int tmp = 0;
    tmp = CBIsEmpty(cbuf);
    PrintMsg("IsEmpty?");
    printf("%d\n",tmp);
}

void PrintCapacity(cir_buffer_t *cbuf)
{
    size_t tmp = 0;
    tmp = CBCapacity(cbuf);
    PrintMsg("Capacity:");
    printf("%lu\n",tmp);
}

void PrintFreeSpace(cir_buffer_t *cbuf)
{
    size_t tmp = 0;
    tmp = CBGetFreeSpace(cbuf);
    PrintMsg("Free Size:");
    printf("%lu\n",tmp);
}


