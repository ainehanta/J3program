/*
 * main.c
 *
 *  Created on: 2013/02/20
 *      Author: makoto
 *
 * Breed Tikkaメインファイル
 * SDLの初期化及びゲームシーンの管理、終了処理
 */

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "title.h"
#include "loading.h"
#include "tikka.h"
#include "utils.h"
#include "result-day.h"
#include "result-life.h"
#include "mini-game.h"
#include "serialize.h"

// ゲーム内で共有する各種デバイス
SDL_Surface *screen;
SDL_Event event;
TTF_Font *font;

int main(int argc,char *argv[])
{
	tikka_status tikka;

	// SDLの初期化
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTTHREAD|SDL_INIT_TIMER)!=0)
	{
		fprintf(stderr,"Unable to init SDL:%s\n",SDL_GetError());
		exit(1);
	}

	// SDLスクリーンの取得
	screen = SDL_SetVideoMode(640,480,16,SDL_SWSURFACE);
	if(screen == NULL)
	{
		fprintf(stderr,"Unable to set 640x480 video:%s\n",SDL_GetError());
		exit(1);
	}

	// フォントライブラリの初期化
	if(TTF_Init() != 0)
	{
		fprintf(stderr,"Unable to init ttf:%s\n",SDL_GetError());
		exit(1);
	}

	// フォントをオープン
	font = TTF_OpenFont("./res/YomogiFont.ttf",24);

	// タイトル画面へ遷移
	NavigateToTitle();
	ShowLoading();
	tikka.position = 1;
	tikka.day = 1;
	tikka.ext = 0;
	tikka.gen = 1;
	tikka.hp = tikka.position*2;

	// セーブデータの読み出し
	tikka = LoadTikka();

	// シーンマネージメント
	int tikka_ret = 1;
	for(;;)
	{
		tikka_ret = NavigateToTikka(&tikka);
		if(tikka_ret==0)
		{
			fprintf(stderr,"Unknown Error.\n");
			break;
		}
		else if(tikka_ret==DAY_END)
		{
			NavigateToDayResult(&tikka);
			tikka.day++;
			tikka.hp = tikka.position*3;
			SaveTikka(&tikka);
		}
		else if(tikka_ret==LIFE_END)
		{
			NavigateToLifeResult(&tikka);
			tikka.position = EGG;
			tikka.hp = tikka.position*3;
		}
		else
		{
			fprintf(stderr,"Unknown Error.\n");
			break;
		}
	}

	// イベントループ
	while(1)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				if(screen!=NULL)
				SDL_FreeSurface(SDL_GetVideoSurface());
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
