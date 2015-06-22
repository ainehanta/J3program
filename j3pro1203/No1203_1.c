#include <stdio.h>

char *my_strchr(const char *s,int c);

int main(void)
{
	int i;
	char *p;
	char str[] = "Test String";
	char sstr[10];

	for(i=0;str[i]!='\0';i++)
	{
		printf("%p : %c\n",&str[i],str[i]);
	}
	printf("%p : \\0\n",&str[i]);

	sstr[0] = '\0';
	printf("Search ch>");
	scanf("%s",sstr);

	p = my_strchr(str,sstr[0]);

	if(p==NULL)
	{
		printf("Not Found.\n");
	}
	else
	{
		printf("Found %c : %p\n",*p,p);
	}

	return 0;
}

char *my_strchr(const char* s,int c)
{
	int i;
	char ch;

	i = 0;
	ch = (char)c;

	if(!s)
		return NULL;

	do
	{
		if(s[i]==ch)
			return (char *)&s[i];
	}while(s[i++]!='\0');

	return NULL;
}
