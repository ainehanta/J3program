#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
	int value;
	struct node *prev;
	struct node *next;
};

typedef struct node stack_t;

void print_menu(void);

void stack_init(stack_t**);
void stack_clear(stack_t**);
int stack_check(stack_t*);
void stack_print(stack_t*);

int stack_pop(stack_t**);
void stack_push(stack_t**,int);

int main(void)
{
	stack_t* stack;
	int status = 0;

	srand((unsigned)time(NULL));
	stack_init(&stack);

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

void stack_push(stack_t** stack,int value)
{
	(*stack)->value = value;
	(*stack)->next = (stack_t*)malloc(sizeof(stack_t));
	(*stack)->next->prev = *stack;
	*stack = (*stack)->next;
	printf("Push:Pushed data : %d\n",value);
}

int stack_pop(stack_t** stack)
{
	if(stack_check(*stack)==0)
	{
		printf("Pop:Stack is underflow.\n");
		return;
	}

	*stack = (*stack)->prev;
	free((*stack)->next);
	(*stack)->next = NULL;
	printf("Pop:Poped data : %d\n",(*stack)->value);
	return (*stack)->value;
}

void stack_init(stack_t** stack)
{
	*stack = (stack_t*)malloc(sizeof(stack_t));
	(*stack)->next = NULL;
	(*stack)->prev = NULL;
}

void stack_clear(stack_t** stack)
{
	if((*stack)->prev==NULL)
	{
		printf("Clear:Stack is empty.\n");
		return;
	}

	*stack = (*stack)->prev;
	free((*stack)->next);
	(*stack)->next = NULL;

	printf("Clear:Stack is clear.\n");

	stack_clear(stack);
}

int stack_check(stack_t* stack)
{
	if(stack->prev==NULL)
	{
		printf("Check:Stack is empty.\n");
		return 0;
	}

	printf("Check:Stack has data.\n");
	return 1;
}

void stack_print(stack_t* stack)
{
	stack_t* tmp;

	if(stack_check(stack)==0)
	{
		printf("Print:Stack is empty.\n");
		return;
	}

	printf("Print:Stack =");

	for(;stack->prev!=NULL;stack = stack->prev)
	{
		printf(" %d",stack->prev->value);
	}

	printf("\n");
}
