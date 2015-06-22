#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_MAX 100
#define NUM_MIN 1
#define TABLE_SIZE 8

int check(int table[][TABLE_SIZE]);
void print_table(int table[][TABLE_SIZE]);
void create_table(int table[][TABLE_SIZE]);
void shuffle(int* array,int size);

int main(void)
{
	srand((unsigned)time(NULL));
	int table[TABLE_SIZE][TABLE_SIZE];

	create_table(table);

	print_table(table);

	if(check(table)==0)
	{
		printf("\nBAD\n");
	}
	else
	{
		printf("\nGOOD\n");
	}
}

int check(int table[][TABLE_SIZE])
{
	int count[NUM_MAX];
	int i,j,total;

	for(i=0;i<NUM_MAX;i++)
		count[i] = 0;

	//値が適正値か判断する
	for(i=0;i<TABLE_SIZE;i++)
	{
		for(j=0;j<TABLE_SIZE;j++)
		{
			if(table[i][j]>100||table[i][j]<1)
			{
				printf("\t値が1〜100の範囲ではありません。:%d\n",table[i][j]);
				return 0;
			}
		}
	}

	//1-100まででない場合segfaultになる
	for(i=0;i<TABLE_SIZE;i++)
	{
		for(j=0;j<TABLE_SIZE;j++)
		{
			count[table[i][j]-1]++;
		}
	}

	total = 0;
	for(i=0;i<NUM_MAX;i++)
	{
		total += count[i];
	}
	if(total!=TABLE_SIZE*TABLE_SIZE)
	{
		printf("\t要素数がおかしいです。:%d\n",total);
		return 0;
	}

	for(i=0;i<NUM_MAX;i++)
	{
		if(count[i]>=2)
		{
			printf("\t同じ値が2度代入されている可能性があります。:%d\n",i+1);
			return 0;
		}
	}

	for(i=0;i<=9;i++)
	{
		if(count[70+i-1]!=1||count[i*10+7-1]!=1)
		{
			printf("\t10の位か1の位が7の数値に抜け落ちがあります。");
			return 0;
		}
	}

	if(count[13-1]!=1)
	{
		printf("\t13が代入されていません。\n");
		return 0;
	}

	return 1;
}

void create_table(int table[][TABLE_SIZE])
{
	int array[TABLE_SIZE*TABLE_SIZE];
	int mask[NUM_MAX];

	int i,j,tmp;

	for(i=0;i<NUM_MAX;i++)
		mask[i] = 0;

	i = 0;
	for(j=0;j<=9;j++)
	{
		if(mask[j*10+7-1]==0)
		{
			array[i++] = j*10 + 7;
			mask[j*10+7-1]++;
		}
	}

	for(j=0;j<=9;j++)
	{
		if(mask[70+j-1]==0)
		{
			array[i++] = 70 + j;
			mask[70+j-1]++;
		}
	}

	if(mask[13-1]==0)
	{
		array[i++] = 13;
		mask[13-1]++;
	}

	for(;i<TABLE_SIZE*TABLE_SIZE;)
	{
		tmp = rand() % NUM_MAX + NUM_MIN;
		if(mask[tmp-1]==0)
		{
			mask[tmp-1]++;
			array[i++] = tmp;
		}
	}

	shuffle(array,TABLE_SIZE*TABLE_SIZE);

	for(i=0;i<TABLE_SIZE;i++)
	{
		for(j=0;j<TABLE_SIZE;j++)
		{
			table[i][j] = array[i*8+j];
		}
	}
}

void print_table(int table[][TABLE_SIZE])
{
	int i,j;
	for(i=0;i<TABLE_SIZE;i++)
	{
		for(j=0;j<TABLE_SIZE;j++)
		{
			printf("%4d",table[i][j]);
		}
		printf("\n");
	}
}

void shuffle(int* array,int size)
{
	int i,j;
	int tmp;

	for(i=0;i<size;i++)
	{
		j = rand() % size;
		tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
}
