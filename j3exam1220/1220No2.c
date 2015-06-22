#include<stdio.h>
#include<stdlib.h>

int get_length(char run[]);
void decode(char run[], char cp[]);

int main(void)
{
	char run[32];
	char dummy;
	int length;
	char *cp;

	printf("Input run_length code : ");
	scanf("%s%c", run, &dummy);

	length = get_length(run);
	printf("length = %d\n", length);

	cp = (char*)malloc(sizeof(char)*(length+1));

	decode(run, cp);
	printf("cp = %s\n", cp);

	return 0;
} 

int get_length(char run[])
{
	int i;
	int length;

	length = 0;
	for(i=0;run[i]!='\0';i++)
	{
		if(run[i]>='0'&&run[i]<='9')
		{
			length += (run[i] - '0');
		}
	}

	return length;
}

void decode(char run[], char cp[])
{
	int i,j;
	int count;

	for(i=j=0;run[i+1]!='\0';i++)
	{
		if(run[i]>='a'&&run[i]<='z')
		{
			if(run[i+1]>='0'&&run[i+1]<='9')
			{
				for(count=0;count<(run[i+1]-'0');j++,count++)
				{
					cp[j] = run[i];
				}
			}
		}
	}
	cp[j] = '\0';
}
