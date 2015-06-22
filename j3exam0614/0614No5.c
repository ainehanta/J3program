#include <stdio.h>

void overf(int*);

int main(void)
{
	int check = 0;

	overf(&check);
}

void overf(int* check)
{
	printf("check = %d\n",(*check)++);
	overf(check);
}
