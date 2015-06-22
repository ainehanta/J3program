#include <stdio.h>
#include <stdlib.h>

#define WORDS 10

struct word_data{
	char word[50];
	struct word_data *next_left_data;
	struct word_data *next_right_data;
};

void cut_string_to_words(char*,struct word_data*);
void set_left_right_to_words(struct word_data*);

//動かない使うな
void print_words_data(struct word_data*);

void preorder(struct word_data*);

int main(void)
{
	struct word_data words[WORDS];
	char buffer[500];

	printf("input >"); gets(buffer);
	cut_string_to_words(buffer,words);
	set_left_right_to_words(words);
//	print_words_data(words);
	preorder(&words[0]);

	return 0;
}

void cut_string_to_words(char* string,struct word_data* words)
{
	char buffer[50];
	int string_p,words_p,buffer_p;

	for(string_p=0,
		words_p=0,
		buffer_p=0;
		string[string_p]!='\0';
		string_p++)
	{
		if(string[string_p]>='a'&&string[string_p]<='z')
		{
			buffer[buffer_p++] = string[string_p];
		}
		if(string[string_p]==' ')
		{
			buffer[buffer_p++]='\0';
			strcpy(words[words_p].word,buffer);
			words_p++;
			buffer_p = 0;
		}
	}

	buffer[buffer_p++] = '\0';
	strcpy(words[words_p++].word,buffer);

	words[words_p-1].next_left_data = NULL;
	words[words_p-1].next_right_data = NULL;
}

void set_left_right_to_words(struct word_data* words)
{
	int words_p = 0;

	for(words_p=0;
		words[words_p].next_left_data!=NULL&&
		words[words_p].next_right_data!=NULL;
		words_p++)
	{
		if(strncmp(words[words_p].word,words[words_p+1].word,1)>0)
		{
			words[words_p].next_left_data = &words[words_p+1];
			words[words_p].next_right_data = NULL;
		}
		else
		{
			words[words_p].next_left_data = NULL;
			words[words_p].next_right_data = &words[words_p+1];
		}
	}
}

void print_words_data(struct word_data* words)
{
	int words_p;

	for(words_p=0;
		words[words_p].next_left_data!=NULL&&
		words[words_p].next_right_data!=NULL;
		words_p++)
	{
		printf("word:%s left:%p right:%p\n",
			words[words_p].word,
			words[words_p].next_left_data,
			words[words_p].next_right_data);
	}
}

void preorder(struct word_data* word)
{
	printf("word:%s addr:%p left:%p right:%p\n",
			word->word,
			word,
			word->next_left_data,
			word->next_right_data);

	if(word->next_left_data==NULL&&
	   word->next_right_data==NULL)
	{
		return;
	}

	if(word->next_right_data==NULL)
	{
		preorder(word->next_left_data);
	}
	else
	{
		preorder(word->next_right_data);
	}
}
