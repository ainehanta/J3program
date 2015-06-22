#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10
#define SORT_NUM 20

typedef struct
{
	int comp;
	int ex;
} INFO;

int print_menu(void);
void create_array(int array[],int length,unsigned int seed);
void show_array(int array[],int length,int now);

void bubble_sort(int array[],int length,INFO *info);
void selection_sort(int array[],int length,INFO *info);
void insertion_sort(int array[],int length,INFO *info);

int main(void)
{
	INFO info;
	int i,total_comp,total_ex;
	int array[ARRAY_SIZE];

	while(1)
	{
		switch(print_menu())
		{
			case 1:
				total_comp = 0;
				total_ex = 0;
				printf("--------------------------------------\n");
				for(i=0;i<SORT_NUM;i++)
				{
					create_array(array,ARRAY_SIZE,(unsigned)time(NULL)+i);
					bubble_sort(array,ARRAY_SIZE,&info);
					total_comp += info.comp;
					total_ex += info.ex;
					printf("count:%d\n",i+1);
					printf("comp:%d\n",info.comp);
					printf("ex  :%d\n",info.ex);
					printf("avarage comp:%d\n",total_comp/(i+1));
					printf("avarage ex  :%d\n",total_ex/(i+1));
				}
				printf("--------------------------------------\n");
				break;
			case 2:
				total_comp = 0;
				total_ex = 0;
				printf("--------------------------------------\n");
				for(i=0;i<SORT_NUM;i++)
				{
					create_array(array,ARRAY_SIZE,(unsigned)time(NULL)+i);
					selection_sort(array,ARRAY_SIZE,&info);
					total_comp += info.comp;
					total_ex += info.ex;
					printf("count:%d\n",i+1);
					printf("comp:%d\n",info.comp);
					printf("ex  :%d\n",info.ex);
					printf("avarage comp:%d\n",total_comp/(i+1));
					printf("avarage ex  :%d\n",total_ex/(i+1));
				}
				printf("--------------------------------------\n");
				break;
			case 3:
				total_comp = 0;
				total_ex = 0;
				printf("--------------------------------------\n");
				for(i=0;i<SORT_NUM;i++)
				{
					create_array(array,ARRAY_SIZE,(unsigned)time(NULL)+i);
					insertion_sort(array,ARRAY_SIZE,&info);
					total_comp += info.comp;
					total_ex += info.ex;
					printf("count:%d\n",i+1);
					printf("comp:%d\n",info.comp);
					printf("ex  :%d\n",info.ex);
					printf("avarage comp:%d\n",total_comp/(i+1));
					printf("avarage ex  :%d\n",total_ex/(i+1));
				}
				printf("--------------------------------------\n");
				break;
			case 0:
				printf("Good bye.\n");
				return 0;
				break;
		}
	}
	return 1;
}

void bubble_sort(int array[],int length,INFO *info)
{
	int i,j,tmp;
	info->comp = 0;
	info->ex = 0;

	for(i=0;i<length-1;i++)
	{
		for(j=length;j>=i;j--)
		{
			info->comp++;
			if(array[j]>array[j+1])
			{
				info->ex++;
				tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
			}
		}
		show_array(array,length,i);
	}
	show_array(array,length,i);
}

void selection_sort(int array[],int length,INFO *info)
{
	int i,j,tmp;
	int lowest,lowi;

	info->comp = 0;
	info->ex = 0;

	for(i=0;i<length-1;i++)
	{
		lowest = array[i];
		for(j=i+1;j<length;j++)
		{
			info->comp++;
			if(lowest>array[j])
			{
				lowest = array[j];
				lowi = j;
			}
		}
		tmp = array[i];
		array[i] = array[lowi];
		array[lowi] = tmp;
		info->ex++;
		show_array(array,length,i);
	}
	show_array(array,length,i);
}

void insertion_sort(int array[],int length,INFO *info)
{
	int i,j,tmp;
	info->comp = 0;
	info->ex = 0;

	for(i=1;i<length;i++)
	{
		for(j=i;j>0&&array[j-1]>array[j];j--)
		{
			info->comp++;
			info->ex++;
			tmp = array[j];
			array[j] = array[j-1];
			array[j-1] = tmp; 
		}
		info->comp++;
		show_array(array,length,i);
	}
}

int print_menu(void)
{
	int input = 0;
	printf("Select Sort Algorythm\n");
	printf("1:bubble,2:selection,3:insertion,0:exit\n");
	printf("input>");
	scanf("%d",&input);

	return input;
}

void create_array(int array[],int length,unsigned int seed)
{
	int i;
	srand(seed);
	for(i=0;i<length;i++)
	{
		array[i] = rand()%length;
	}
}

void show_array(int array[],int length,int now)
{
	int i;
	for(i=0;i<length;i++)
	{
		if(i==now)
			printf(" |");
		printf("%2d",*array);
		array++;
	}
	printf("\n");
}
