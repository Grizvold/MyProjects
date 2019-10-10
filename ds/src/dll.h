#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h> /* size_t */

/*########################### typedefs ###########################*/

/* typedef of node */
typedef struct dll_node dll_node_t;

/* typedef of list */
typedef struct dll_list dll_t;


/* typedef of iterator to dll */
typedef struct dll_iter
{
	dll_note_t *current;
	dll_t *cur_list;	
}dll_iter_t;

/* 	typedef of action function for ForEach function	*/
typedef int (*dll_act_func_t)(void *data, void *param);

/* 	typedef of action function for Find function		*/
typedef int (*dll_cmp_func_t)(void *data, void *param);
/*################################################################*/

/*####################### DLL Funtionality #######################*/

/* *Create new doubly linked list
   *Return pointer to new created list	*/
dll_t *DLLCreate();

/* *Free desired doubly linked list	*/
void DLLDestroy(dll_t *target_dll);

/* *Insert new element in dll
   *Return  iterator to next item in case of success
    Return EndIterator in case of failure
    	refering to <past-the-end> element in vector container			
   *Complexity O(1)										*/
dll_iter_t DLLInsert(dll_iter_t dll_iterator, const void *data);

/* *Remove element from dll
   *Return  iterator to next item in case of success
    Return EndIterator in case of failure
     refering to <past-the-end> element in vector container			
   *Complexity O(1)										*/    
dll_iter_t DLLRemove(dll_iter_t dll_iterator);

/* *Push new element at the start of dll
   *Return iterator to the new element
    In case of failure return EndIterator
    	refering to <past-the-end> element in vector container			
   *Complexity O(1)										*/
dll_iter_t DLLPushFront(dll_iter_t dll_iterator, const void *data);

/* *Pop first element of the dll
   *Returns data of the first element				
   *Complexity O(1)										*/
void *DLLPopFront(dll_iter_t dll_iterator);

/* *Push new element at the end of dll
   *Return iterator to the new element
    In case of failure return EndIterator
    	refering to <past-the-end> element in vector container	
   *Complexity O(1)										*/
dll_iter_t DLLPushBack(dll_iter_t dll_iterator, const void *data);

/* *Pop last element of the dll
   *Returns data of the last element
   *Complexity O(1)										*/
void *DLLPopBack(dll_iter_t dll_iterator);

/* *Find element in targeted dll
   *Return iterator to element in case of success
    Return EndIterator in case of failure	
    	refering to <past-the-end> element in vector container	
   *Complexity O(n)										*/
dll_iter_t DLLFind(dll_iter_t start, dll_iter_t end, dll_cmp_func_t cmp_func, void *param);

/* *Perform action on each element of the dll
   *Return status of performed action
    0 - Success
    1 - Failure	
   *Complexity O(n)										*/
int DLLForEach(dll_iter_t start, dll_iter_t end, dll_act_func_t act_func, void *param);

/* *Insert source dll size from-to into dest dll
   *Return iterator "where"
   *In case of failure return iterator of EndIterator
	refering to <past-the-end> element in vector container		*/
dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t from, dll_iter_t to);

/* *Return number of elements in targeted dll			
   *Complexity O(n)										*/
size_t DLLSize(const dll_t *target_list);
/*################################################################*/

/*####################### DLL Iterator Functionality #######################*/
/* *Receives targeted dll list
   *Returns first element of dll				*/
dll_iter_t DLLBegin(const dll_t *list);

/* *Receives targeted dll list
   *Returns iterator refering to 
   	<past-the-end> element in vector container	*/
dll_iter_t DLLEnd(const dll_t *list);

/* *Receives current iterator of targeted dll	
   *Returns next iterator
   *If used on EndIterator, returns EndIterator
   	refering to <past-the-end> element 
	in vector container						*/
dll_iter_t DLLIterNext(dll_iter_t cur_iter);

/* *Receives current iterator of targeted dll	
   *Returns previous iterator
   *If used on StartIterator, returns EndIterator
   	refering to <past-the-end> element 
	in vector container						*/
dll_iter_t DLLIterPrev(dll_iter_t cur_iter);

/* *Compare 2 iterators
   *Returns 1 if equal
    		  0 if not equal					*/
int DLLIterIsEqual(dll_iter_t iter_1, dll_iter_t iter_2);

/* *Receives requested iterator
   *Returns data of requested iterator			*/
void *DLLIterGetData(dll_iter cur_iter);
/*##########################################################################*/

#endif /*__DLL_H__*/


