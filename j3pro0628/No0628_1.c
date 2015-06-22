#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
	int value;
	struct node *prev;
};

typedef struct node STACK;

void print_menu(void);

void stack_clear(STACK**);
int stack_check(STACK*);
void stack_print(STACK*);

int stack_pop(STACK**);
void stack_push(STACK**,int);

int main(void)
{
	STACK* stack;
	int status = 0;

	srand((unsigned)time(NULL));

	for(;;)
	{
		print_menu();
		scanf("%d",&status);
		switch(status)
		{
		case 0:
			stack_push(&stack,rand()%10);
			break;
		case 1:
			stack_pop(&stack);
			break;
		}

		if(status==2)
		{
			break;
		}

		stack_print(stack);
	}

	stack_print(stack);
	stack_clear(&stack);
}

void print_menu(void)
{
	printf("------------------------\n");
	printf("0:Push,1:Pop,2:Exit\n");
	printf("Input:");
}

void stack_push(STACK** stack,int value)
{
	STACK *tmp;
	if((*stack)==NULL)
	{
		*stack = (STACK*)malloc(sizeof(STACK));
		(*stack)->prev = NULL;
	}
	else
	{
		tmp = *stack;
		*stack = (STACK*)malloc(sizeof(STACK));
		(*stack)->prev = tmp;
	}

	(*stack)->value = value;
	printf("Push:Pushed data : %d\n",value);
}

int stack_pop(STACK** stack)
{
	STACK *tmp;
	int value;

	if(!(*stack))
	{
		printf("Pop:Stack is underflow.\n");
		return;
	}

	value = (*stack)->value;

	if(!((*stack)->prev))
	{
		free(*stack);
		*stack = NULL;
	}
	else
	{
		tmp = *stack;
		*stack = (*stack)->prev;
		free(tmp);
	}

	printf("Pop:Poped data : %d\n",value);
	return value;
}

void stack_clear(STACK** stack)
{
	STACK *tmp;

	if(!(*stack))
	{
		printf("Clear:Stack is empty.\n");
		return;
	}

	tmp = *stack;
	*stack = (*stack)->prev;

	free(tmp);

	if(!((*stack)->prev))
	{
		free(*stack);
	}
	else
	{
		stack_clear(stack);
	}

	printf("Clear:Stack is clear.\n");
}

void stack_print(STACK* stack)
{
	if(!stack)
	{
		printf("Print:Stack is empty.\n");
		return;
	}

	printf("Print:Stack =");

	for(;stack;stack = stack->prev)
	{
		printf(" %d",stack->value);
	}

	printf("\n");
}
