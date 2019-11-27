#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>		/*size_t*/

typedef struct heap heap_t;

typedef int (*is_before_t)(const void *data1, const void *data2, void *param);
typedef int(*is_match_t)(const void *data, void *param);

/********************** API **********************************/

heap_t *HEAPCreate(is_before_t func, void *param);

int HEAPPush(heap_t *heap, const void *data);

void HEAPPop(heap_t *heap);

void *HEAPPeek(heap_t *heap);

size_t HEAPSize(const heap_t *heap);

int HEAPIsEmpty(const heap_t *heap);

void HEAPDestroy(heap_t *heap);

void *HEAPFind(heap_t *heap, is_match_t func, void *key);

void HEAPErase(heap_t *heap, is_match_t func, void *key);


#endif /* __HEAP_H__ */