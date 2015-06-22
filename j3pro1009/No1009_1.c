#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

int linear_search(int* array,int size,int key);

int main(void)
{
	int array[ARRAY_SIZE];
	int i;
	int key;
	int result;

	srand((unsigned)time(NULL));

	for(i=0;i<ARRAY_SIZE;i++)
	{
		array[i] = rand() % 100;
	}

	printf("array\n");
	printf("------------------------\n");
	for(i=0;i<ARRAY_SIZE;i++)
	{
		printf("array[%d] = %d\n",i,array[i]);
	}
	printf("------------------------\n");

	for(;;)
	{
		printf("Search Key>"); scanf("%d",&key);
		result = linear_search(array,ARRAY_SIZE,key);
		if(result==-1)
		{
			printf("Search Result>Not found:%d\n",key);
		}
		else
		{
			printf("Search Result>%d was found at %d\n",key,result);
		}
	}
}

int linear_search(int* array,int size,int key)
{
	int i;

	for(i=0;i<size;i++)
	{
		if(array[i]==key)
		{
			return i;
		}
	}

	return -1;
}
