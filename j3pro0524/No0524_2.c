#include <stdio.h>
#include <stdlib.h>

struct _QUEUE_CELL
{
	struct _QUEUE_CELL *next;
	int val;
};

typedef struct
{
	struct _QUEUE_CELL *front;
	struct _QUEUE_CELL *rear;
} QUEUE;

typedef struct _QUEUE_CELL QUEUE_CELL;

int init_queue(QUEUE*);
void print_queue(QUEUE*);
int enqueue(QUEUE*,int val);
int dequeue(QUEUE*);

int print_menu(void);

int main(void)
{
	int tmp;
	QUEUE* queue = malloc(sizeof(QUEUE));
	init_queue(queue);
	
	for(;;)
	{
		tmp = print_menu();

		switch(tmp)
		{
			case 1:
				printf("Value Input>");
				scanf("%d",&tmp);
				enqueue(queue,tmp);
				printf("Enqueued:%d\n",tmp);
				break;
			case 2:
				tmp = dequeue(queue);
				printf("Dequeued:%d\n",tmp);
				break;
			case 3:
				print_queue(queue);
				break;
			case 0:
				printf("Good bye!\n");
				return 0;
				break;
			default:
				break;
		}
	}
}

int print_menu(void)
{
	int tmp;
	printf("1:enqueue,2:dequeue,3:show queue,0:quit\n");
	printf("Input>");
	scanf("%d",&tmp);
	return tmp;
}

void print_queue(QUEUE* queue)
{
	QUEUE_CELL* cell;

	if(queue->rear == queue->front)
	{
		printf("Queue is empty.\n");
		return;
	}

	printf("front >> ");

	for(cell=queue->front;cell->next!=NULL;cell=cell->next)
	{
		printf("%3d ",cell->val);
	}

	printf(">> rear\n");
}

int enqueue(QUEUE* queue,int val)
{
	queue->rear->val = val;
	queue->rear->next = malloc(sizeof(QUEUE_CELL));
	queue->rear = queue->rear->next;
	queue->rear->next = NULL;

	return 0;
}

int dequeue(QUEUE* queue)
{
	QUEUE_CELL* tmp;
	int val;

	if(queue->rear == queue->front)
	{
		printf("queue is empty.\n");
		return 0;
	}

	val = queue->front->val;
	tmp = queue->front;
	queue->front = queue->front->next;
	free(tmp);

	return val;
}

int init_queue(QUEUE* queue)
{
	queue->rear = malloc(sizeof(QUEUE_CELL));
	queue->front = queue->rear;
}
