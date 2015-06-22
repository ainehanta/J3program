/*
 * tikka.c
 *
 *  Created on: 2013/02/20
 *      Author: makoto
 */

#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "tikka.h"
#include "utils.h"
#include "serialize.h"
#include "mini-game.h"

extern SDL_Surface* screen;
extern TTF_Font *font;

int NavigateToTikka(tikka_status* tikka)
{
	int end_flag = 0;
	SDL_Surface *bg;
	SDL_Surface *button_mini_game,*button_mini_game_pressed;
	SDL_Surface *button_speak,*button_speak_pressed;
	SDL_Rect rect,scr_rect,button_mini_game_rect,button_speak_rect;
	SDL_Rect tikka_rect;

	SDL_Event event;

	bg = SDL_LoadBMP("./res/main/main-bg.bmp");

	button_mini_game = SDL_LoadBMP("./res/main/main-button-minigame.bmp");
	button_speak = SDL_LoadBMP("./res/main/main-button-speak.bmp");

	button_mini_game_pressed = SDL_LoadBMP("./res/main/main-button-minigame-pressed.bmp");
	button_speak_pressed = SDL_LoadBMP("./res/main/main-button-speak-pressed.bmp");

	if(bg==NULL||
	   button_mini_game==NULL||
	   button_speak==NULL||
	   button_mini_game_pressed==NULL||
	   button_speak_pressed==NULL)
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

	button_mini_game_rect.x = 40;
	button_mini_game_rect.y = 415;
	rect.w = button_mini_game->w;
	rect.h = button_mini_game->h;
	SDL_BlitSurface(button_mini_game,&rect,screen,&button_mini_game_rect);

	button_speak_rect.x = 230;
	button_speak_rect.y = 415;
	rect.w = button_speak->w;
	rect.h = button_speak->h;
	SDL_BlitSurface(button_speak,&rect,screen,&button_speak_rect);

	tikka_rect.x = 220;
	tikka_rect.y = 100;
	DrawTikka(tikka,tikka_rect);
	PrintExpAndHP(tikka);

	SDL_Flip(screen);

	int tikka_state = 0;
	while(1)
	{
		tikka_state = TikkaExpCheck(tikka);
		if(tikka_state==1)
		{
			end_flag = LIFE_END;
		}
		else if(tikka_state==2)
		{
			end_flag = DAY_END;
		}

		switch(end_flag)
		{
		case DAY_END :
			return DAY_END;
			break;
		case LIFE_END :
			return LIFE_END;
			break;
		}

		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_MOUSEMOTION :
				rect.w = button_mini_game->w;
				rect.h = button_mini_game->h;
				SDL_BlitSurface(button_mini_game,&rect,screen,&button_mini_game_rect);
				rect.w = button_speak->w;
				rect.h = button_speak->h;
				SDL_BlitSurface(button_speak,&rect,screen,&button_speak_rect);

				if(event.motion.x >= button_mini_game_rect.x && event.motion.y >= button_mini_game_rect.y &&
				   event.motion.x <= button_mini_game_rect.x+button_mini_game->w && event.motion.y <= button_mini_game_rect.y+button_mini_game->h)
				{
					rect.w = button_mini_game->w;
					rect.h = button_mini_game->h;
					SDL_BlitSurface(button_mini_game_pressed,&rect,screen,&button_mini_game_rect);
				}
				if(event.motion.x >= button_speak_rect.x && event.motion.y >= button_speak_rect.y &&
						event.motion.x <= button_speak_rect.x+button_speak->w && event.motion.y <= button_speak_rect.y+button_speak->h)
				{
					rect.w = button_speak->w;
					rect.h = button_speak->h;
					SDL_BlitSurface(button_speak_pressed,&rect,screen,&button_speak_rect);
				}

				SDL_Flip(screen);
				break;
			case SDL_MOUSEBUTTONDOWN :
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					if(event.button.x >= button_mini_game_rect.x && event.button.y >= button_mini_game_rect.y &&
							event.button.x <= button_mini_game_rect.x+button_mini_game->w && event.button.y <= button_mini_game_rect.y+button_mini_game->h)
					{
						//TODO : ミニゲーム関連

						int ret = 0;
						if((ret=Button_Mini_Game_Clicked(tikka))==0)
						{
							end_flag = LIFE_END;
							tikka->gen++;
							tikka->position = EGG;

							SDL_FreeSurface(bg);
							SDL_FreeSurface(button_mini_game);
							SDL_FreeSurface(button_mini_game_pressed);
							SDL_FreeSurface(button_speak);
							SDL_FreeSurface(button_speak_pressed);
							SDL_FreeSurface(SDL_GetVideoSurface());

							return LIFE_END;
						}

						tikka->ext += ret;

						rect.x = 0;
						rect.y = 0;
						rect.w = bg->w;
						rect.h = bg->h;
						scr_rect.x = 0;
						scr_rect.y = 0;
						SDL_BlitSurface(bg,&rect,screen,&scr_rect);

						button_mini_game_rect.x = 40;
						button_mini_game_rect.y = 415;
						rect.w = button_mini_game->w;
						rect.h = button_mini_game->h;
						SDL_BlitSurface(button_mini_game,&rect,screen,&button_mini_game_rect);

						button_speak_rect.x = 230;
						button_speak_rect.y = 415;
						rect.w = button_speak->w;
						rect.h = button_speak->h;
						SDL_BlitSurface(button_speak,&rect,screen,&button_speak_rect);

						tikka_rect.x = 220;
						tikka_rect.y = 100;
						DrawTikka(tikka,tikka_rect);
						PrintExpAndHP(tikka);

						SDL_Flip(screen);
						PrintExpAndHP(tikka);
						SaveTikka(tikka);
					}
					if(event.button.x >= button_speak_rect.x && event.button.y >= button_speak_rect.y &&
							event.button.x <= button_speak_rect.x+button_speak->w && event.button.y <= button_speak_rect.y+button_speak->h)
					{
						rect.x = 0;
						rect.y = 0;
						rect.w = bg->w;
						rect.h = bg->h;
						scr_rect.x = 0;
						scr_rect.y = 0;
						SDL_BlitSurface(bg,&rect,screen,&scr_rect);

						button_mini_game_rect.x = 40;
						button_mini_game_rect.y = 415;
						rect.w = button_mini_game->w;
						rect.h = button_mini_game->h;
						SDL_BlitSurface(button_mini_game,&rect,screen,&button_mini_game_rect);

						button_speak_rect.x = 230;
						button_speak_rect.y = 415;
						rect.w = button_speak->w;
						rect.h = button_speak->h;
						SDL_BlitSurface(button_speak,&rect,screen,&button_speak_rect);

						tikka_rect.x = 220;
						tikka_rect.y = 100;
						DrawTikka(tikka,tikka_rect);

						SDL_Flip(screen);
						Button_Speak_Clicked(tikka);
						PrintExpAndHP(tikka);
						SaveTikka(tikka);
					}
				}
				break;
			case SDL_QUIT :
				SDL_FreeSurface(bg);
				SDL_FreeSurface(button_mini_game);
				SDL_FreeSurface(button_mini_game_pressed);
				SDL_FreeSurface(button_speak);
				SDL_FreeSurface(button_speak_pressed);
				SDL_FreeSurface(SDL_GetVideoSurface());
				if(font!=NULL)
					TTF_CloseFont(font);
				TTF_Quit();
				SDL_Quit();
				exit(0);
				break;
			default :
				break;
		}
	}

	return 0;
}

void DrawTikka(tikka_status *tikka,SDL_Rect position)
{
	SDL_Surface* tikka_image,*tikka_image_1;
	SDL_Rect rect;

	switch(tikka->position)
	{
	case EGG :
		tikka_image = SDL_LoadBMP("./res/tikka/egg.bmp");
		break;
	case CHICK1 :
		tikka_image = SDL_LoadBMP("./res/tikka/chick-1.bmp");
		break;
	case CHICK2 :
		tikka_image = SDL_LoadBMP("./res/tikka/chick-2.bmp");
		break;
	case ADULT :
		tikka_image = SDL_LoadBMP("./res/tikka/adult.bmp");
		break;
	default :
		return;
		break;
	}

	if(tikka_image==NULL)
	{
		fprintf(stderr,"Error : Can't read Resources.\n");
		return;
	}

	rect.x = 0;
	rect.y = 0;
	rect.w = tikka_image->w;
	rect.h = tikka_image->h;

	SDL_SetColorKey(tikka_image,SDL_SRCCOLORKEY,SDL_MapRGB(tikka_image->format,0xF0,0xF0,0xF0));
	tikka_image_1 = SDL_DisplayFormat(tikka_image);

	SDL_BlitSurface(tikka_image_1,&rect,screen,&position);

	SDL_FreeSurface(tikka_image);
	SDL_FreeSurface(tikka_image_1);
}

void Button_Speak_Clicked(tikka_status* tikka)
{
	if(tikka->hp>0)
		tikka->hp--;

	SDL_Rect str_pos;
	SDL_Color color;

	char message[150];
	char filename[50];

	switch(tikka->position)
	{
	case EGG :
		strcpy(filename,"./res/tikka/egg.txt");
		break;
	case CHICK1 :
		strcpy(filename,"./res/tikka/chick-1.txt");
		break;
	case CHICK2 :
		strcpy(filename,"./res/tikka/chick-2.txt");
		break;
	case ADULT :
		strcpy(filename,"./res/tikka/adult.txt");
		break;
	}

	ReadAndRandomSelectMessage(filename,message);
	color.r = 0;
	color.g = 0;
	color.b = 0;

	str_pos.x = 50;
	str_pos.y = 330;

	tikka->ext += 10;

	PrintStringToSurface(message,screen,str_pos,color);

	SDL_Flip(screen);
}

int Button_Mini_Game_Clicked(tikka_status* tikka)
{
	if(tikka->hp>0)
		tikka->hp--;

	int ret = 0;

	ret = NavigateToMiniGame(tikka);

	return ret;
}

int TikkaExpCheck(tikka_status* tikka)
{
	if(tikka->hp>0)
	{
		if(tikka->ext>4000)
		{
			tikka->position = 1;
			tikka->ext = 0;
			tikka->gen++;
			tikka->day++;
			return 1;
		}
		if(tikka->ext>3000)
		{
			tikka->position = ADULT;
			return 0;
		}
		if(tikka->ext>2000)
		{
			tikka->position = CHICK2;
			return 0;
		}
		if(tikka->ext>1000)
		{
			tikka->position = CHICK1;
			return 0;
		}
	}
	else
	{
		return 2;
	}

	return 0;
}

void PrintExpAndHP(tikka_status* tikka)
{
	SDL_Rect hp_pos,exp_pos,day_pos;
	SDL_Color color;

	char buffer[80];

	color.r = 0;
	color.g = 0;
	color.b = 0;

	hp_pos.x = 30;
	hp_pos.y = 15;

	exp_pos.x = 500;
	exp_pos.y = 15;

	day_pos.x = 30;
	day_pos.y = 50;

	sprintf(buffer,"HP : %d/%d",(int)tikka->hp,(int)tikka->position*3);
	PrintStringToSurface(buffer,screen,hp_pos,color);

	sprintf(buffer,"Exp : %d",(int)tikka->ext);
	PrintStringToSurface(buffer,screen,exp_pos,color);

	sprintf(buffer,"Tikka%d世・%d日め",(int)tikka->gen,(int)tikka->day);
	PrintStringToSurface(buffer,screen,day_pos,color);

	SDL_Flip(screen);
}
