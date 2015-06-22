#include <stdio.h>
#include <stdlib.h>

struct CELL {
	int data;
	struct CELL *next;
	struct CELL *prev;
};

void print_list(struct CELL *p);
void cell_swap(struct CELL *p, int k);

int main(void)
{
	struct CELL head;
	struct CELL *p;
	int data;
	int k;

	head.next = head.prev = p = &head;

	scanf("%d", &data);

	while (data > 0) {
		p->next = (struct CELL*)malloc(1 * sizeof(struct CELL));
		head.prev = p->next;
		p->next->prev = p;
		p = p->next;
		p->data = data;
		scanf("%d", &data);
	}
	p->next = &head;

	print_list(&head);

	scanf("%d", &k);
	cell_swap(&head, k);
	print_list(&head);

	return 0;
}

void print_list(struct CELL *p)
{
	struct CELL *wp;

	printf("next\n");
	for (wp = p->next; wp != p; wp = wp->next) {
		printf("%d\n", wp->data);
	}

  printf("prev\n");
  for(wp = p->prev; wp != p; wp = wp->prev)
  {
    printf("%d\n",wp->data);
  }
}

void cell_swap(struct CELL *p, int k)
{
	int i;
	
	for (i = 0; i < k; i++) {
		p = p->next;
	}

	p->prev->next = p->next;
	p->next = p->next->next;
	p->prev->next->next = p;

/*
  p->next->prev = p;
  p->prev->prev = p->prev;
  p->prev = p->next->prev;
*/
  p->prev->next->prev = p->prev;
  p->next->prev = p;
  p->prev = p->prev->next;
}
