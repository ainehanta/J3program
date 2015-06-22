#include <stdio.h>

#define STACK_SIZE 10

void push(int data, int *sp, int stack[]);
int pop(int *sp, int stack[]);

int main(void)
{
	int stack[STACK_SIZE];
	int sp;

	sp = 0;

	push(3, &sp, stack);
	push(5, &sp, stack);

	printf("%d\n", pop(&sp, stack));
	
	return 0;
}

void push(int data, int *sp, int stack[])
{
	if (*sp == STACK_SIZE) {
		printf("Stack is full!  So you can't push the data!!\n");	
	} else {
		stack[(*sp)++] = data;
	}
}

int pop(int *sp, int stack[])
{
	if (*sp == 0) {
		printf("Stack is empty!  So you can't pop the data!!\n");
		return -1;
	} else {
		return stack[--(*sp)];
	}

	return 0;
}	
