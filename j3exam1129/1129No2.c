#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 30
#define AVARAGE_NUM 100000

int my_l_search(int my_array[], int n, int key, int *count);
void my_shuffle(int my_array[], int n);

int main(void)
{
	int my_array[SIZE];
	int i;
	int key;
	int count;

	double total_count;
	int loop_count;
	int next_loop_count;
	unsigned long seed;

	total_count = 0;
	next_loop_count = 1;
	seed = (unsigned)time(NULL);
	for(loop_count=1;loop_count<=AVARAGE_NUM;loop_count++)
	{
		srand(seed++);

		my_shuffle(my_array, SIZE);

		key = my_array[rand()%SIZE];
		count = 0;

		i = my_l_search(my_array, SIZE, key, &count);
		total_count += count;

		if(loop_count==next_loop_count)
		{
			printf("loop_count = %d\n",loop_count);
			printf("Key = %d, My_array[%d] = %d\n", key, i, my_array[i]);
			printf("Count = %d\n", count);
			printf("Avarage count = %lf\n",total_count/loop_count);
			printf("\n");
			next_loop_count *= 2;
		}
	}

	return 0;
}	

int my_l_search(int my_array[], int n, int key, int *count)
{
	int i;

	for (i = 0; i < n; i++) {
		(*count)++;
		if (my_array[i] == key) {
			return i;
		}
	}
	return -1;
}

void my_shuffle(int my_array[], int n)
{
	int i;

	for (i = 0; i < n; i++) {
		my_array[i] = rand()%100;
		//printf("%d ", my_array[i]);
	}
	//printf("\n");
}

	

	
