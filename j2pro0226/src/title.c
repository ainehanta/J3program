/*
 * title.c
 *
 *  Created on: 2013/02/20
 *      Author: makoto
 */


#include "title.h"
#include "utils.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

extern SDL_Surface* screen;
extern TTF_Font *font;

int NavigateToTitle(void)
{
	SDL_Surface *bg,*button_start,*button_setting;
	SDL_Surface *button_start_pressed,*button_setting_pressed;
	SDL_Rect rect,scr_rect,button_start_rect,button_setting_rect;

	SDL_Event event;

	int ret;

	bg = SDL_LoadBMP("./res/title/title-bg.bmp");
	button_start = SDL_LoadBMP("./res/title/title-button-start.bmp");
	button_setting = SDL_LoadBMP("./res/title/title-button-setting.bmp");
	button_start_pressed = SDL_LoadBMP("./res/title/title-button-start-selected.bmp");
	button_setting_pressed = SDL_LoadBMP("./res/title/title-button-setting-selected.bmp");

	if(bg==NULL||
	   button_start==NULL||
	   button_setting==NULL||
	   button_start_pressed==NULL||
	   button_setting_pressed==NULL)
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

	button_start_rect.x = 300;
	button_start_rect.y = 250;
	rect.w = button_start->w;
	rect.h = button_start->h;
	SDL_BlitSurface(button_start,&rect,screen,&button_start_rect);

	button_setting_rect.x = 300;
	button_setting_rect.y = 300;
	rect.w = button_setting->w;
	rect.h = button_setting->h;
//	SDL_BlitSurface(button_setting,&rect,screen,&button_setting_rect);

	SDL_Flip(screen);

	while(1)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_MOUSEMOTION :
				if(event.motion.x >= button_start_rect.x && event.motion.y >= button_start_rect.y &&
				   event.motion.x <= button_start_rect.x+button_start->w && event.motion.y <= button_start_rect.y+button_start->h)
				{
					rect.w = button_start->w;
					rect.h = button_start->h;
					SDL_BlitSurface(button_start_pressed,&rect,screen,&button_start_rect);
					SDL_Flip(screen);
				}
				else
				{
					rect.w = button_start->w;
					rect.h = button_start->h;
					SDL_BlitSurface(button_start,&rect,screen,&button_start_rect);
					SDL_Flip(screen);
				}
				break;
			case SDL_MOUSEBUTTONDOWN :
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					if(event.button.x >= button_start_rect.x && event.button.y >= button_start_rect.y &&
					   event.button.x <= button_start_rect.x+button_start->w && event.button.y <= button_start_rect.y+button_start->h)
					{
						ret = 1;
						return ret;
					}
				}
				break;
			case SDL_QUIT :
				SDL_FreeSurface(bg);
				SDL_FreeSurface(button_setting);
				SDL_FreeSurface(button_setting_pressed);
				SDL_FreeSurface(button_start);
				SDL_FreeSurface(button_start_pressed);
				SDL_FreeSurface(screen);
				if(font!=NULL)
					TTF_CloseFont(font);
				TTF_Quit();
				SDL_Quit();
				exit(0);
				break;
		}
	}
	return 0;
}
