#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int total(int array[]);

int main(void)
{
	int i;
	int* ip;

	srand((unsigned)time(NULL));

	ip = (int*)malloc(sizeof(int)*3);
	for(i=0;i<3;i++)
	{
		ip[i] = rand()%10;
		printf("ip[%d] = %d\n",i,ip[i]);
	}

	printf("total = %d\n",total(ip));

	return 0;
}

int total(int array[])
{
	int i;
	int tmp = 0;

	for(i=0;i<3;i++)
		tmp += *array++;

	return tmp;
}
