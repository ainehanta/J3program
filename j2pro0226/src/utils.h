/*
 * utils.h
 *
 *  Created on: 2013/02/21
 *      Author: makoto
 */

#ifndef UTILS_H_
#define UTILS_H_

typedef struct{
	Uint32 now;
	Uint32 wait;
	Uint32 progress;
}timers;

void frames(void);
void ReadAndRandomSelectMessage(char* filename,char* target);
void PrintStringToSurface(char*,SDL_Surface*,SDL_Rect,SDL_Color);

#endif /* UTILS_H_ */
