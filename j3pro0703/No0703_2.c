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
void list_insert(LIST*,int);

int main(void)
{
	LIST list;
	list.next = &list;

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
				list_print(&list);
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
	LIST* head;
	head = list;

	printf("PRINT\n");

	if(list->next==list)
	{
		printf("List is Empty.\n");
		return;
	}

	printf("START >>");

	for(list=list->next;list!=head;list=list->next)
	{
		printf(" %d",list->value);
	}

	printf(" >> END\n");
}

void list_insert(LIST* list,int value)
{
	LIST *next;

	next = list->next;
	list->next = (LIST*)malloc(sizeof(LIST));
	list = list->next;
	list->next = next;
	list->value = value;
}
