#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET_SIZE 10

struct CELL {
	char str[10];
	struct CELL *next;
};

void Insert(struct CELL *hash_table[], char str[]);
int hash(char str[]);
void InitTable(struct CELL *hash_table[]);
void PrintTable(struct CELL *hash_table[]);

int hash(char str[])
{
	int i;
	int tmp;

	for(tmp=0;str[i]!='\0';i++)
	{
		tmp += str[i];
	}

	return tmp%BUCKET_SIZE;
}

void InitTable(struct CELL *hash_table[])
{
	int i;

	for (i = 0; i < BUCKET_SIZE; i++) {
		hash_table[i] = NULL;
	}
}
	
void Insert(struct CELL *hash_table[], char str[])
{
	int key = hash(str);
	struct CELL *node;
	int i;

	node = (struct CELL*)malloc(sizeof(struct CELL));
	for(i=0;str[i]!='\0'&&i<9;i++)
	{
		node->str[i] = str[i];
	}
	node->str[i] = '\0';

	hash_table[key] = node;
}

void PrintTable(struct CELL *hash_table[])
{
	int i;
		
	for (i = 0; i < BUCKET_SIZE; i++) {
		printf("%2d -> %s\n", i, hash_table[i]->str);
	}
}

int main(void)
{
	struct CELL *hash_table[BUCKET_SIZE];
	char str[10];
	int menu;
	char dummy;

	InitTable(hash_table);

	do {
		printf("(1) Insert str  (2) Print table  (0) End  :");
		scanf("%d%c", &menu, &dummy);

		switch (menu) {
		case 1 : 
			    printf("Input string : "); 
			    scanf("%s%c", str, &dummy);
			    Insert(hash_table, str);
			    break;
		case 2 : 
			    PrintTable(hash_table);
			    break;
		}
	} while (menu != 0);

	return 0;
}

		
