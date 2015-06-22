#ifndef __LIST_H_
#define __LIST_H_



#define MAX_GAKUSEI 1000
#define MAX_KAMOKU  400

struct _SEISEKI
{
	struct _SEISEKI *glink;
	struct _SEISEKI *klink;
	struct _GAKUSEI *gakusei;
	struct _KAMOKU  *kamoku;
	short seiseki;
};

struct _GAKUSEI
{
	struct _SEISEKI *glink;
	char *name;
};

struct _KAMOKU
{
	struct _SEISEKI *klink;
	char *name;
};

typedef struct _SEISEKI SEISEKI;
typedef struct _GAKUSEI GAKUSEI;
typedef struct _KAMOKU KAMOKU;

GAKUSEI gakusei[MAX_GAKUSEI];
KAMOKU  kamoku[MAX_KAMOKU];

void init(void);
void add(int x,int y,short a);
short get_seiseki(int x,int y);
void print_seiseki(int x);



#endif
