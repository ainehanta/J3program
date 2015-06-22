/*
 * result-day.c
 *
 *  Created on: 2013/02/20
 *      Author: makoto
 *  1日の結果表示画面
 */

#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "result-day.h"
#include "tikka.h"

// 共有デバイス
extern SDL_Surface *screen;
extern TTF_Font *font;

// 画面描画、イベント管理
void NavigateToDayResult(tikka_status* tikka)
{
	SDL_Surface *bg,*button_next;
	SDL_Surface *button_next_pressed;
	SDL_Rect rect,scr_rect,button_next_rect;
	SDL_Rect tikka_rect;

	SDL_Event event;

	int ret;

	bg = SDL_LoadBMP("./res/result-day/result-day-bg.bmp");
	button_next = SDL_LoadBMP("./res/result-day/result-day-button-next-day.bmp");
	button_next_pressed = SDL_LoadBMP("./res/result-day/result-day-button-next-day-pressed.bmp");

	if(bg==NULL||
			button_next==NULL||
			button_next_pressed==NULL)
	{
		fprintf(stderr,"Error : Can't read Resources.\n");
	}

	rect.x = 0;
	rect.y = 0;
	rect.w = bg->w;
	rect.h = bg->h;
	scr_rect.x = 0;
	scr_rect.y = 0;
	SDL_BlitSurface(bg,&rect,screen,&scr_rect);

	rect.w = button_next->w;
	rect.h = button_next->h;
	button_next_rect.x = 400;
	button_next_rect.y = 200;
	SDL_BlitSurface(button_next,&rect,screen,&button_next_rect);

	tikka_rect.x = 50;
	tikka_rect.y = 120;
	DrawTikka(tikka,tikka_rect);

	SDL_Flip(screen);

	// イベントループ
	while(1)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
		case SDL_MOUSEMOTION :
			if(event.motion.x >= button_next_rect.x && event.motion.y >= button_next_rect.y &&
					event.motion.x <= button_next_rect.x+button_next->w && event.motion.y <= button_next_rect.y+button_next->h)
			{
				rect.w = button_next->w;
				rect.h = button_next->h;
				SDL_BlitSurface(button_next_pressed,&rect,screen,&button_next_rect);
				SDL_Flip(screen);
			}
			else
			{
				rect.w = button_next->w;
				rect.h = button_next->h;
				SDL_BlitSurface(button_next,&rect,screen,&button_next_rect);
				SDL_Flip(screen);
			}
			break;
		case SDL_MOUSEBUTTONDOWN :
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				if(event.button.x >= button_next_rect.x && event.button.y >= button_next_rect.y &&
						event.button.x <= button_next_rect.x+button_next->w && event.button.y <= button_next_rect.y+button_next->h)
				{
					ret = 1;
					return;
				}
			}
			break;
		case SDL_QUIT :
			SDL_FreeSurface(bg);
			SDL_FreeSurface(button_next);
			SDL_FreeSurface(button_next_pressed);
			SDL_FreeSurface(screen);
			if(font!=NULL)
				TTF_CloseFont(font);
			TTF_Quit();
			SDL_Quit();
			exit(0);
			break;
		}
	}
	return;
}
