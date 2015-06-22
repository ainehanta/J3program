#include <stdio.h>
#include <stdlib.h>

#define STATE_INSERT	0
#define STATE_PRINT		1
#define STATE_EXIT		2

struct NODE
{
	int value;
	struct NODE *next;
};

typedef struct NODE LIST;

void print_menu(void);
void list_print(LIST*);
void list_insert(LIST**,int);

int main(void)
{
	LIST* list;
	list = NULL;

	int state;
	int data;

	while(1)
	{
		print_menu();
		printf("INPUT>");
		scanf("%d",&state);

		if(state==STATE_EXIT)
			break;

		switch(state)
		{
			case STATE_INSERT:
				printf("DATA>");
				scanf("%d",&data);
				list_insert(&list,data);
				break;
			case STATE_PRINT :
				list_print(list);
				break;
		}
	}

	return 0;
}

void print_menu(void)
{
	printf("------------------------\n");
	printf("0:INSERT,1:PRINT,2:EXIT\n");
}

void list_print(LIST* list)
{
	LIST* now;
	printf("PRINT\n");

	if(!list)
	{
		printf("List is Empty.\n");
		return;
	}

	printf("START >>");

	now = list;
	do {
		printf(" %d",now->value);
		now = now->next;
	} while(list!=now);

	printf(" >> END\n");
}

void list_insert(LIST** list,int value)
{
	LIST* next;
	if(!(*list))
	{
		*list = (LIST*)malloc(sizeof(LIST));
		(*list)->next = *list;
		(*list)->value = value;
	}
	else
	{
		next = (*list)->next;
		(*list)->next = (LIST*)malloc(sizeof(LIST));
		*list = (*list)->next;
		(*list)->next = next;
		(*list)->value = value;
	}
}
