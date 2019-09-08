#include <stdio.h> /* printf */
 
#define ARR_SIZE  100

int JosephusArray(int *, size_t);
int JosephusRecursive(int , int ); 
size_t GetNextPosition(int *, size_t, size_t);

/*  */

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
  


int main(int argc, char **argv) 
{ 
  int n = 100; 
  int k = 2; 
  int arr_joseph[ARR_SIZE] = {0};
  char *num_from_string = 
  
  /* result of Josephus problem using array */ 
  printf("\nThe last standing is %d\n", JosephusArray(arr_joseph, ARR_SIZE));

  
  /* Recursive Josephus */
  printf("\nThe chosen place is %d\n", JosephusRecursive(n, k)); 
  
  return 0; 
} 

