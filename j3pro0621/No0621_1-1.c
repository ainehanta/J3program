#include <stdio.h>
#include <stdlib.h>

#define ENQUEUE 0
#define DEQUEUE 1
#define END 2

struct cell {
	int data;
	struct cell *next;
};

struct cell *enqueue(int data, struct cell *front, struct cell *rear);
struct cell *dequeue(struct cell *front, struct cell *rear, int *data);
void print_menu(int *action);
void print_queue(struct cell *wp);


int main(void)
{
	int data;
	int action;
	struct cell *front;
	struct cell *rear;

	front = NULL;
	rear = front;

	print_menu(&action);

	while (action != END) {

		switch (action) {
			case ENQUEUE:
				data = rand()%10;
				rear = enqueue(data, front, rear);
				if(!front)
				{
					front = rear;
				}
				printf("%d has been enqueued.\n",data);
				break;
			case DEQUEUE:
				if ( !front ) {
					printf("Queue is empty, so you can't take the data.\n");
				} else if(front == rear) {
					dequeue(front,rear,&data);
					front = NULL;
				} else {
					front = dequeue(front, rear, &data);
					printf("%d has been dequeued.\n", data);
				}
				break;
			default:
				break;
		}

		print_queue(front);
		
		print_menu(&action);
	}


	return 0;
}

struct cell *enqueue(int data, struct cell *front, struct cell *rear)
{
	if(!rear)
	{
		rear = (struct cell*)malloc(sizeof(struct cell));
	}
	rear->next = (struct cell *)malloc(sizeof(struct cell));
	rear->data = data;
	rear->next->next = NULL;
	return rear->next;
}

struct cell *dequeue(struct cell *front, struct cell *rear, int *data)
{
	struct cell *next;
	*data = front->data;
	next = front->next;
	free(front);
	return next;
}

void print_queue(struct cell *wp)
{
	if (!wp->next)  {
		printf("Queue is empty!\n");
	} else {
		printf("Queue =");
		for ( ; wp->next; wp = wp->next) {
			printf(" %d", wp->data);
		}
		printf("\n");
	}
}

void print_menu(int *action)
{
	printf("\n------------------------------\n");
	printf("MENU\n");
	printf("0: Enqueue, 1: Dequeue, 2: End\n"); 
	printf("------------------------------\n");
	printf("Input number: ");
	scanf("%d", action);
	printf("\n");
}
