#ifndef __single_ll_h__
#define __single_ll_h__

typedef int(*func_t)(node_t *);

typedef struct{
		void *data;
		node_t next_node*;
}node_t;

/* 	*Creates root for new linked list
	*Returns pointer to the root							*/
node *SLLCreateNode(void *data, node_t *next_node);

/*	*Remove all nodes from list including root
	*Complexcity O()									*/
void SLLFreeAll(node *node);

/* *Remove spesific node from our linked list, complexity O(1)	*/
void SLLRemove(node_t *node);


void SLLRemoveAfter(node_t *node);

/*  */
void SLLInsert(node_t *target, node_t *new_node, void *data);

void SLLInsertAfter(node_t *target, node_t *new_node, void *data);

size_t SLLCount(const node_t *list);

int SLLForEach(node_t *root_of_list, func_t *p_func);

node_t *SLLFind(node_t *root_of_list, func_t *p_func);

note_t *SLLFlip(node_t *root);

int SLLHasLoop(node_t *list);

note_t *SLLFindIntersection(node_t *first_list, node_t *second_node);

#endif /* __single_ll_h__ */


