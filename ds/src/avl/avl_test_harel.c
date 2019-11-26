/*************************************
*    AVL(Functions)                   * 
*                                     *
* Dev: Yuval Shlomo                   *
* Rev: Matan Albilia                  *
* Date: 23.11.19                      *
* Status: Sent                        *
**************************************/

#include <stdio.h> /*printf*/

#include "avl.h" 

/*printf color macros*/ 
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"

int CreateDestroyTest();
int InsertForEachTest();
int SizeIsEmptyTest();
int FindTest();
int RemoveTest();
int HeightTest();
int LeftRotationTest();
int RightRotationTest();
int RemoveRotationTest();


static int IsIntBefore(const void *data1, const void *data2, void *param);
static int Add(void *data, void *param);
static int PrintInt(void *data, void *param);

/****************************************************/

int main()
{
  CreateDestroyTest();
  InsertForEachTest();
  SizeIsEmptyTest();
  FindTest();
  RemoveTest();
  HeightTest();

  LeftRotationTest();
  RightRotationTest();
  RemoveRotationTest();

  return 0;

}

/****************************************************/

int CreateDestroyTest()
{
    avl_t *avl = NULL;

    printf("\n%sAVLCreate and AVLDestroy Tests:\n",KYEL);
	printf("%s\n",KNRM);

    avl = AVLCreate(IsIntBefore, NULL);

    printf("Check Vlg.\n\n");

    AVLDestroy(avl);

    return 0;
}

/****************************************************/

int InsertForEachTest()
{
	int array[] = {-10,3,11,43,2,1,0,-2,14,22,76};
	size_t i = 0;
	size_t size = 11;
	int param = 10;

	avl_t *avl = AVLCreate(IsIntBefore, NULL);
	if(NULL == avl)
	{
		return 1;
	}
	printf("\n%sAVLInsert and AVLForEach Tests:\n",KYEL);
	printf("%s\n",KNRM);

	printf("Before insert:\n");
	for (i = 0; i < size; ++i)
	{
		PrintInt(&array[i], NULL);
	}

	for (i = 0; i < size; ++i)
	{
		AVLInsert(avl, &array[i]);
	}

	puts("\n\nAfter insert:");
	AVLForEach(avl, PrintInt, NULL);

	puts("\n\nAfter insert + 10:");
	AVLForEach(avl, Add, &param);
	AVLForEach(avl, PrintInt, NULL);

	puts("");

	AVLDestroy(avl);

	return 0;
}

/****************************************************/

int SizeIsEmptyTest()
{
	size_t i = 0;
	int array[] = {2,7,3,-5};

	avl_t *avl = AVLCreate(IsIntBefore, NULL);
	if(NULL == avl)
	{
		return 1;
	}

	printf("\n%sAVLSize and AVLIsEmpty Tests:\n",KYEL);
	printf("%s\n",KNRM);

	AVLIsEmpty(avl) == 1 ? puts("IsEmpty works (:") : puts("Error in IsEmpty!");
	AVLSize(avl) == 0 ?  puts("Size Works (:\n") : puts("Error in Size!");

	for (i = 0; i < 4; ++i)
	{
		AVLInsert(avl, &array[i]);
	}

	AVLIsEmpty(avl) == 0 ? puts("IsEmpty works (:") : puts("Error in IsEmpty!");
	AVLSize(avl) == 4 ?  puts("Size Works (:\n") : puts("Error in Size!");

	AVLDestroy(avl);

	return 0;
}
  
/****************************************************/

int FindTest()
{
	size_t i = 0;
	int array[] = {25,10,5,20,0,35,15,40,99};
	int *find = NULL;

	avl_t *avl = AVLCreate(IsIntBefore, NULL);
	if(NULL == avl)
	{
		return 1;
	}

	printf("\n%sAVLFind Test:\n",KYEL);
	printf("%s\n",KNRM);

	for (i = 0; i < 8; ++i)
	{
		AVLInsert(avl, &array[i]);
	}

	find = AVLFind(avl, &array[2]);
	*(int *)find == 5 ? puts("Find Works (:") : puts("Error in Find!");

	find = AVLFind(avl, &array[5]);
	*(int *)find == 35 ? puts("Find Works (:") : puts("Error in Find!");

	find = AVLFind(avl, &array[8]);
	find == NULL ? puts("Find Works (:\n") : puts("Error in Find!");

	AVLDestroy(avl);

	return 0;

	}

/****************************************************/

int RemoveTest()
{
	size_t i = 0;
	int array[] = {10, 20, 60, 50, 70, 40, 100, 30, 80, 90};

	avl_t *avl = AVLCreate(IsIntBefore, NULL);
	if(NULL == avl)
	{
		return 1;
	}

	printf("\n%sAVLRemove Test:\n",KYEL);
	printf("%s\n",KNRM);

	for (i = 0; i < 10; ++i)
	{
		AVLInsert(avl, &array[i]);
	}

	for (i = 0; i < 10; ++i)
	{
		AVLForEach(avl, PrintInt, NULL);
		puts("");
		AVLRemove(avl, &array[i]);
	}

	AVLIsEmpty(avl) == 1 ? puts("IsEmpty works (:") : puts("Error in IsEmpty!");

	AVLDestroy(avl);

	return 0;
}

int HeightTest()
{
	int arr[8] =    {5, 2, 8, 10, 1, 7, 6, 12};
	int result[8] = {4, 4, 3, 3, 2, 2, 2, 1};
	size_t i = 0;

	avl_t *avl = AVLCreate(IsIntBefore, NULL);
	if(NULL == avl)
	{
		return 1;
	}

	printf("\n%sAVLHight Test:\n",KYEL);
	printf("%s\n",KNRM);

	for (i = 0; i < 8; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	for (i = 0; i < 8; ++i)
	{
		AVLTreePrint(avl);
		AVLHeight(avl) != result[i] ? puts("Error in height!") : puts("Height Works (:");
   		printf("%ld\n",AVLHeight(avl));

		AVLRemove(avl, &arr[i]);
	}

	return 0;
}


/************************************************************/

static void LeftTest1();
static void LeftTest2();
static void LeftTest3();
static void LeftTest4();
static void LeftTest5();
static void LeftTest6();


int LeftRotationTest()
{
	printf("\n%sLeftRotate Test:\n",KYEL);
	printf("%s\n",KNRM);

	LeftTest1();
	LeftTest2();
	LeftTest3();
	LeftTest4();
	LeftTest5();
	LeftTest6();

	return 0;
}

static void LeftTest1()
{
	int arr[3] = {10, 8, 6};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 3; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 2 ? puts("Left Rotation Succes (:\n") : puts("Left Rotation Failure!\n");
	AVLDestroy(avl);
}

static void LeftTest2()
{
	int arr[6] = {10, 12, 7, 8, 6, 4};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 6; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 3 ? puts("Left Rotation Success (:\n") : puts("Left Rotation Failure!\n");
	AVLDestroy(avl);
}

static void LeftTest3()
{
	int arr[6] = {10, 12, 8, 13, 6, 5};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 6; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 3 ? puts("Left Rotation Success (:\n") : puts("Left Rotation Failure!\n");
	AVLDestroy(avl);
}

static void LeftTest4()
{
	int arr[8] = {10, 12, 8, 9, 6, 5, 7, 4};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 8; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 4 ? puts("Left Rotation Success (:\n") : puts("Left Rotation Failure!\n");
	AVLDestroy(avl);
}

static void LeftTest5()
{
	int arr[6] = {10, 12, 6, 5, 8, 9};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 6; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 3 ? puts("Left Rotation Success (:\n") : puts("Left Rotation Failure!\n");
	AVLDestroy(avl);
}

static void LeftTest6()
{
	int arr[9] = {20, 22, 10, 23, 12, 6, 5, 8, 9};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 9; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 4 ? puts("Left Rotation Success (:\n") : puts("Left Rotation Failure!\n");
	AVLDestroy(avl);
}

/************************************************************/

static void RightTest1();
static void RightTest2();
static void RightTest3();

int RightRotationTest()
{
	printf("\n%sRightRotate Test:\n",KYEL);
	printf("%s\n",KNRM);

	RightTest1();
	RightTest2();
	RightTest3();

	return 0;
}

static void RightTest1()
{
	int arr[3] = {10, 12, 15};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 3; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 2 ? puts("Right Rotation Success (:\n") : puts("Right Rotation Failure!\n");
	AVLDestroy(avl);
}

static void RightTest2()
{
	int arr[200] = {0};
	size_t i = 0;
	avl_t *avl = NULL;

	for(i = 0; i < 200; ++i)
	{
		arr[i] = i;
	}

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 200; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	AVLHeight(avl) == 8 ? puts("Right Rotation Success (:\n") : puts("Right Rotation Failure!\n");
	AVLDestroy(avl);
}

static void RightTest3()
{  
	int arr[6] = {10, 8, 15, 2, 20, 1};
	size_t i = 0;
	avl_t *avl = NULL;

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 6; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	AVLForEach(avl, PrintInt, NULL);
	AVLHeight(avl) == 3 ? puts("Right Rotation Success (:\n") : puts("Right Rotation Failure!\n");
	AVLDestroy(avl);
}

/**********************************************************************/

int RemoveRotationTest()
{
	int arr[7] = {10, 5, 15, 8, 20, 2, 1};
	size_t i = 0;
	avl_t *avl = NULL;

	printf("\n%sRemoveRotation Test:\n",KYEL);
	printf("%s\n",KNRM);

	avl = AVLCreate(IsIntBefore, NULL);

	for (i = 0; i < 7; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	AVLHeight(avl) == 4 ? puts("Remove Rotation Success (:\n") : puts("Remove Rotation Failure!\n");
	AVLRemove(avl, &arr[1]);
	AVLHeight(avl) == 3 ? puts("Remove Rotation Success (:\n") : puts("Remove Rotation Failure!\n");
	AVLDestroy(avl);

	return 0;
}


/****************************************************/

static int IsIntBefore(const void *data1, const void *data2, void *param)
{

	return (*(int *)data1 < *(int *)data2);
}

/****************************************************/

static int Add(void *data, void *param)
{
  *(int *)data += *(int *)param;

  return 0;
}

/****************************************************/

static int PrintInt(void *data, void *param)
{
  printf("%d  ",*(int *)data);

  return 0;
}

/****************************************************/

