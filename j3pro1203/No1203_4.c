#include <stdio.h>
#include <string.h>

int bf_match(const char txt[],const char pat[]);

int main(void)
{
	char text[80];
	char pat[80];

	printf("Input Text>");
	scanf("%s",text);
	printf("Input Pattern>");
	scanf("%s",pat);

	printf("Match at %d\n",bf_match(text,pat));
}


int bf_match(const char txt[],const char pat[])
{
	int i,j;
	int pat_length;

	for(pat_length=0;pat[pat_length]!='\0';pat_length++);

	for(i=0;txt[i]!='\0';i++)
	{
		for(j=0;pat[j]!='\0'&&txt[i+j]!='\0';j++)
		{
			if(pat[j]!=txt[i+j])
			{
				break;
			}
		}
		if(j==pat_length)
		{
			return i;
		}
	}

	return -1;
}
