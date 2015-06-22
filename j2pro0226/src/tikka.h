/*
 * tikka.h
 *
 *  Created on: 2013/02/20
 *      Author: makoto
 */
#ifndef _TIKKA_H
#define _TIKKA_H

#define EGG		1
#define CHICK1	2
#define CHICK2	3
#define ADULT		4
#define DEAD		5

#define DAY_END	1
#define LIFE_END	2

typedef struct
		{
			int ext;		//経験値
			int gen;		//世代
			int position;	//現在の成長過程
			int day;
			int hp;
		}
tikka_status;

int NavigateToTikka(tikka_status*);
void DrawTikka(tikka_status*,SDL_Rect);
void Button_Speak_Clicked(tikka_status*);
int Button_Mini_Game_Clicked(tikka_status*);
int TikkaExpCheck(tikka_status*);
void PrintExpAndHP(tikka_status*);

#endif
