#include <stdio.h>
#include <stdlib.h>

struct node
{
	char* word;
	struct node* next;
};

typedef struct node* node_p;
typedef struct node node_t;

void input(node_p*);
void output(node_p*);
void sort(node_p*);
void search(node_p*);

int main(void)
{
	node_p start;

	input(&start);

	printf("--------------------\n");
	output(&start);
	printf("--------------------\n");

	printf("\n");

	sort(&start);
	printf("Sorting...\n");
	printf("--------------------\n");
	output(&start);
	printf("--------------------\n");

	return 0;
}

void input(node_p* n)
{
	char buffer[10];
	*n = (node_p)calloc(1,sizeof(node_t));
	(*n)->word = (char*)calloc(50,sizeof(char));
	printf("単語を入力してください\n>");
	scanf("%s",(*n)->word);

	printf("次の単語を入力しますか？\n>");
	scanf("%s",buffer);

	if(buffer[0]=='n')
	{
		(*n)->next = NULL;
	}
	else
	{
		input(&(*n)->next);
	}
}

void output(node_p* n)
{
	printf("%s\n",(*n)->word);

	if((*n)->next!=NULL)
	{
		output(&(*n)->next);
	}
}

void sort(node_p* n)
{
	int result;
	int count,i;
	node_p tmp;

	tmp = *n;
	for(count=0;tmp->next!=NULL;count++,tmp=tmp->next);

	for(i=0;count>=i;i++)
	{
		search(n);
	}
}

void search(node_p* now)
{
	int result;
	char* tmp;

	if((*now)->next==NULL)
	{
		return;
	}
	else
	{
		result = strncmp((*now)->word,(*now)->next->word,1);

		if(result>0)
		{
			tmp = (*now)->word;
			(*now)->word = (*now)->next->word;
			(*now)->next->word = tmp;
		}

		search(&((*now)->next));
	}
}
