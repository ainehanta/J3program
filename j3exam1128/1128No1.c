#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

void my_bubble_sort(int my_array[], int n);

int main(void)
{
	int my_array[SIZE];
	int i;

	srand((unsigned)time(NULL));

	for (i = 0; i < SIZE; i++) {
		my_array[i] = rand()%100;
	}

	my_bubble_sort(my_array, SIZE);

	for (i = 0; i < SIZE; i++) {
		printf("%d ", my_array[i]);
	}
	printf("\n");

	return 0;
}

void my_bubble_sort(int my_array[], int n)
{
	int i, j, t;

	for (i = 0; i < n-1; i++) {
		for (j = n -1; j > i; j--) {
			if (my_array[j - 1] < my_array[j]) {
				t = my_array[j];
				my_array[j] = my_array[j-1];
				my_array[j-1] = t;
			}
		}
	}
}
