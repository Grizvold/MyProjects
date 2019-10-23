/* Clib */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Header files */
#include "single_ll.h"

void TestSLLFindInterSection();
void PrintList(sll_node_t *head);
int IntAddToData(void *data, void *param);
int IntFindNum(const void *data, void *param);
void PrintMsg(const char *msg);

/* driver program */
int main (void)
{
    sll_node_t *head = NULL;
    sll_node_t *current = NULL;
    sll_node_t *testnode = NULL;

    int i = 0;
    int x = 10;
    int arr[] = {0,1,2,3,4,5};
    int param = 11;
    
    PrintMsg("Create List");

    /* initialize list with array values */
    for (i = 0; i <(int)(sizeof(arr)/sizeof(arr[0])); i++)
    {
        if (NULL != head)
        {
            current->next = SLLCreateNode((void *)&arr[i],NULL);
            current = current->next;
        }
        else
        {
            head = SLLCreateNode((void *)&arr[i],NULL);
            current = head;
        }
    }
    
    /* print list */
    PrintList(head);
    printf("Count list :%lu\n",SLLCount(head));

    /* add num to each node */
    PrintMsg("Add num for each node");
    SLLForEach(head,IntAddToData,&x);
    PrintList(head);

    /* find param number */
    PrintMsg("Find Second node and print the list from this node");
    testnode = SLLFind(head,IntFindNum,&param);
    PrintList(testnode);
    
    /* insert node in the 4th position */
    PrintMsg("Insert After Third position");
    current = head;
    testnode = SLLCreateNode((void *)&x,NULL);
    for (i = 0; i < 3; i++)
    {
        current = current->next;
    }
    current = SLLInsertAfter(current,testnode);
    PrintList(head);
    printf("data in the 4th node: %d\n",*(int *)current->data);

    /* remove insert node from before */
    PrintMsg("Remove last inserted node");
    current = head;
    for (i = 0; i < 3; i++)
    {
        current = current->next;
    }
    current = SLLRemoveAfter(current);
    printf("Data in the node after: %d\n",*(int *)current->data);
    PrintList(head);

    PrintMsg("Test flip");
    head = SLLFlip(head);
    PrintList(head);

    PrintMsg("Test has loop");
    current = head;
    while (NULL != current->next)
    {
        current = current->next;
    }

    testnode = head;
    for (i = 0; i < 2; i++)
    {
        testnode = testnode->next;
    }

    current->next = testnode;
    printf("Has Loop : %d\n",SLLHasLoop(head));
    current->next = NULL;
    PrintList(head);
    
    PrintMsg("Test Find Intersection");
    TestSLLFindInterSection();

    /* free all nodes */
    SLLFreeAll(head);
    
    return 0;
}

void PrintList(sll_node_t *head)
{
    sll_node_t *current = NULL;

    for(current = head; current != NULL && NULL !=current->data; current = current->next)
    {
        printf("%d ",*(int *)current->data);
    }
    printf("%s","\n");
}

void PrintMsg(const char *msg)
{
    char *hyphen = "...............";
    printf("\n%-16s%s%16s\n",hyphen,msg,hyphen);
}

void TestSLLFindInterSection()
{
    sll_node_t *new_node;
    sll_node_t *head1 = SLLCreateNode(NULL,NULL);
    sll_node_t *head2 = SLLCreateNode(NULL,NULL);

    static int arr[] = {0,10,20,30,40,50,60,70,80,90};

    head1->data = &arr[0];
    head2->data = &arr[1];
    
    new_node = SLLCreateNode(&arr[2],NULL);
    head1->next = new_node;

    new_node = SLLCreateNode(&arr[3],NULL);
    head2->next = new_node;

    new_node = SLLCreateNode(&arr[4],NULL);
    head1->next->next = new_node;

    new_node = SLLCreateNode(&arr[8],NULL);
    head1->next->next->next = new_node;
    head2->next->next = new_node;


    new_node = SLLCreateNode(&arr[6],NULL);
    head1->next->next->next->next = new_node;
   
    puts("list1");
    PrintList(head1);
    puts("list2");
    PrintList(head2);
    new_node = SLLFindIntersection(head2,head1);
    
    printf("intersection data value: %d\n",*(int *)new_node->data);

    SLLFreeAll(head1);
    free(head2->next);
    free(head2);
}

int IntAddToData(void *data,void *param)
{
    *(int *)data += *(int *)param;

    return 0;
}

int IntFindNum(const void *data, void *param)
{
    if (*(int *)data == *(int *)param)
    {
        return 0; 
    }
    
    return -1;
}
