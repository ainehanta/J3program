#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
	int value;
	struct node *next;
};

typedef struct node LIST;

void list_init(LIST**,int);
void list_print(LIST*);
void list_copy(LIST**,LIST**);

int main(void)
{
	LIST* dest = NULL;
	LIST* source = NULL;

	srand((unsigned)time(NULL));

	list_init(&source,10);
	
	printf("\nINIT\n");
	printf("LIST:source\n");
	list_print(source);
	printf("LIST:destination\n");
	list_print(dest);

	list_copy(&dest,&source);

	printf("\nCOPY\n");
	printf("LIST:source\n");
	list_print(source);
	printf("LIST:destination\n");
	list_print(dest);

	return 0;
}

void list_init(LIST** list,int length)
{
	*list = (LIST*)malloc(sizeof(LIST));
	(*list)->value = rand()%10;

	length--;
	if(length)
	{
		list_init(&((*list)->next),length);
	}
	else
	{
		(*list)->next = NULL;
	}
}

void list_print(LIST* list)
{
	int i;
	printf("START >>");

	for(;list;list=list->next)
		printf(" %d",list->value);

	printf(" >> END\n");
}

void list_copy(LIST** dest,LIST** source)
{
	if(!(*source))
	{
		(*dest) = NULL;
		return;
	}

	*dest = (LIST*)malloc(sizeof(LIST));
	(*dest)->value = (*source)->value;

	list_copy(&((*dest)->next),&((*source)->next));
}
