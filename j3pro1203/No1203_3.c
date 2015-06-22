#include <stdio.h>
#include <string.h>

int my_strcmp(const char *s1,const char *s2);
int my_strncmp(const char *s1,const char *s2,int n);

int main(void)
{
	char str1[80];
	char str2[80];
	int n;

	printf("Input String1>");
	scanf("%s",str1);
	printf("Input String2>");
	scanf("%s",str2);
	printf("Compare Length>");
	scanf("%d",&n);

	printf("ref Result : %d\n",strncmp(str1,str2,n));
	printf("Result : %d\n",my_strncmp(str1,str2,n));
}

int my_strncmp(const char *s1,const char *s2,int n)
{
	int i;

	n--;
	for(i=0;s1[i]!='\0'&&i<n;i++)
	{
		if(s2[i]=='\0'||
		   s1[i]!=s2[i])
		{
			break;
		}
	}

	return s1[i]-s2[i];

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
