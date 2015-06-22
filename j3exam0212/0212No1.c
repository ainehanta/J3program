#include <stdio.h>

int my_search(char str[], char c, int m, int n);

int main(void)
{
	char str[32];
	char c;
	char dummy;
	int m, n;

	printf("Input str : ");
	scanf("%s%c", str, &dummy);
	printf("Input c : ");
	scanf("%c%c", &c, &dummy);
	printf("Input    m : ");
	scanf("%d", &m);
	printf("Input    n : ");
	scanf("%d", &n);

	printf("result = %d\n", my_search (str, c, m, n));

	return 0;
}

int my_search(char str[], char c, int m, int n)
{
  int i;
  int tmp;

  // compare
  if(m>n)
  {
    tmp = m;
    m = n;
    n = tmp;
  }

/*
  /i/ if negative
  if(m<=0)
  {
    m = 1;
  }
  if(n<=0)
  {
    n = 1;
  }
*/

  // Convert ch position to array index
  m--;
  n--;

  for(i=m;i<n&&str[i]!='\0';i++)
  {
    if(str[i]==c)
    {
      break;
    }
  }

  // search fail
  if(str[i]!=c)
  {
    return -1;
  }

  return i;
}
