#include <stdio.h>

struct node
{
	int data;
	struct node *left;
	struct node *right;
};

int main(void)
{
	struct node root;
	struct node second;
	struct node third;

	root.right = &second;
	second.left = &third;
	third.data = 3;

	printf("%d\n",root.right->left->data);
}
