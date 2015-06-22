#include <stdio.h>

int string_length(char*);

int main(void)
{
	char buffer[80];
	int length = 0;

	printf("input >"); scanf("%s",buffer);
	length = string_length(buffer);

	printf("length:%d\n",length);

	return 0;
}

int string_length(char* string)
{
	if(string[0]!='\0')
	{
		string++;
		return string_length(string)+1;
	}
	else
	{
		return 0;
	}
}
