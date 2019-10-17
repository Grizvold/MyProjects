#ifndef __CIR_BUFFER__
#define __CIR_BUFFER__

#include <stddef.h> /* size_t */

typedef struct cir_buffer cir_buffer_t;

/* 	*Create Circular_Buffer of fixed size <capacity>.
   	*Return pointer to created circ_buffer.				*/
cir_buffer_t *CBCreate(size_t capacity);

/* 	*Destroy Circular_Buffer, freeing allocated memory.	*/
void CBDestroy(cir_buffer_t *circ_buffer);

/* 	*Write num_bytes from data to circ_buffer. If the 
		buffer is full, override starting from head.
	*Return num_bytes written. 
	*Complexity O(n).								*/
size_t CBWrite(cir_buffer_t *circ_buffer, void *data, size_t num_bytes); 

/* 	*Read num_bytes from circ_buffer into data.
	*Return num_bytes read, 0 indicates empty buffer.
	*Complexity O(n).	 							*/
size_t CBRead(cir_buffer_t *circ_buffer, void *buffer, size_t num_bytes);

/* 	*Return capacity of circ_buffer.					*/
size_t CBCapacity(const cir_buffer_t *circ_buffer); 

/* 	*Return free space of circ_buffer.
	*Complexity O(1).								*/
size_t CBGetFreeSpace(const cir_buffer_t *circ_buffer);

/* 	*Boolean function to check if circ_buffer is 
		empty or not. 
	*Return 1 - empty
		   0	- not empty
	*Complexity O(1).								*/
int CBIsEmpty(const cir_buffer_t *circ_buffer);

#endif /* __CIR_BUFFER__ */
