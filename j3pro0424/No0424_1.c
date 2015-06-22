#include <stdio.h>
#include <stdlib.h>

struct node{
	char *question;
	struct node *yes;
	struct node *no;
};

void question(struct node*);

int main(void)
{
	struct node *start;
	struct node *study_like;
	struct node *test_start;
	struct node *game_like;
	struct node *own_like;
	struct node *otoge_like;
	struct node *book_like;
	struct node *otoge_start;
	struct node *next;
	struct node *loop;

	study_like = (struct node*)malloc(sizeof(struct node));
	test_start = (struct node*)malloc(sizeof(struct node));
	game_like =  (struct node*)malloc(sizeof(struct node));
	own_like =  (struct node*)malloc(sizeof(struct node));
	otoge_like =  (struct node*)malloc(sizeof(struct node));
	book_like =  (struct node*)malloc(sizeof(struct node));
	otoge_start =  (struct node*)malloc(sizeof(struct node));
	next = (struct node*)malloc(sizeof(struct node));
	loop =  (struct node*)malloc(sizeof(struct node));

	study_like->question = (char*)malloc(sizeof(char)*50);
	test_start->question = (char*)malloc(sizeof(char)*50);
	game_like->question = (char*)malloc(sizeof(char)*50);
	own_like->question = (char*)malloc(sizeof(char)*50);
	otoge_like->question = (char*)malloc(sizeof(char)*50);
	book_like->question = (char*)malloc(sizeof(char)*50);
	otoge_start->question = (char*)malloc(sizeof(char)*50);
	next->question = (char*)malloc(sizeof(char)*50);
	loop->question = (char*)malloc(sizeof(char)*50);

	strcpy(study_like->question,"�ٶ��Ϲ�����");
	strcpy(test_start->question,"�ƥ����ٶ���2���ְʾ������餹�롩");
	strcpy(game_like->question,"������Ϲ�����");
	strcpy(own_like->question,"����ʼ�ʬ����­���Ƥ롩");
	strcpy(otoge_like->question,"�������Ϲ�����");
	strcpy(book_like->question,"�ܤϹ�����");
	strcpy(otoge_start->question,"��������Ϥ�ޤ��礦");
	strcpy(next->question,"�ʵ�Ǥ��ޤ��͡�");
	strcpy(loop->question,"���Τޤޤ���αǯ���뤫��");

	study_like->yes = test_start;
	study_like->no = game_like;
	test_start->yes = own_like;
	test_start->no = game_like;
	game_like->yes = otoge_like;
	game_like->no = book_like;
	own_like->yes = next;
	own_like->no = otoge_start;
	otoge_like->yes = loop;
	otoge_like->no = book_like;
	book_like->yes = next;
	book_like->no = loop;
	otoge_start->yes = loop;
	otoge_start->no = loop;
	next->yes = NULL;
	next->no = NULL;
	loop->yes = NULL;
	loop->no = NULL;

	start = study_like;

	question(start);

	return 0;
}

void question(struct node* q)
{
	char buffer[10];

	printf("����\n");

	printf("%s\n",q->question);

	if(q->yes==NULL&&q->no==NULL)
	{
		printf("�����ޤ�\n");
		exit(0);
	}

	printf("y/n\n");
	scanf("%s",buffer);

	if(buffer[0]=='y')
	{
		question(q->yes);
	}
	else
	{
		question(q->no);
	}
}
