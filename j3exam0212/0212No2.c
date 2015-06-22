#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	char word[20];
	int word_length;
	struct node *left;
	struct node *right;
};

struct node *make_binary_search_tree(char str[]);
struct node *insert_node(struct node *p, char word[]);
void print_tree_inorder(struct node *p);

void print_tree_postorder(struct node *p);
void get_wl(struct node *p);

int main(void)
{
	char str[] = "this is an apple for us.";
	struct node *root = NULL;

	root = make_binary_search_tree(str);
	print_tree_inorder(root);
	print_tree_postorder(root);
	get_wl(root);
	print_tree_inorder(root);
	print_tree_postorder(root);

	return 0;
}

struct node *make_binary_search_tree(char str[])
{
	int i, j;
	char word[20];

	struct node *root = NULL;
	
	j = 0;
	for (i = 0; str[i] != '\0'; i++) {
		if ((str[i] != ' ') &&(str[i] != '.')) {
			word[j++] = str[i];
		} else {
			word[j] = '\0';
			j = 0;	
			root = insert_node(root, word);
		}
	}
	
	return root;
}

struct node *insert_node(struct node *p, char word[])
{
	if (p == NULL) {
		p = (struct node *)malloc(1 * sizeof(struct node));
		strcpy(p->word, word);
		p->word_length = 0;
		p->left = NULL;
		p->right = NULL;
	} else {
		if (strcmp(p->word, word) > 0) {
			p->left = insert_node(p->left, word);
		} else {
			p->right = insert_node(p->right, word);
		}
	}
	return p;
}

void print_tree_inorder(struct node *p)
{
	if (p != NULL) {
		print_tree_inorder(p->left);
		printf("%s %d\n", p->word, p->word_length);
		print_tree_inorder(p->right);
	}
}

void print_tree_postorder(struct node *p)
{
  if(p == NULL)
    return;
  print_tree_postorder(p->left);
  print_tree_postorder(p->right);
  printf("%s %d\n",p->word, p->word_length);
}

void get_wl(struct node *p)
{
  if(p == NULL)
    return;
  get_wl(p->left);
  get_wl(p->right);

  p-> word_length = strlen(p->word);
}



