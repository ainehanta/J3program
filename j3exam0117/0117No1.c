#include <stdio.h>
#include <stdlib.h>

struct CELL {
	char word[20];
	int word_length;
	struct CELL *next;
};

void print_list(struct CELL *p);
void get_wl(struct CELL *p);
void decode_list(struct CELL *p, char buf2[]);

int main(void)
{
	char buf1[64] = "This is a pen.";
	char buf2[64] = "test";

	struct CELL *root;
	struct CELL *p;

	int i, j;

	root = (struct CELL *)malloc(1 * sizeof(struct CELL));
	p = root;
	p->word_length = 0;
	p->next = NULL;

	j = 0;

	for (i = 0; buf1[i] != '.'; i++) {
		if (buf1[i] != ' ') {
			p->word[j] = buf1[i];
			j++;
		} else {
			p->word[j] = '\0';
			j =0;
			p->next = (struct CELL *)malloc(1 * sizeof(struct CELL));
			p = p->next;
			p->word_length = 0;
			p->next = NULL;
		}
	}
	p->word[j] = '\0';
	get_wl(root);
	print_list(root);
	printf("buf2 = %s\n", buf2);

	return 0;
}

void print_list(struct CELL *p)
{
	for ( ; p != NULL; p = p->next) {
		printf("word = %s,length = %d\n", p->word,p->word_length);
	}
}

void get_wl(struct CELL *p)
{
  while(p!=NULL)
  {
    for(p->word_length=0;p->word[p->word_length]!='\0';p->word_length++);
    p = p->next;
  }
}

void decode_list(struct CELL *p, char buf2[])
{

}
