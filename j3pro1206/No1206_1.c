#include <stdio.h>
#include <string.h>

int kmp_match(const char txt[],const char pat[]);

int main(void)
{
	char text[80];
	char pat[80];

	printf("Input Text>");
	scanf("%s",text);
	printf("Input Pattern>");
	scanf("%s",pat);

	printf("Match at %d\n",kmp_match(text,pat));
}


int kmp_match(const char txt[],const char pat[])
{
	int txt_pos,pat_pos;
	int skip[256];

	txt_pos = 1;
	pat_pos = 0;

	skip[txt_pos] = 0;

	while(txt[txt_pos] != '\0')
	{
		if(pat[txt_pos] == pat[pat_pos])
		{
			skip[++txt_pos] = ++pat_pos;
		}
		else if(pat_pos == 0)
		{
			skip[++txt_pos] = pat_pos;
		}
		else
		{
			pat_pos = skip[pat_pos];
		}
	}

	txt_pos = pat_pos = 0;

	while(txt[txt_pos] != '\0' && pat[pat_pos] != '\0')
	{
		if(txt[txt_pos] == pat[pat_pos])
		{
			txt_pos++;
			pat_pos++;
		}
		else if(pat_pos == 0)
		{
			txt_pos++;
		}
		else
		{
			pat_pos = skip[pat_pos];
		}
	}

	if(pat[pat_pos] == '\0')
	{
		return txt_pos - pat_pos;
	}

	return -1;
}
