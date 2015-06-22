/*
 * mini-game.c
 *
 *  Created on: 2013/02/20
 *      Author: makoto
 *
 *  ミニゲーム描画関連
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "mini-game.h"
#include "utils.h"
#include "tikka.h"

extern SDL_Surface *screen;
extern TTF_Font *font;
extern SDL_Event event;

// 画面構成画像のデータ
SDL_Surface *bg;
SDL_Surface *button_g,*button_g_pressed;
SDL_Surface *button_h,*button_h_pressed;
SDL_Surface *button_j,*button_j_pressed;
SDL_Surface *note_blue,*note_green,*note_red;

// ミニゲーム内の描画処理及びイベント管理
int NavigateToMiniGame(tikka_status* tikka)
{
	mini_game status;

	SDL_Rect rect,scr_rect,button_g_rect,button_h_rect,button_j_rect;
//	SDL_Rect note_red_rect,note_blue_rect,note_green_rect;

	int ret = 0;

	bg = SDL_LoadBMP("./res/mini-game/mini-game-bg.bmp");

	button_g = SDL_LoadBMP("./res/mini-game/mini-game-button-g.bmp");
	button_g_pressed = SDL_LoadBMP("./res/mini-game/mini-game-button-g-pressed.bmp");
	button_h = SDL_LoadBMP("./res/mini-game/mini-game-button-h.bmp");
	button_h_pressed = SDL_LoadBMP("./res/mini-game/mini-game-button-h-pressed.bmp");
	button_j = SDL_LoadBMP("./res/mini-game/mini-game-button-j.bmp");
	button_j_pressed = SDL_LoadBMP("./res/mini-game/mini-game-button-j-pressed.bmp");

	note_blue = SDL_LoadBMP("./res/mini-game/mini-game-note-blue.bmp");
	note_red = SDL_LoadBMP("./res/mini-game/mini-game-note-red.bmp");
	note_green = SDL_LoadBMP("./res/mini-game/mini-game-note-green.bmp");

	if(bg==NULL||
			button_g==NULL||
			button_g_pressed==NULL||
			button_h==NULL||
			button_h_pressed==NULL||
			button_j==NULL||
			button_j_pressed==NULL||
			note_blue==NULL||
			note_red==NULL||
			note_green==NULL)
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

	CreateNotes(&status);
	DrawNotes(&status);
//	MiniGamePrintScore(status.clear_count,status.notes_count,status.exp);

	SDL_FreeSurface(bg);
	SDL_FreeSurface(button_g);
	SDL_FreeSurface(button_g_pressed);
	SDL_FreeSurface(button_h);
	SDL_FreeSurface(button_h_pressed);
	SDL_FreeSurface(button_j);
	SDL_FreeSurface(button_j_pressed);
	SDL_FreeSurface(note_blue);
	SDL_FreeSurface(note_red);
	SDL_FreeSurface(note_green);

	return status.exp;

	while(1)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
		case SDL_KEYUP :
			break;
		case SDL_QUIT :
			SDL_FreeSurface(bg);
			SDL_FreeSurface(button_g);
			SDL_FreeSurface(button_g_pressed);
			SDL_FreeSurface(button_h);
			SDL_FreeSurface(button_h_pressed);
			SDL_FreeSurface(button_j);
			SDL_FreeSurface(button_j_pressed);
			SDL_FreeSurface(note_blue);
			SDL_FreeSurface(note_red);
			SDL_FreeSurface(note_green);
			SDL_FreeSurface(screen);
			if(font!=NULL)
				TTF_CloseFont(font);
			TTF_Quit();
			SDL_Quit();
			exit(0);
			break;
		}
	}
	return ret;
}

// ミニゲームの獲得得点を表示
void MiniGamePrintScore(int clear,int count,int score)
{
	SDL_Rect score_pos;
	SDL_Color color;

	char buffer[80];

	color.r = 0;
	color.g = 0;
	color.b = 0;

	score_pos.x = 250;
	score_pos.y = 15;

	sprintf(buffer,"Notes : %d/%d",(int)clear,(int)count);
	PrintStringToSurface(buffer,screen,score_pos,color);

	score_pos.x = 250;
	score_pos.y = 40;

	sprintf(buffer,"Score : %d",(int)score);
	PrintStringToSurface(buffer,screen,score_pos,color);
}

// ノートの描画タイミングを作成
void CreateNotes(mini_game *status)
{
	static int init_flag = 0;
	if(init_flag == 0)
	{
		srand((unsigned)time(NULL));
		init_flag++;
	}

	status->notes_count = 0;

	int i;
	for(i=0;i<25;i++)
	{
		if(rand()%2)
		{
			status->notes_red[i] = 1;
			status->notes_count++;
		}
		if(rand()%2)
		{
			status->notes_blue[i] = 1;
			status->notes_count++;
		}
		if(rand()%2)
		{
			status->notes_green[i] = 1;
			status->notes_count++;
		}

		status->clear_count = 0;
		status->notes_now = 0;

		status->notes_blue_flag = 0;
		status->notes_green_flag = 0;
		status->notes_red_flag = 0;

		status->exp = 0;
	}
}

// 現在のカウントにしたがってノートを描画
void DrawNotes(mini_game *status)
{
	int time_count = 0;
	int loop_count = 0;
	SDL_Rect rect,scr_rect,note_red_rect,note_green_rect,note_blue_rect;
	SDL_Rect button_g_rect,button_h_rect,button_j_rect;

	while(loop_count<25)
	{
		time_count++;
		if(status->notes_blue_flag >= 345&&
		status->notes_green_flag >= 345&&
		status->notes_red_flag >= 345)
		{
			time_count = 0;
			status->notes_now++;
			status->notes_blue_flag = 110;
			status->notes_green_flag = 110;
			status->notes_red_flag = 110;
			loop_count++;
		}



		status->notes_blue_flag+=12;
		status->notes_green_flag+=12;
		status->notes_red_flag+=12;
		SDL_Delay(1);

		rect.x = 0;
		rect.y = 0;

		rect.w = bg->w;
		rect.h = bg->h;
		scr_rect.x = 0;
		scr_rect.y = 0;
		SDL_BlitSurface(bg,&rect,screen,&scr_rect);

		MiniGamePrintScore(status->clear_count,status->notes_count,status->exp);

//		rect.w = button_g->w;
//		rect.h = button_g->h;
//		button_g_rect.x = 190;
//		button_g_rect.y = 380;
//		SDL_BlitSurface(button_g,&rect,screen,&button_g_rect);
//
//		rect.w = button_h->w;
//		rect.h = button_h->h;
//		button_h_rect.x = 285;
//		button_h_rect.y = 380;
//		SDL_BlitSurface(button_h,&rect,screen,&button_h_rect);
//
//		rect.w = button_j->w;
//		rect.h = button_j->h;
//		button_j_rect.x = 385;
//		button_j_rect.y = 380;
//		SDL_BlitSurface(button_j,&rect,screen,&button_j_rect);

		if(status->notes_blue[status->notes_now]==1)
		{
			rect.x = 0;
			rect.y = 0;
			rect.w = note_blue->w;
			rect.h = note_blue->h;
			note_blue_rect.x = 370;
			note_blue_rect.y = status->notes_blue_flag;
			SDL_BlitSurface(note_blue,&rect,screen,&note_blue_rect);
		}

		if(status->notes_red[status->notes_now]==1)
		{
			rect.w = note_red->w;
			rect.h = note_red->h;
			note_red_rect.x = 170;
			note_red_rect.y = status->notes_red_flag;
			SDL_BlitSurface(note_red,&rect,screen,&note_red_rect);
		}

		if(status->notes_green[status->notes_now]==1)
		{
			rect.w = note_green->w;
			rect.h = note_green->h;
			note_green_rect.x = 270;
			note_green_rect.y = status->notes_green_flag;
			SDL_BlitSurface(note_green,&rect,screen,&note_green_rect);
		}

		SDL_UpdateRect(screen,0,0,0,0);
		SDL_Delay(10);

		SDL_PollEvent(&event);
		switch(event.type)
		{
		case SDL_KEYDOWN :
			switch(event.key.keysym.sym)
			{
			case SDLK_g :
				Button_g_pressed(status);
				break;
			case SDLK_h :
				Button_h_pressed(status);
				break;
			case SDLK_j :
				Button_j_pressed(status);
				break;
			case SDLK_ESCAPE :
				return;
				break;
			default :
				break;
			}
			break;
			case SDL_QUIT :
				return;
				break;
		}
	}
}

// オブジェクトのスコア判定
int CheckNoteLine(mini_game *status,int color)
{
	int ret = 0;

	if(color==NOTE_BLUE&&status->notes_blue[status->notes_now] == 1)
	{
		if(status->notes_blue_flag<300)
		{
			status->exp += 10;
			status->notes_blue[status->notes_now] = 0;
			status->clear_count++;
		}
		else if(status->notes_blue_flag==335)
		{
			status->exp += 100;
			status->notes_blue[status->notes_now] = 0;
			status->clear_count++;
		}
		else if(status->notes_blue_flag>335)
		{
			status->exp += 20;
			status->notes_blue[status->notes_now] = 0;
			status->clear_count++;
		}
		else if(status->notes_blue_flag<335)
		{
			status->exp += 50;
			status->notes_blue[status->notes_now] = 0;
			status->clear_count++;
		}
	}
	if(color==NOTE_RED&&status->notes_red[status->notes_now] == 1)
	{
		if(status->notes_red_flag<300)
		{
			status->exp += 10;
			status->notes_red[status->notes_now] = 0;
			status->clear_count++;
		}
		else if(status->notes_red_flag==335)
		{
			status->exp += 100;
			status->notes_red[status->notes_now] = 0;
			status->clear_count++;
		}
		else if(status->notes_red_flag>335)
		{
			status->exp += 20;
			status->notes_red[status->notes_now] = 0;
			status->clear_count++;
		}
		else if(status->notes_red_flag<335)
		{
			status->exp += 50;
			status->notes_red[status->notes_now] = 0;
			status->clear_count++;
		}
	}
	if(color==NOTE_GREEN&&status->notes_green[status->notes_now] == 1)
	{
		if(status->notes_green_flag<300)
		{
			status->exp += 10;
			status->notes_green[status->notes_now] = 0;
			status->clear_count++;
		}
		else if(status->notes_green_flag==335)
		{
			status->exp += 100;
			status->notes_green[status->notes_now] = 0;
			status->clear_count++;
		}
		else if(status->notes_green_flag>335)
		{
			status->exp += 20;
			status->notes_green[status->notes_now] = 0;
			status->clear_count++;
		}
		else if(status->notes_green_flag<335)
		{
			status->exp += 50;
			status->notes_green[status->notes_now] = 0;
			status->clear_count++;
		}
	}

	return ret;
}

//キーボード入力のイベントハンドラ
void Button_g_pressed(mini_game* status)
{
	CheckNoteLine(status,NOTE_RED);
}

void Button_h_pressed(mini_game* status)
{
	CheckNoteLine(status,NOTE_GREEN);
}

void Button_j_pressed(mini_game* status)
{
	CheckNoteLine(status,NOTE_BLUE);
}
