#include <stdio.h>

#define QUEUE_SIZE 3

#define ENQUEUE 0
#define DEQUEUE 1
#define END 2

#define next(a) ((a+1) % QUEUE_SIZE)

void init(int *front, int *rear,int *flag);
void enqueue(int data, int front, int *rear, int queue[],int *flag);
int dequeue(int *front, int rear, int queue[],int *flag);
int empty(int front, int rear,int flag);
void print_queue(int front, int rear, int queue[],int flag);
void print_menu(int *action);

void init(int *front, int *rear,int *flag)
{
	*front = 0;
	*rear = 0;
	*flag = 0;
}

void enqueue(int data, int front, int *rear, int queue[],int *flag)
{
	queue[*rear] = data;
	*rear = next(*rear);
	if(*rear==front)
	{
		*flag = 1;
	}
}

int dequeue(int *front, int rear, int queue[],int *flag)
{
	int data = queue[*front];
	*front = next(*front);
	if(*front != rear)
	{
		*flag = 0;
	}
	return data;
}

int empty(int front, int rear,int flag)
{
	return (front == rear)&&(flag == 0);
}

void print_queue(int front, int rear, int queue[],int flag)
{
	int i;
	int tmp;

	if (empty(front, rear, flag)) {
		printf("Queue is empty.\n");
	} else {
		printf("Queue has data.\n");
		printf("Queue =");
		if (rear > front) {
			tmp = rear;
		} else {
			tmp = rear + QUEUE_SIZE;
		}
		for (i = front; i < tmp; i++) {
			printf(" %d", queue[ i % QUEUE_SIZE ]);
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

int main(void)
{
	int queue[QUEUE_SIZE];
	int front, rear;
	int data;
	int action;
	int flag;

	init(&front, &rear, &flag);
	
	print_menu(&action);

	while (action != END) {

		switch (action) {
			case ENQUEUE:
				data = rand()%10;
				if ( flag ) {
					printf("Queue is full, so you can't store the data.\n");
				} else {
					enqueue(data, front, &rear, queue, &flag);
					printf("%d has been enqueued.\n",data);
				}
				break;
			case DEQUEUE:
				if ( empty(front, rear, flag) ) {
					printf("Queue is empty, so you can't take the data.\n");
				} else {
					data = dequeue(&front, rear, queue, &flag);
					printf("%d has been dequeued.\n", data);
				}
				break;
			default:
				break;
		}

		printf("front = %d, rear = %d, flag = %d\n", front, rear, flag);

		print_queue(front, rear, queue, flag);
		
		print_menu(&action);
	}

	return 0;
}
