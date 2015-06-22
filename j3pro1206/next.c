#include <stdio.h>
#include <stdlib.h>
//自分と比較
//どれくらいずらしたら一番マッチする件数が多いか

int main(void)
{
	int i,j;
	int *next;
	int pat_length;
	int match_length;
	char pat[] = "ababb";
	char txt[] = "abababbbababcbbb";

	for(pat_length=0;pat[pat_length]!='\0';pat_length++);

	next = (int*)malloc(sizeof(int)*pat_length);

	next[0] = 1;

	for(i=1;i<pat_length;i++)
	{
		for(j=0;j+i<pat_length;j++)
		{
			if(pat[j+i]!=pat[j])
				break;
		}

		next[i] = j;
	}

	for(i=0;i<pat_length;i++)
	{
		printf("next[%d] = %d\n",i,next[i]);
	}
}
