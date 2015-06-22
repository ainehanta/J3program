#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HASH_BUCKET	5
#define ARRAY_SIZE	10

struct _hash_node
{
	int value;
	struct _hash_node* next;
};

typedef struct _hash_node HASH_NODE;

int print_menu(void);

HASH_NODE* hash_search(HASH_NODE** table,int key);
//int hash_remove(HASH_NODE** table,HASH_NODE* node);
void hash_init(HASH_NODE** table);
void hash_insert(HASH_NODE** table,int value);
void hash_print(HASH_NODE** table);
void print_hash_node(HASH_NODE* node);
void insert_hash_node(HASH_NODE** root,int value);
HASH_NODE* seek_hash_node(HASH_NODE* root,int value);
int hash(int value);

int main(void)
{
	int menu_select;
	int value;

	HASH_NODE* hash_table[HASH_BUCKET];
	hash_init(hash_table);

	for(;;)
	{
		menu_select = print_menu();

		switch(menu_select)
		{
		case 1:
			printf("Insert value>"); scanf("%d",&value);
			hash_insert(hash_table,value);
			break;
		case 2:
			printf("Can't select this menu\n");
			break;
		case 3:
			printf("Insert value>"); scanf("%d",&value);
			HASH_NODE* node = hash_search(hash_table,value);
			printf("Result:");
			if(node==NULL)
			{
				printf("Not Found:%d\n",value);
			}
			else
			{
				printf("Found:%d at %p\n",value,node);
			}
			break;
		case 4:
			printf("HASH>\n");
			hash_print(hash_table);
			break;
		case 5:
			return 0;
			break;
		default:
			printf("Please select 1 to 5\n");
			break;
		}
	}

	return 1;
}

int print_menu(void)
{
	int select;
	printf("(1)Insert (2)Remove (3)Search (4)Print (5)Exit\n");
	printf("Input >");
	scanf("%d",&select);
	return select;
}

void hash_init(HASH_NODE** table)
{
	int i;
	for(i=0;i<HASH_BUCKET;i++)
	{
		table[i] = NULL;
	}
}

void hash_print(HASH_NODE** table)
{
	int i;
	for(i=0;i<HASH_BUCKET;i++)
	{
		printf("[%02d]",i);
		if(table[i])
		{
			print_hash_node(table[i]);
		}
		printf("\n");
	}
}

void print_hash_node(HASH_NODE* node)
{
	printf(" -> %d(%p)",node->value,node);
	if(node->next)
	{
		print_hash_node(node->next);
	}
}

void hash_insert(HASH_NODE** table,int value)
{
	int hash_value;

	hash_value = hash(value);
	insert_hash_node(&table[hash_value],value);
}

HASH_NODE* hash_search(HASH_NODE** table,int key)
{
	int hash_value = hash(key);
	HASH_NODE* result;

	return seek_hash_node(table[hash_value],key);
}

void insert_hash_node(HASH_NODE** root,int value)
{
	HASH_NODE* tmp = NULL;

	if(*root==NULL)
	{
		*root = malloc(sizeof(HASH_NODE));
		(*root)->next = NULL;
		(*root)->value = value;
		return;
	}

	tmp = *root;
	for(;tmp->next!=NULL;tmp=tmp->next);

	tmp->next = malloc(sizeof(HASH_NODE));
	tmp->next->next = NULL;
	tmp->next->value = value;
}

HASH_NODE* seek_hash_node(HASH_NODE* root,int value)
{
	for(;root;root=root->next)
	{
		if(root->value==value)
		{
			break;
		}
	}

	return root;
}

int hash(int value)
{
	return value % HASH_BUCKET;
}
