#include <stdio.h>

void my_strcpy(char str1[], char str2[], int n);

int main(void)
{
	char str1[32];
	char str2[32];
	char dummy;
	int n;

	printf("Input str1 : ");
	scanf("%s%c", str1, &dummy);
	printf("Input str2 : ");
	scanf("%s%c", str2, &dummy);
	printf("Input    n : ");
	scanf("%d", &n);

	my_strcpy(str1, str2, n);

	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);

	return 0;
}

void my_strcpy(char str1[], char str2[], int n)
{
	int i;

	if(n==0)
	{
		str2[0] = '\0';
		return;
	}

	for(i=0;i<n;i++)
	{
		str2[i] = str1[i];
	}
	str2[i] = '\0';
}
