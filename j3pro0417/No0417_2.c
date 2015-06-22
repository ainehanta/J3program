#include <stdio.h>

void draw(int,int,int);
void line(int,int,int);
void stars(int);
void spaces(int);

int main(void)
{
	draw(0,5,7);
	return 0;
}

void draw(int space,int star,int n)
{
	if (star==0 && space>0) {
		return;
	}
	if (star>0) {
		line(space,star,n);
		printf("\n");
		draw(space+1,star-1,n);
	}
}

void line(int space,int star,int n)
{
	spaces(space); stars(star); printf(" ");
	if(n-1>0)
	{
		line(space,star,n-1);
	}
}

void stars(int n)
{
	if(n>0)
	{
		printf("*");
		stars(n-1);
	}
}

void spaces(int n)
{
	if(n>0)
	{
		printf(" ");
		spaces(n-1);
	}
}
