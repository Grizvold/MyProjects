#include "queue.h"

struct dll_queue{
	dll_node_t *start;
	dll_node_t *end;
	size_t dll_counter;
};

typedef struct{
	void *data;
	dll_node_t *next;
	dll_node_t *previous;
}dll_node_t;


