#include <stdio.h>
#include <string.h>

int my_strcmp(const char *s1,const char *s2);

int main(void)
{
	char str1[80];
	char str2[80];

	printf("Input String1>");
	scanf("%s",str1);
	printf("Input String2>");
	scanf("%s",str2);

	printf("ref Result : %d\n",strcmp(str1,str2));
	printf("Result : %d\n",my_strcmp(str1,str2));
}

int my_strcmp(const char *s1,const char *s2)
{
	int i;

	for(i=0;s1[i]!='\0';i++)
	{
		if(s2[i]=='\0'||
		   s1[i]!=s2[i])
		{
			break;
		}
	}

	return s1[i]-s2[i];
}
