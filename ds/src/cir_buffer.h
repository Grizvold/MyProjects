#ifndef __CIR_BUFFER__
#define __CIR_BUFFER__

#include <stddef.h> /* size_t */

typedef struct cir_buffer cir_buffer_t;

/* 	*Create Circular_Buffer of fixed size "capacity".
   	*Return pointer to created  Circular_Buffer.			*/
cir_buffer_t *CBCreate(size_t capacity);

/* 	*Destroy Circular_Buffer, freeing allocated memory.	*/
void CDDestroy(cir_buffer_t *target_circ_buffer);

/* 	*Write num_bytes from "*data" to Circular_Buffer.
	*Return num_bytes written. 
	*Complexity O(n).								*/
size_t CBWrite(cir_buffer_t *target_circ_buffer, void *data, size_t num_bytes); 

/* 	*Read num_bytes from Circular_Buffer into "*data".
	*Return num_bytes read, 0 indicates end of file.
	*Complexity O(n).	 							*/
size_t CBRead(cir_buffer_t *target_circ_buffer, void *data, size_t num_bytes);

/* 	*Return capacity of Circular_Buffer.				*/
size_t CBCapacity(const cir_buffer_t *target_circ_buffer); 

/* 	*Return free space of Circular_Buffer.
	*Complexity O(1).								*/
size_t CBGetFreeSpace(const cir_buffer_t *target_circ_buffer);

/* 	*Boolean function to check if Circular_Buffer is 
		empty or not. 
	*Return 0 - empty
		   1	- not empty
	*Complexity O(1).								*/
int CBIsEmpty(const cir_buffer_t *target_circ_buffer);

#endif /* __CIR_BUFFER__ */
