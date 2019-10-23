#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h> /* size_t */

/* ################################ Typedefs ################################ */

/* managment struct of the doubly linked list 								  */
typedef struct dll dll_t;

/* struct of the nodes in the doubly linked list. 							  */
typedef struct dll_node dll_node_t;

/* struct of the iterator the doubly linked list. 							  */
typedef struct dll_iter dll_iter_t;

/*  Signature of the user-inserted action function to be used in <DLLForeach>.*/
typedef int (*dll_act_func_t)(void *data, void *param);

/*  Signature of the user-inserted compare function to be used in <DLLFind>.  */
typedef int (*dll_cmp_func_t)(const void *data, void *param);


/* ########################### Basic Functions ############################## */

/*  Creates a new doubly linked list. The list hold pointers to the data 
	provided by the user, but not the data istself.
	Return Value:
		pointer to the created doubly linked list.							  */
dll_t *DLLCreate();

/*  Frees the list and all the items it contains.
	WARNING:
		Any data stored in the list will be lost!							  */
void DLLDestroy(dll_t *dll);

/*  Inserts one item to the list, at the the position before the
	iterator <iter>.
	Return Value:
		iterator with the position of the inserted item.
		In case of failure, will return an iterator equal to DLLEnd(dll).	  */
dll_iter_t DLLInsert(dll_iter_t iter, void *data);

/*  Inserts one item to the back (i.e. tail) of the list.
	Return Value:
		iterator with the position of back of the list.		
		In case of failure, will return an iterator equal to DLLEnd(dll).	  */
dll_iter_t DLLPushBack(dll_t *dll, const void *data);

/*  Inserts one item to the front (i.e. head) of the list.
	Return Value:
		iterator with the position of the front of the list.		
		In case of failure, will return an iterator equal to DLLEnd(dll).	  */
dll_iter_t DLLPushFront(dll_t *dll, const void *data);

/*  Removes one item from the list, at the position of the iterator <iter>.
	Return Value:
		iterator with the position of the item located after the removed
		item.																  */
dll_iter_t DLLRemove(dll_iter_t iter); 

/*  Removes one item from  the back (i.e. tail) of the list.
	Return Value:
		Pointer to the data pointed by the removed item.					  */
void *DLLPopBack(dll_t *dll);

/*  Removes one item from the front (i.e. head) of the list.
	Return Value:
		Pointer to the data pointed by the removed item.					  */
void *DLLPopFront(dll_t *dll);

/*  Returns the number of items in the list.								  */
size_t DLLSize(const dll_t *dll);

/*  Checks wheter the list is empty or not.
	Return Value:
		1 if the list is empty, 0 if not empty.					 			  */
int DLLIsEmpty(const dll_t *dll);

/*  Returns an iterator with the position of front of the list.				  */
dll_iter_t DLLBegin(const dll_t *dll);

/*  Returns an iterator with the position of back of the list.				  */
dll_iter_t DLLEnd(const dll_t *dll);

/*  Moves all the items located between <iter_from> & <iter_to> (including)
	from their original list to the list of <iter_where>. The new position of
	the	items is before <iter_where>.
	Return Value:
		iterator with the new position of <iter_from>.
	Undefined behaviors:
		if the list of <iter_from> & <iter_to> is empty.
		if <iter_from> & <iter_to> are not on the same list.				  */
dll_iter_t DLLSplice(dll_iter_t iter_where, dll_iter_t iter_from,
					 dll_iter_t iter_to);


/* ########################## Utility Functions ############################# */

/*  Preform the user- function <dll_act_func_t> on each of the items in the 
	list, between <iter_from> & <iter_to> (including). The user-function 
	receives 1 argument (<param>), and must return status (0 for sucsses, !0 
	for failure). In case the user-function fails, no action will be preformed 
	on the remaining items of the list.
	Return Value:
		0 for sucsses, !0 for failure.										  */
int DLLForEach(dll_iter_t iter_from, dll_iter_t iter_to,
		   dll_act_func_t foreach_func, void *param);

/*  Finds the location of a value in the list, between <iter_from> & <iter_to> 
	(including), using the user-function <dll_cmp_func_t>. The user-function 
	receives 1 argument (<param>), and must return status (1 if  the value was 
	found, 0 if it wasn't).
	Return Value:
		iterator with the position of the item where the value is stored. If
		the value isn't found, returns DLLEnd().			 				  */
dll_iter_t DLLFind(dll_iter_t iter_from, dll_iter_t iter_to,
		dll_cmp_func_t cmp_func, void *param);


/* ########################## Iterator Functions ############################ */

/* Returns an iterator with the position of the next item of <iter>.		  */
dll_iter_t DLLIterNext(dll_iter_t iter);

/* Returns an iterator with the position of the previous item of <iter>.	  */
dll_iter_t DLLIterPrev(dll_iter_t iter);

/*  Checks whether the two iterators hold the same item/position in the list.
	Return Value:
		1 if the iterators are equal, 0 if they are not equal.				  */
int DLLIterIsEqual(dll_iter_t iter1, dll_iter_t iter2);

/* Returns a pointer to the data stored in the item at the position of <iter> */
void *DLLIterGetData(dll_iter_t iter);


/* ######################## Internal Use Defenitions ######################## */
/* DO NOT USE THIS!															  */
struct dll_iter
{
	dll_t *dll_list;
	dll_node_t *curr;
};


#endif /*__DLL_H__ */










