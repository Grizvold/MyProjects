#include <stdio.h> /* printf */
#include <stdlib.h> /* atoi(string argument to int) */ 

#define ARR_SIZE  100

int JosephusArray(int *, size_t);
int JosephusRecursive(int , int ); 
size_t GetNextPosition(int *, size_t, size_t);
void InitializeArrayForFreeList(int *, int);
int JosephusUsingFreeList(int *);

/* getting next position in our array */
size_t GetNextPosition(int *arr, size_t position, size_t size_arr)
{
	while(arr[position] || position == size_arr)
	{
		if(position == size_arr)
		{
			position = 0;
		}
		else
		{
			position++;
		}
	}
	
	return position;
}

/* Solving Josephus problem using array */
int JosephusArray(int *arr, size_t arr_size)
{
	size_t amount_of_dead = 0, position_in_array = 0;
	int is_dead = 0;
 	
	/* run on array <stdlib.h> / untill 1 person left "alive" 	*/
	/* 1 - dead, 0 - alive				*/
	while(amount_of_dead < arr_size) 
	{
		/* if 1 - dead -> then move to next position and  */
		/* reset is_dead to 0				  */
		if(is_dead)
		{
			position_in_array = GetNextPosition(arr, position_in_array + 1, arr_size);
			is_dead = !is_dead;	
		}
		/* if 0 - means alive, go to next cell "kill" him */
		/* and raise amout of dead people by 1		  */
		else
		{
			position_in_array = GetNextPosition(arr, position_in_array + 1, arr_size);
			arr[position_in_array] = 1;
			is_dead = !is_dead;
			amount_of_dead++;
		}
	}

	return position_in_array + 1;
}

/* Josephus recursive solution of algorithm  */ 
int JosephusRecursive(int n, int k) 
{ 
  if (n == 1) 
    return 1; 
  else
    /* The position returned by josephus(n - 1, k) is adjusted because the 
       recursive call josephus(n - 1, k) considers the original position  
       k%n + 1 as position 1 */
    return (JosephusRecursive(n - 1, k) + k-1) % n + 1; 
} 

/* Initialize array so the last cell [n-1] = 0, [0] = 1, [1] = 2 and so on */ 
void InitializeArrayForFreeList(int *soldr_arr, int num_of_soldr)
{
	int i = 0;
	for(; i < num_of_soldr - 1; ++i)
	{
		soldr_arr[i] = i + 1;
	}
	
  	/* put 0 in last cell */
	soldr_arr[num_of_soldr - 1] = 0;
}


int JosephusUsingFreeList(int *soldr_array)
{
	int  i = 0;
	/* if value inside arr == index => this is the last	*/
	/* soldier left alive	(laststanding)			*/
	while(i != soldr_array[i])
	{
		soldr_array[i] = soldr_array[soldr_array[i]];
		i = soldr_array[i];
	}
	
	return i + 1;
}


int main(int argc, char **argv) 
{ 
  /* var for recursive Joseph */
  int n = 100; 
  int k = 2; 
  /* arr for "long version" of Joseph */
  int arr_joseph[ARR_SIZE] = {0};
  /* var for "free list" Joseph */
  int num_of_soldiers = 0;
  int *soldiers_arr = NULL;

  /* check for user input of number of soldiers */	
  if(argc == 2)
  {
	num_of_soldiers = atoi(argv[1]);
  	soldiers_arr = (int *)calloc(num_of_soldiers, sizeof(int));
	/* initializing array so the value of last cell [n-1] = 0, and [0] = 1, [1] = 2 and so on... */
 	InitializeArrayForFreeList(soldiers_arr, num_of_soldiers);
	printf("%*c    The position of soldier left alive is: %d if amount of soldiers is: %d\n", 5, ' ', JosephusUsingFreeList(soldiers_arr)
													, num_of_soldiers);
  }
  else
  {
  	printf("%*c    No input from command line, or wrong input\n", 5, ' ');
  }
  
  /* result of Josephus problem using array */ 
  	printf("%*c    The position of soldier left alive is: %d if amount of soldiers is: %d\n", 5, ' ', JosephusArray(arr_joseph, ARR_SIZE)
													, ARR_SIZE);

  
  /* Recursive Josephus */
  	printf("%*c    The position of soldier left alive is: %d if amount of soldiers is: %d\n", 5, ' ', JosephusRecursive(n, k), n);
  
  return 0; 
} 

