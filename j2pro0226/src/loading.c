/*
 * loading.c
 *
 *  Created on: 2013/02/20
 *      Author: makoto
 * Breed Tikka ロード画面描画
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "loading.h"
#include "utils.h"

// 最初に初期化した各種デバイス
extern SDL_Event event;
extern SDL_Surface* screen;

// ロード画面の表示及びアニメーション、イベント管理
void ShowLoading(void)
{
	SDL_Surface *bg0,*bg1,*bg2,*bg3;
	SDL_Rect rect,scr_rect;

	bg0 = SDL_LoadBMP("./res/loading/loading-0.bmp");
	bg1 = SDL_LoadBMP("./res/loading/loading-1.bmp");
	bg2 = SDL_LoadBMP("./res/loading/loading-2.bmp");
	bg3 = SDL_LoadBMP("./res/loading/loading-3.bmp");

	if(bg0==NULL||
			bg1==NULL||
			bg2==NULL||
			bg3==NULL)
	{
		fprintf(stderr,"Error : Can't read Resources.\n");
	}

	Uint32 start;

	int i;
	int page = 0;
	for(i=0;i<0;i++)
	{
		page = 0;
		start = SDL_GetTicks();

		while(1)
		{
			if(page>=4) break;

			if(SDL_GetTicks()-start>=300)
			{
				page++;
				start = SDL_GetTicks();
			}

			switch(page)
			{
			case 0 :
				rect.x = 0;
				rect.y = 0;
				rect.w = bg0->w;
				rect.h = bg0->h;
				scr_rect.x = 0;
				scr_rect.y = 0;
				SDL_BlitSurface(bg0,&rect,screen,&scr_rect);
				SDL_Flip(screen);
				break;
			case 1 :
				rect.x = 0;
				rect.y = 0;
				rect.w = bg1->w;
				rect.h = bg1->h;
				scr_rect.x = 0;
				scr_rect.y = 0;
				SDL_BlitSurface(bg1,&rect,screen,&scr_rect);
				SDL_Flip(screen);
				break;
			case 2 :
				rect.x = 0;
				rect.y = 0;
				rect.w = bg2->w;
				rect.h = bg2->h;
				scr_rect.x = 0;
				scr_rect.y = 0;
				SDL_BlitSurface(bg2,&rect,screen,&scr_rect);
				SDL_Flip(screen);
				break;
			case 3:
				rect.x = 0;
				rect.y = 0;
				rect.w = bg3->w;
				rect.h = bg3->h;
				scr_rect.x = 0;
				scr_rect.y = 0;
				SDL_BlitSurface(bg3,&rect,screen,&scr_rect);
				SDL_Flip(screen);
				break;
			case 4:
				rect.x = 0;
				rect.y = 0;
				rect.w = bg0->w;
				rect.h = bg0->h;
				scr_rect.x = 0;
				scr_rect.y = 0;
				SDL_BlitSurface(bg0,&rect,screen,&scr_rect);
				SDL_Flip(screen);
				break;
			}

			SDL_PollEvent(&event);

			switch(event.type)
			{
			case SDL_QUIT :
				SDL_FreeSurface(bg0);
				SDL_FreeSurface(bg1);
				SDL_FreeSurface(bg2);
				SDL_FreeSurface(bg3);
				SDL_FreeSurface(screen);
				SDL_Quit();
				exit(0);
				break;
			}
		}
	}
}
