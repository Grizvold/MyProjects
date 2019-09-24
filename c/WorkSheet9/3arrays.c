#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*calloc*/

void CmpArrays(char* arr1, char* arr2, char* arr3);

int main()
{
	char* str1= "abbaccd";
	char* str2= "abbefd";
	char* str3= "afg";
	
	CmpArrays(str1, str2, str3);
	
	return 0;	
}


void CmpArrays(char* arr1, char* arr2, char* arr3)
{
	int* arr_letters = NULL;
	size_t i = 0;
	
	arr_letters = (int*)calloc(26,sizeof(int));   /*array in the size of the ABC*/
	assert( NULL != arr_letters);
	
	for (i = 0; *(arr1+i) != '\0'; i++)
	{
		/* checking if it is the first time the letter appears*/
		if (arr_letters[*(arr1+i)-'a'] == 0)    
		{
			arr_letters[*(arr1+i)-'a'] +=1;
		}
	}
	
	for (i = 0; *(arr2+i) != '\0'; i++)
	{
		/* checking if it is the first time the letter appears in the secound array*/
		if (arr_letters[*(arr2+i)-'a'] == 1)  
		{
			arr_letters[*(arr2+i)-'a'] +=1;
		}
	}
	
	for (i = 0; *(arr3+i) != '\0'; i++)
	{
		arr_letters[*(arr3+i)-'a'] =0;
	}
	
	for (i = 0; i<26 ; i++)
	{
		if (arr_letters[i] >=2)
		{
			printf("%c ", (int)i+'a');
		}	
	}
	
	printf("\n");
	
	free(arr_letters);
	arr_letters = NULL;
	
}	 

