#include <stdio.h>
#include <stdlib.h>

struct CELL {
	int data;
	struct CELL *next;
};

void pirnt_list(struct CELL *r);
struct CELL *search_key(struct CELL *r, int key);

int main(void)
{
	struct CELL root;
	struct CELL *p;
	int data;
	int key;

	root.next = NULL;
	p = &root;

	printf("Input data = ");
	scanf("%d", &data);

	while (data > 0) {
		p->next = (struct CELL *)malloc(1 * sizeof(struct CELL));
		p = p->next;
		p->data = data;
		p->next = NULL;
		printf("Input data = ");
		scanf("%d", &data);
	}
	
	pirnt_list(root.next);


	printf("Input key = ");
	scanf("%d", &key);

	if(search_key(root.next,key)==NULL)
	{
		printf("Not found.\n");
	}
	else
	{
		printf("Key has been found. Address =  %p\n",search_key(root.next,key));
	}

	return 0;
}

void pirnt_list(struct CELL *r)
{
	struct CELL *p;

	for (p = r; p != NULL; p = p->next) {
		printf("Data = %d, Address = %p\n", p->data, p);
	}	
}

struct CELL *search_key(struct CELL *r, int key)
{
	struct CELL *p;

	for(p=r;p!=NULL&&p->data!=key;p=p->next);

	return p;
}
