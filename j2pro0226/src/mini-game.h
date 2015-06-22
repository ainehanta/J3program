/*
 * mini-game.h
 *
 *  Created on: 2013/02/20
 *      Author: makoto
 */


#ifndef __MINI_GAME_H_
#define __MINI_GAME_H_

#include "tikka.h"

#define NOTE_RED		1
#define NOTE_GREEN	2
#define NOTE_BLUE		3

typedef struct
{
	int notes_count;
	int clear_count;
	int notes_now;
	int notes_red[25];
	int notes_green[25];
	int notes_blue[25];
	int notes_red_flag;
	int notes_green_flag;
	int notes_blue_flag;
	int exp;
}mini_game;

int NavigateToMiniGame(tikka_status*);
void MiniGamePrintScore(int,int,int);
void CreateNotes(mini_game*);
void DrawNotes(mini_game*);
int CheckNoteLine(mini_game*,int);
void Button_g_pressed(mini_game*);
void Button_h_pressed(mini_game*);
void Button_j_pressed(mini_game*);

#endif
