#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *left;
	struct node *right;
};

void preorder(struct node *p);
void inorder(struct node *p);

int main(void)
{
	struct node *root;
	
	root = (struct node *)malloc(1 * sizeof(struct node));
	root->data = 5;
	root->left = (struct node *)malloc(1 * sizeof(struct node));
	root->left->data = 3;
	root->left->left = NULL;
	root->left->right = NULL;
	root->right = (struct node *)malloc(1 * sizeof(struct node));
	root->right->data = 7;
	root->right->left =  (struct node *)malloc(1 * sizeof(struct node));
	root->right->left->data = 6;
	root->right->left->left = NULL;
	root->right->left->right = NULL;
	root->right->right = (struct node *)malloc(1 * sizeof(struct node));
	root->right->right->data = 8;
	root->right->right->left = NULL;
	root->right->right->right = NULL;

	//preorder(root);
	inorder(root);
	printf("\n");

	return 0;
}

void preorder(struct node *p)
{
	if (p == NULL) return;
	printf("%d ", p->data);
	preorder(p->left);
	preorder(p->right);
}

void inorder(struct node *p)
{
	if (p == NULL) return;
	preorder(p->left);
	printf("%d ", p->data);
	preorder(p->right);
}
