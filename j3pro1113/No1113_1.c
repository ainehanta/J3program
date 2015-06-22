#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ARRAY_SIZE 1000000
#define SORT_NUM 20

int print_menu(void);
void create_array(int array[],int length,unsigned long seed);
void show_array(int array[],int length);

void insertion_sort(int array[],int length);
void shell_sort_a(int array[],int length);
void shell_sort_b(int array[],int length);

int main(void)
{
	unsigned long seed;
	clock_t start_clock,end_clock;
	int dt;
	int array[ARRAY_SIZE];

	seed = (unsigned)time(NULL);

	printf("------------------------------------\n");
	printf("Insertion sort start\n");

	create_array(array,1000,seed);
	start_clock = clock();
	insertion_sort(array,ARRAY_SIZE);
	end_clock = clock();

	printf("Insertion sort end\n");
	dt = (end_clock-start_clock)/1000;
	printf("time:%dmsec\n",dt);
	printf("------------------------------------\n");

	printf("\n");

	printf("------------------------------------\n");
	printf("Shell Sort A start\n");

	create_array(array,1000,seed);
	start_clock = clock();
	shell_sort_a(array,ARRAY_SIZE);
	end_clock = clock();

	printf("Shell Sort A end\n");
	dt = (end_clock-start_clock)/1000;
	printf("time:%dmsec\n",dt);
	printf("------------------------------------\n");

	printf("\n");

	printf("------------------------------------\n");
	printf("Shell Sort B start\n");

	create_array(array,1000,seed);
	start_clock = clock();
	shell_sort_b(array,ARRAY_SIZE);
	end_clock = clock();

	printf("Shell Sort B end\n");
	dt = (end_clock-start_clock)/1000;
	printf("time:%dmsec\n",dt);
	printf("------------------------------------\n");

	return 0;
}

void shell_sort_a(int array[],int length)
{
	int i,j,tmp;
	int h;

	for(h=1;h<length/9;h=h*3+1)
	{
		printf("h = %d\n",h);
	}

	for(;h>0;h/=3)
	{
		for(i=h;i<length;i++)
		{
			for(j=i;j>=h&&array[j-h]>array[j];j-=h)
			{
				tmp = array[j];
				array[j] = array[j-h];
				array[j-h] = tmp;
			}
		}
	}
}

void shell_sort_b(int array[],int length)
{
	int i,j,tmp;
	int h;

	for(i=1;h<length/9;i++)
	{
		h = pow(2,i)-1;
		printf("h = %d\n",h);
	}

	for(;h>0;h/=2)
	{
		for(i=h;i<length;i++)
		{
			for(j=i;j>=h&&array[j-h]>array[j];j-=h)
			{
				tmp = array[j];
				array[j] = array[j-h];
				array[j-h] = tmp;
			}
		}
	}
}

void insertion_sort(int array[],int length)
{
	int i,j,tmp;

	for(i=1;i<length;i++)
	{
		for(j=i;j>0&&array[j-1]>array[j];j--)
		{
			tmp = array[j];
			array[j] = array[j-1];
			array[j-1] = tmp; 
		}
	}
}

void create_array(int array[],int length,unsigned long seed)
{
	int i;
	srand(seed);
	for(i=0;i<length;i++)
	{
		array[i] = rand()%length;
	}
}

void show_array(int array[],int length)
{
	int i;
	for(i=0;i<length;i++)
	{
		printf("%2d\n",*array);
		array++;
	}
}
