/*
 * utilus.c
 *
 *  Created on: 2013/02/21
 *      Author: makoto
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "utils.h"

timers timer;
extern TTF_Font *font;

//削除すること
void frames(void)
{
	timer.now = SDL_GetTicks();
	timer.wait = timer.now-timer.progress;

	if((int unsigned long)(timer.wait)<(int unsigned long)2)
		SDL_Delay((int unsigned long)(1-(int unsigned long)timer.wait));

	timer.progress = SDL_GetTicks();
	SDL_UpdateRect(SDL_GetVideoSurface(),0,0,0,0);
}

void FreeSurfaces(SDL_Surface **surfaces,int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		SDL_FreeSurface(surfaces[i]);
	}
}

void PrintStringToSurface(char* string,SDL_Surface* screen,SDL_Rect position,SDL_Color color)
{
	SDL_Rect rect;
	SDL_Surface* temp;

	temp = TTF_RenderUTF8_Blended(font,string,color);

	rect.x = 0;
	rect.y = 0;
	rect.w = temp->w;
	rect.h = temp->h;
	SDL_BlitSurface(temp,&rect,screen,&position);

	SDL_FreeSurface(temp);
}

void ReadAndRandomSelectMessage(char* filename,char* target)
{
	int count;
	int index;
	int i;
	char buffer[150];
	FILE* fp;

	static int init_flag = 0;
	if(init_flag==0)
	{
		init_flag++;
		srand((unsigned)time(NULL));
	}

	fp = fopen(filename,"r");

	if(fp==NULL)
	{
		fprintf(stderr,"Error : Can't open script file.\n");
		target[0] = '\0';
		return;
	}

	fscanf(fp,"%s",target);
	count = atoi(&target[1]);

	index = rand()%count+1;

	for(i=0;i<index;i++)
	{
		fscanf(fp,"%s",target);
	}

	strcpy(buffer,&target[3]);
	strcpy(target,buffer);

	printf("%s\n",target);

	fclose(fp);
}
