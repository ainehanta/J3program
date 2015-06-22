#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct stack_node
{
	int value;

	struct stack_node *next;
	struct stack_node *prev;
};

typedef struct stack_node stack_node_t;
//typedef struct stack_node* stack_node_p;

void stack_init(stack_node_t**);
void stack_clear(stack_node_t*);
int stack_check(stack_node_t*);
int pop(stack_node_t*);
void push(stack_node_t*,int);

int main(void)
{
	int i,value;
	stack_node_t* stack;

	srand((unsigned)time(NULL));

	stack_init(&stack);
	stack_clear(stack);
	stack_check(stack);

	for(i=0;i<10;i++)
	{
		if(rand()%2==0)
		{
			value = rand()%10;
			push(stack,value);
		}
		else
		{
			pop(stack);
		}
	}

	stack_check(stack);
}

void stack_init(stack_node_t** stack)
{
	stack = (stack_node_t*)malloc(sizeof(stack_node_t));
	stack->prev = NULL;
	stack->next = NULL;
}

void stack_clear(stack_node_t* stack)
{
	if(stack->prev==NULL&&stack->next==NULL)
	{
		return;
	}

	if(stack->next!=NULL)
	{
		stack_clear(stack->next);
	}
	else
	{
		stack = stack->prev;
		free(stack->next);
		stack->next = NULL;
		stack_clear(stack);
	}

#ifdef DEBUG
	printf("Success\t:Stack Clear.\n");
#endif
}

int stack_check(stack_node_t* stack)
{
	if(stack->prev==NULL)
	{
#ifdef DEBUG
		printf("Stack is Empty.\n");
#endif
		return 0;
	}
	else
	{
#ifdef DEBUG
		printf("Stack has Data.\n");
#endif
		return 1;
	}

	return 1;
}

int pop(stack_node_t* stack)
{
	int value;

	if(stack->prev==NULL)
	{
		printf("Error\t:Stack is underflow.\n");
		return 0;
	}

	value = stack->prev->value;

#ifdef DEBUG
	printf("Success\t:Stack pop\t, data = %d\n",value);
#endif

	stack = stack->prev;
	free(stack->next);
	stack->next = NULL;

	return value;
}

void push(stack_node_t* stack,int value)
{
	stack->value = value;
	stack->next = (stack_node_t*)malloc(sizeof(stack_node_t));
	stack->next->prev = stack;

	stack = stack->next;
	stack->next = NULL;

#ifdef DEBUG
	printf("Success\t:Stack push\t, data = %d\n",value);
#endif
}
