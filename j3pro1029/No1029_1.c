#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

#define DELETED		(int*)1
#define EMPTY		NULL
#define STATUS_OK	0
#define STATUS_FAIL	-1

int print_menu(void);

int hash(int value);
int rehash(int value);

void hash_init(int* table[]);
int hash_add(int* table[],int value);
int hash_delete(int* table[],int value);
int hash_search(int* table[],int value);
void hash_dump(int* table[]);

int main(void)
{
	int mode = 0;
	int result = 0;
	int tmp = 0;

	int* table[TABLE_SIZE];
	hash_init(table);

	for(;;)
	{
		mode = print_menu();
		switch(mode)
		{
			case 1:
				printf("Input data>");
				scanf("%d",&tmp);
				result = hash_add(table,tmp);
				if(result==STATUS_FAIL)
				{
					printf("Can't add this data.\n");
				}
				break;
			case 2:
				printf("input data>");
				scanf("%d",&tmp);
				result = hash_delete(table,tmp);
				if(result==STATUS_FAIL)
				{
					printf("Can't delete this data.\n");
				}
				break;
			case 3:
				printf("Input data>");
				scanf("%d",&tmp);
				result = hash_search(table,tmp);
				if(result==STATUS_FAIL)
				{
					printf("Not found data:%d\n",tmp);
				}
				else
				{
					printf("%d found at %d\n",tmp,result);
				}
				break;
			case 4:
				printf("--------------------------------\n");
				hash_dump(table);
				printf("--------------------------------\n");
				break;
			case 0:
				printf("Good bye.\n");
				return 0;
			default :
				printf("invalid value.Please retry.\n");
				break;
		}
	}

	return 1;
}

int print_menu(void)
{
	int mode = 0;
	printf("(1)Add data (2)Delete data (3)Search data (4)Dump (0)End\n");
	printf("Input>");
	scanf("%d",&mode);

	return mode;
}

int hash(int value)
{
	return value % TABLE_SIZE;
}

int rehash(int value)
{
	return (value+1) % TABLE_SIZE;
}

void hash_init(int* table[])
{
	int i;
	for(i=0;i<TABLE_SIZE;i++)
	{
		table[i] = EMPTY;
	}
}

int hash_add(int* table[],int value)
{
	int count;
	int hash_value = hash(value);

	for(count=0;count<TABLE_SIZE;count++)
	{
		if(table[hash_value]==EMPTY||
		   table[hash_value]==DELETED)
		{
			break;
		}

		hash_value = rehash(hash_value);
	}

	if(count==TABLE_SIZE)
	{
		return STATUS_FAIL;
	}

	table[hash_value] = malloc(sizeof(int));
	*table[hash_value] = value;

	return STATUS_OK;
}

int hash_search(int* table[],int value)
{
	int count;
	int hash_value = hash(value);

	for(count=0;count<TABLE_SIZE;count++)
	{
		if(table[hash_value]==EMPTY)
		{
			return STATUS_FAIL;
		}
		else if(table[hash_value]!=DELETED)
		{
			if(*table[hash_value]==value)
			{
				break;
			}
		}
		hash_value = rehash(hash_value);
	}

	if(count==TABLE_SIZE)
	{
		return STATUS_FAIL;
	}

	return hash_value;
}

int hash_delete(int* table[],int value)
{
	int result = 0;
	result = hash_search(table,value);

	if(result==STATUS_FAIL)
	{
		return STATUS_FAIL;
	}

	free(table[result]);
	table[result] = DELETED;

	return STATUS_OK;
}

void hash_dump(int* table[])
{
	int i;
	for(i=0;i<TABLE_SIZE;i++)
	{
		printf("table[%2d] = ",i);
		if(table[i]==EMPTY)
		{
			printf("EMPTY");
		}
		else if(table[i]==DELETED)
		{
			printf("DELETED");
		}
		else
		{
			printf("%d",*table[i]);
		}
		printf("\n");
	}
}
