#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};

int main(void)
{
	struct node* root;
	root = (struct node*)malloc(sizeof(struct node));
	root->next = (struct node*)malloc(sizeof(struct node));
	root->next->next = (struct node*)malloc(sizeof(struct node));
	root->next->next->data = 3;

	printf("%d\n",root->next->next->data);
}
