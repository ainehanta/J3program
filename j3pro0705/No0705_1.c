#include <stdio.h>
#include <stdlib.h>

#define STATE_EXIT		3
#define STATE_OUTPUT	2
#define STATE_INSERT	0
#define STATE_DELETE	1

struct node
{
	struct node *next;
	struct node *prev;
	int value;
};

typedef struct node LIST;

void list_init(LIST*);
void list_print(LIST*);
LIST* list_seek(LIST*,int);
void list_insert(LIST*,LIST*,int);
void list_delete(LIST*,LIST*);

void print_menu(void);

int main(void)
{
	int state = 0;
	int data = 0;

	LIST list;
	LIST* pos;
	pos = NULL;
	list_init(&list);

	while(1)
	{
		printf("----------------------------------\n");

		list_print(&list);

		printf("----------------------------------\n");
		printf("0:INSERT,1:DELETE,2:OUTPUT,3:EXIT\n");
		printf("input>");
		scanf("%d",&state);

		switch(state)
		{
			case STATE_OUTPUT:
				list_print(&list);
				break;
			case STATE_INSERT:
				printf("Input insert position>");
				scanf("%d",&data);
				pos = list_seek(&list,data);
				if(pos==NULL)
				{
					printf("Error\n");
					break;
				}
				printf("Input insert data>");
				scanf("%d",&data);
				list_insert(&list,pos,data);
				break;
			case STATE_DELETE:
				printf("Input delete position>");
				scanf("%d",&data);
				pos = list_seek(&list,data);
				if(pos==NULL)
				{
					printf("Error\n");
					break;
				}
				list_delete(&list,pos);
				break;
			default:
				state = STATE_EXIT;
				break;
		}

		if(state==STATE_EXIT)
		{
			break;
		}
	}
}

void print_menu(void)
{
	printf("---------------------------------\n");
	printf("1:OUTPUT,2:INSERT,3:DELETE,0:EXIT\n");
}

void list_init(LIST* list)
{
	list->prev = list->next = list;
}

LIST* list_seek(LIST* list,int pos)
{
	LIST* head;
	head = list;

	if(pos==0)
	{
		return head;
	}

	if(head==head->next)
	{
		printf("List is empty.\n");
		return NULL;
	}

	for(list=head->next;
		pos>0&&list!=head;
		list=list->next,pos--);

	if(list==head)
	{
		printf("This data was not found.\n");
		list = NULL;
	}

	return list;
}

void list_insert(LIST* list,LIST* pos,int data)
{
	LIST* tmp;
	tmp = (LIST*)malloc(sizeof(LIST));
	tmp->value = data;

	for(list=list->next;list!=pos;list=list->next);

	tmp->next = list->next;
	tmp->prev = list;
	list->next->prev = tmp;
	list->next = tmp;
}

void list_delete(LIST* list,LIST* pos)
{
	LIST* head;
	LIST* tmp;
	head = list;

	if(head->next==head)
	{
		printf("List is empty.\n");
		return;
	}

	if(pos!=head)
	{
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		free(pos);
	}
	else
	{
		list->next->next->prev = list;
		tmp = list->next->next;
		free(list->next);
		list->next = tmp;
	}
}

void list_print(LIST* list)
{
	int count = 0;
	LIST* head;
	head = list;

	printf("RIGHT:\n");
	printf("START >>");

	for(list=head->next,count=0;list!=head;list=list->next,count++)
	{
		printf(" %d:(%d)",list->value,count);
	}

	printf(" >> END\n");

	printf("LEFT:\n");
	printf("START >>");

	for(list=head->prev,count=0;list!=head;list=list->prev,count++)
	{
		printf(" %d:(%d)",list->value,count);
	}

	printf(" >> END\n");
}
