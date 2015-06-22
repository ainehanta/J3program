#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELETE_FAIL	1
#define DELETE_OK	0

struct _node
{
	char word[20];
	int count;
	struct _node *left;
	struct _node *right;
};

typedef struct _node NODE;

NODE* save_sentence(char* str);
void create_sentence(NODE* tree,char* str);
void insert_sentence(NODE* tree,char* str);
int delete_sentence(NODE** tree,char* str);
NODE** delete_min_sentence(NODE* node);

void print_tree(NODE* tree);
void print_node(NODE* node);

NODE* clean_node(NODE* node);

int main(void)
{
	int result;
	char input_buffer[256];

	printf("Input Text>");
	gets(input_buffer);

	NODE** tree = NULL;
	tree = &save_sentence(input_buffer);
	printf("\nProcess:Complete!>%s\n",input_buffer);
	print_tree(*tree);

	for(;;)
	{
		print_tree(*tree);
		printf("Delete Sentence>");
		scanf("%s",input_buffer);
		if(strcmp(input_buffer,"Exit")==0)
		{
			break;
		}

		result = delete_sentence(tree,input_buffer);

		switch(result)
		{
		case DELETE_FAIL:
			printf("削除失敗:単語が登録されていません\n");
			break;
		case DELETE_OK:
			printf("削除完了\n");
			break;
		default:
			break;
		}
	}

	tree = clean_node(*tree);
	printf("Clean tree:Complete!\n");

	return 0;
}

void print_tree(NODE* tree)
{
	if(tree==NULL)
	{
		printf("Tree is empty.\n");
		return;
	}


	printf("Address count : word       left       right\n");
	printf("-----------------------------------------------\n");
	
	print_node(tree);

	printf("-----------------------------------------------\n");
	return;
}

void print_node(NODE* node)
{
	printf("%-10p %2d : %-10s %-10p %-10p\n",node,node->count,node->word,node->left,node->right);

	if(node->left!=NULL)
	{
		print_node(node->left);
	}
	if(node->right!=NULL)
	{
		print_node(node->right);
	}

	return;
}

NODE* clean_node(NODE* node)
{
	if(node->left!=NULL)
	{
		clean_node(node->left);
	}
	if(node->right!=NULL)
	{
		clean_node(node->right);
	}

	if(node!=NULL)
	{
		free(node);
	}

	return NULL;
}

//文を二部探索木へ
NODE* save_sentence(char* str)
{
	NODE* tree;

	char buffer[20];
	int buf_i;
	int str_i;
	int process_flag = 0;

	tree = (NODE*)malloc(sizeof(NODE));

	for(str_i=buf_i=0;str[str_i]!='\0';str_i++)
	{
		if(str[str_i]==' '||str[str_i]=='\n')
		{
			if(process_flag==0)
			{
				printf("Process Start>");
				buffer[buf_i++] = '\0';
				buf_i = 0;
				process_flag = 1;
				printf("Buffer:%s\n",buffer);
				insert_sentence(tree,buffer);
			}
			str_i++;
		}

		if(process_flag!=0)
			process_flag = 0;

		buffer[buf_i++] = str[str_i];
	}

	if(buf_i!=0)
	{
		buffer[buf_i++] = '\0';
		insert_sentence(tree,buffer);
	}

	return tree;
}

int delete_sentence(NODE** tree,char* str)
{
	NODE** min_node;
	NODE* tmp;
	int cmp_result = 0;

	while(tree != NULL)
	{
		cmp_result = strcmp(tree->word,str);
		if(cmp_result==0)
		{
			tmp = tree;
			if(tree->left==NULL&&tree->right==NULL)
			{
				tree = NULL;
			}
			else if(tree->left==NULL)
			{
				tree = tree->right;
			}
			else if(tree->right==NULL)
			{
				tree =tree->left;
			}
			else
			{
				min_node = delete_min_sentence(tree->right);
				(*min_node)->right = tmp->right;
				(*min_node)->left = tmp->left;
			}
			free(tmp);
			return DELETE_OK;
		}
		else if(cmp_result>0)
		{
			tree = tree->right;
		}
		else
		{
			tree = tree->left;
		}
	}

	return DELETE_FAIL;
}

/* 名前はdeleteだけど要素をつなぎかえるだけ */
NODE** delete_min_sentence(NODE** tree)
{
	NODE** result;

	while(tree->left!=NULL)
	{
		tree = tree->left;
	}
	result = &tree;
	tree = tree->right;
	return result;
}

void insert_sentence(NODE* tree,char* str)
{
	int cmp_res = 0;

	//ツリーのルートの時
	if(tree->count==0)
	{
		tree->count++;
		tree->left = NULL;
		tree->right = NULL;
		strcpy(tree->word,str);
		return;
	}

	//最下層に到達しているとき
	if(tree->right==NULL&&tree->left==NULL)
	{
		create_sentence(tree,str);
		return;
	}

	print_tree(tree);
	cmp_res = strcmp(tree->word,str);
	printf("CMP:%d,STR:%s,TRR:%s\n",cmp_res,str,tree->word);

	if(cmp_res==0)
	{
		tree->count++;
		return;
	}
	else if(cmp_res>0)
	{
		if(tree->left==NULL)
		{
			printf("left==NULL\n");
			create_sentence(tree,str);
			return;
		}

		tree = tree->left;
	}
	else if(cmp_res<0)
	{
		if(tree->right==NULL)
		{
			printf("right==NULL\n");
			create_sentence(tree,str);
			return;
		}

		tree = tree->right;
	}

	insert_sentence(tree,str);

	return;
}

//ツリーの最下層にノード追加
void create_sentence(NODE* tree,char* str)
{
	NODE* dest_node = NULL;
	int cmp_res = 0;

	cmp_res = strcmp(tree->word,str);

	if(cmp_res>0)
	{
		tree->left = malloc(sizeof(NODE));
		dest_node = tree->left;
	}
	else if(cmp_res<0)
	{
		tree->right = malloc(sizeof(NODE));
		dest_node = tree->right;
	}

	dest_node->right = NULL;
	dest_node->left	 = NULL;
	dest_node->count = 1;
	strcpy(dest_node->word,str);
}
