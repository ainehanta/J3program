/*
 * serialize.c
 *
 *  Created on: 2013/02/20
 *      Author: makoto
 */


#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>

#include "serialize.h"
#include "tikka.h"
#include "utils.h"

void SaveTikka(tikka_status* tikka)
{
	FILE* fp;
	fp = fopen("save.txt","w");

	if(fp==NULL)
	{
		fprintf(stderr,"Error : Can't create save file.\n");
		return;
	}

	fprintf(fp,"%d\n",tikka->ext);
	fprintf(fp,"%d\n",tikka->gen);
	fprintf(fp,"%d\n",tikka->position);
	fprintf(fp,"%d\n",tikka->day);
	fprintf(fp,"%d\n",tikka->hp);

	fclose(fp);
}

tikka_status LoadTikka(void)
{
	tikka_status tikka;
	FILE* fp;

	fp = fopen("save.txt","r");

	if(fp==NULL)
	{
		fprintf(stderr,"Error : Can't open save file.\n");
		fp = fopen("save.txt","w");
		tikka.position = 1;
		tikka.day = 1;
		tikka.ext = 0;
		tikka.gen = 1;
		tikka.hp = tikka.position*2;
		SaveTikka(&tikka);
		return tikka;
	}

	fscanf(fp,"%d",&tikka.ext);
	fscanf(fp,"%d",&tikka.gen);
	fscanf(fp,"%d",&tikka.position);
	fscanf(fp,"%d",&tikka.day);
	fscanf(fp,"%d",&tikka.hp);

	fclose(fp);

	return tikka;
}
