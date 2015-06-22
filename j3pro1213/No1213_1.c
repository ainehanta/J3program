#include <stdio.h>
#include <string.h>

#define max(a,b) ((a)>(b) ? a : b)

int bf_match(const char txt[],const char pat[]);
int bm_match(const char txt[],const char pat[]);
void print_space(int num);

int main(void)
{
	char text[80];
	char pat[80];

	printf("Input Text>");
	scanf("%s",text);
	printf("Input Pattern>");
	scanf("%s",pat);

	printf("(BF)Match at %d\n",bf_match(text,pat));
	printf("(BM)Match at %d\n",bm_match(text,pat));
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
			print_space(i);
			printf("_\n");
			printf("%s\n",txt);
			print_space(i);
			printf("%s\n",pat);
			print_space(i+j);
			printf("^\n");

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

int bm_match(const char txt[],const char pat[])
{
	int i,j;
	int spot_i;
	int pat_length;
	int txt_length;

	int skip[256];

	for(pat_length=0;pat[pat_length]!='\0';pat_length++);
	for(txt_length=0;txt[txt_length]!='\0';txt_length++);

	for(i=0;i<256;i++)
	{
		skip[i] = pat_length;
	}
	for(i=0;i<pat_length-1;i++)
	{
		skip[pat[i]] = pat_length - i - 1;
	}

	for(i=pat_length-1;i < txt_length;)
	{
		spot_i = i;
		/*
		print_space(spot_i);
		printf("_\n");
		printf("%s\n",txt);
		print_space(spot_i-(pat_length-1));
		printf("%s\n",pat);
		print_space(spot_i-(pat_length-1)+j);
		printf("^\n\n");
		*/

		for(j=pat_length-1;txt[i] == pat[j];)
		{
			print_space(spot_i);
			printf("_\n");
			printf("%s\n",txt);
			print_space(spot_i-(pat_length-1));
			printf("%s\n",pat);
			print_space(spot_i-(pat_length-1)+j);
			printf("^\n\n");

			if(j == 0)
			{
				return i;
			}

			i--;
			j--;
		}
		if(i==j)
		{
			print_space(spot_i);
			printf("_\n");
			printf("%s\n",txt);
			print_space(spot_i-(pat_length-1));
			printf("%s\n",pat);
			print_space(spot_i-(pat_length-1)+j);
			printf("^\n\n");

		}
		i = i + max(skip[txt[i]],pat_length-j);
	}

	return -1;
}

void print_space(int num)
{
	for(;num>0;num--)
	{
		printf(" ");
	}
}
