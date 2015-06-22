#define DEBUG
#define ST_SIZE 10

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
	int value[ST_SIZE];
	int sp;
} STACK;

void stack_clear(STACK*);
int stack_check(STACK*);
int pop(STACK*);
void push(STACK*,int);

int main(void)
{
	int i,value;
	STACK stack;

	srand((unsigned)time(NULL));

	stack_clear(&stack);
	stack_check(&stack);

	for(i=0;i<10;i++)
	{
		if(rand()%2==0)
		{
			value = rand()%10;
			push(&stack,value);
		}
		else
		{
			pop(&stack);
		}
	}

	stack_check(&stack);
}

void stack_clear(STACK* stack)
{
	stack->sp = 0;

#ifdef DEBUG
	printf("Success\t:Stack Clear. sp = %d\n",stack->sp);
#endif
}

int stack_check(STACK* stack)
{
	if(stack->sp>0)
	{
#ifdef DEBUG
		printf("Stack has Data. sp = %d\n",stack->sp);
#endif
		return 0;
	}
	else
	{
#ifdef DEBUG
		printf("Stack is Empty. sp = %d\n",stack->sp);
#endif
		return 1;
	}

	return 1;
}

int pop(STACK* stack)
{
	if(stack->sp==0)
	{
		printf("Error\t:Stack is underflow. sp = %d\n",stack->sp);
		return 0;
	}

#ifdef DEBUG
	printf("Success\t:Stack pop\t, data = %d , sp = %d\n",stack->value[stack->sp-1],stack->sp-1);
#endif

	return stack->value[--stack->sp];
}

void push(STACK* stack,int value)
{
	if(stack->sp==ST_SIZE)
	{
		printf("Error\t:Stack is overflow. sp = %d\n",stack->sp);
		return;
	}

#ifdef DEBUG
	printf("Success\t:Stack push\t, data = %d , sp = %d\n",value,stack->sp);
#endif

	stack->value[stack->sp++] = value;
}
