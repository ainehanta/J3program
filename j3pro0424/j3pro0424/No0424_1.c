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

	strcpy(study_like->question,"勉強は好き？");
	strcpy(test_start->question,"テスト勉強は2週間以上前からする？");
	strcpy(game_like->question,"ゲームは好き？");
	strcpy(own_like->question,"そんな自分に満足してる？");
	strcpy(otoge_like->question,"音ゲーは好き？");
	strcpy(book_like->question,"本は好き？");
	strcpy(otoge_start->question,"音ゲーを始めましょう");
	strcpy(next->question,"進級できますね。");
	strcpy(loop->question,"このままだと留年するかも");

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

	printf("開始\n");

	printf("%s\n",q->question);

	if(q->yes==NULL&&q->no==NULL)
	{
		printf("おしまい\n");
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
