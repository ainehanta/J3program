#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ARRAY_SIZE 100000
#define N_MAX 100
#define AVARAGE_NUM 20

int print_menu(void);
void create_array(int array[],int length,unsigned long seed);
void show_array(int array[],int length);

void shell_sort_n(int array[],int length,int n);

int main(void)
{
	unsigned long seed;
	clock_t start_clock,end_clock;
	int dt;
	int array[ARRAY_SIZE];
	int n;
	int total_n[N_MAX] = {0};
	int i;


	for(i=0;i<AVARAGE_NUM;i++)
	{
		seed = (unsigned)time(NULL);
		for(n=1;n<=N_MAX;n++)
		{
//			printf("------------------------------------\n");
//			printf("Shell sort start\n");
//			printf("n param = %d\n",n);

			create_array(array,65536,seed);
			start_clock = clock();
			shell_sort_n(array,ARRAY_SIZE,n);
			end_clock = clock();

//			printf("Shell sort end\n");
			dt = (end_clock-start_clock)/1000;
//			printf("time:%dmsec\n",dt);
//			printf("------------------------------------\n");

//			printf("\n");
			total_n[n-1] += dt;
		}
	}

	printf("avarage_time\n");
	for(i=1;i<=N_MAX;i++)
	{
		printf("n = %d : %dmsec\n",i,total_n[i-1]/AVARAGE_NUM);
	}

	return 0;
}

void shell_sort_n(int array[],int length,int n)
{
	int i,j,tmp;
	int h;

	for(h=1;h<length/n;h=h*3+1)
	{
		//printf("h = %d\n",h);
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
