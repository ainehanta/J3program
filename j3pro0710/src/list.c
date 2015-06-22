#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void init(void)
{
	int i;

	for(i=0;i<MAX_GAKUSEI;i++)
		gakusei[i].glink = NULL;
	for(i=0;i<MAX_KAMOKU;i++)
		kamoku[i].klink = NULL;
}

void add(int x,int y,short a)
{
	SEISEKI *p;
	p = malloc(sizeof(SEISEKI));
	p->glink = gakusei[x].glink;
	gakusei[x].glink = p;
	p->klink = kamoku[y].klink;
	kamoku[y].klink = p;
	p->gakusei = &gakuse[x];
	p->kamoku = &kamoku[y];
	p->seiseki = a;
}

short get_seiseki(int x,int y)
{
	SEISEKI *p;
	for(p=gakusei[x].glink;p!=NULL;p=p->glink)
	{
		if(p->kamoku == &kamoku[y])
			return (p->seiseki);
	}
	return -1;
}

void print_gakusei(int x)
{
	SEISEKI *p;
	for(p=kamoku[x].klink;p!=NULL;p=p->klink)
	{
		printf("%s %d\n",p->gakusei->name,p->seiseki);
	}
}

int main(void)
{
	return 0;
}
