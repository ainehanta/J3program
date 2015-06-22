#include <stdio.h>
#include <stdlib.h>
 
struct CELL {
        int data;
        struct CELL *next;
};

struct CELL *make_node(int in_data);
void print_list(struct CELL *p);
struct CELL* search_point(int in_data,struct CELL* p);

int main(void)
{
        struct CELL *root, *p, *tmp;
        int in_data;

        root = make_node(-1);
        p = root;
		tmp = NULL;

        scanf("%d", &in_data);

        while (in_data > 0) {
				p = search_point(in_data,root);
				tmp = p->next;
				p->next = make_node(in_data);
				p->next->next = tmp;
                scanf("%d", &in_data);
        }

        print_list(root);

        return 0;
}

struct CELL *make_node(int in_data)
{
	struct CELL* node = NULL;
	node = malloc(sizeof(struct CELL));

	node->data = in_data;
	node->next = NULL;

	return node;
}

void print_list(struct CELL *p)
{
	p = p->next;
	if(p!=NULL)
	{
		printf("%-2d",p->data);
		print_list(p);
	}
	else	
	{
		printf("\n");
	}
	return;
}

struct CELL* search_point(int in_data,struct CELL* p)
{
	for(;p->next!=NULL;p=p->next)
	{
		if(p->next->data>=in_data)
		{
			break;
		}
	}

	return p;
}
