#include <stdio.h>
#include <stdlib.h>

struct word_data{
	char* word;
	struct word_data *next_left_data;
	struct word_data *next_right_data;
};

typedef struct word_data word_data_t;
typedef word_data_t* word_data_p;

void cut_string_to_words(char*,word_data_p*);
void set_left_right_to_words(word_data_p);

void preorder(word_data_p);

int main(void)
{
	word_data_p words;
	char buffer[500];

	printf("input >"); gets(buffer);
	cut_string_to_words(buffer,&words);
	set_left_right_to_words(words);
	preorder(words);

	return 0;
}

void cut_string_to_words(char* string,word_data_p* words)
{
	char* buffer;
	int string_p,buffer_p;
	word_data_p prev,tmp;

	prev = NULL;

	buffer = (char*)malloc(sizeof(char)*50);
	tmp = (word_data_p)malloc(sizeof(word_data_t));

	(*words) = tmp;

	for(string_p=0,
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
			tmp->word = buffer;
			if(prev!=NULL)
			{
				prev->next_left_data = tmp;
				prev->next_right_data = tmp;
			}
			prev = tmp;
			buffer = (char*)malloc(sizeof(char)*50);
			tmp = (word_data_p)malloc(sizeof(word_data_t));
			buffer_p = 0;
		}
	}

	buffer[buffer_p++] = '\0';
	tmp = (word_data_p)malloc(sizeof(word_data_t));
	tmp->word = buffer;
	prev->next_left_data = tmp;
	tmp->next_left_data = NULL;
	tmp->next_right_data = NULL;
}

void set_left_right_to_words(word_data_p words)
{
	if(words->next_left_data!=NULL)
	{
		if(strncmp(words->word,words->next_left_data->word,1)>0)
		{
			words->next_left_data = words->next_left_data;
			words->next_right_data = NULL;
			set_left_right_to_words(words->next_left_data);
		}
		else
		{
			words->next_right_data = words->next_left_data;
			words->next_left_data = NULL;
			set_left_right_to_words(words->next_right_data);
		}
	}
}

void preorder(word_data_p word)
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
