#ifndef __SINGLE_LL_H__
#define __SINGLE_LL_H__

typedef int(*sll_func_t)(void *data, void *param);

typedef int(*sll_c_func_t)(const void *data, void *param);

typedef struct sll_node sll_node_t;

struct sll_node{
		void *data;
		sll_node_t *next;
};

/* 	*Creates root for new linked list
	*Returns pointer to the root							*/
node *SLLCreateNode(void *data, sll_node_t *next);

/*	*Remove all nodes from list including root
	*Complexcity O()									*/
void SLLFreeAll(sll_node_t *node);

/*	*Removes specified node from linked list, complexity O(1)	
	*Does not handle last node as an argument				*/
sll_node_t *SLLRemove(sll_node_t *target);

/*	*Removes node from linked list, after specified node		
	* complexity O(1)									*/
sll_node_t *SLLRemoveAfter(sll_node_t *target);

/*	*Links a new item at , re-links adjacent items
	*Returns pointer to the next node  					*/
sll_node_t *SLLInsert(sll_node_t *target, sll_node_t *new_node);

sll_node_t *SLLInsertAfter(sll_node_t *target, sll_node_t *new_node);

size_t SLLCount(const sll_node_t *root);

int SLLForEach(sll_node_t *root, const sll_func_t func);

sll_node_t *SLLFind(sll_node_t *root, sll_c_func_t func);

sll_node_t *SLLFlip(sll_node_t *root);

int SLLHasLoop(const sll_node_t *list);

note_t *SLLFindIntersection(const sll_node_t *first_list, const sll_node_t *second_node);

#endif /* __SINGLE_LL_H__ */


