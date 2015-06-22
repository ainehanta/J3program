#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10

int binary_search(int* array,int key,int min,int max);
void bubble_sort(int* array,int size);

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

	bubble_sort(array,ARRAY_SIZE);

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
		result = binary_search(array,key,0,ARRAY_SIZE-1);
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

//¾º½çÁ°Äó
int binary_search(int* array,int key,int min,int max)
{
	int ret = 0;
	int half = (max-min)/2+min;
	printf("min = %d,half = %d,max = %d\n",min,half,max);

	if(min==max&&array[min]!=key)
	{
		return -1;
	}

	if(array[min]==key)
	{
		return min;
	}
	else if(array[max]==key)
	{
		return max;
	}
	else if(array[half]==key)
	{
		return half;
	}

	if(array[half]<key)
	{
		return binary_search(array,key,half+1,max);
	}
	else
	{
		return binary_search(array,key,min,half);
	}
}

//¾º½ç
void bubble_sort(int* array,int size)
{
	int i,j;
	int tmp;

	for(i=0;i<size;i++)
	{
		for(j=0;j<size-1;j++)
		{
			if(array[j]>array[j+1])
			{
				tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
			}
		}
	}
}
