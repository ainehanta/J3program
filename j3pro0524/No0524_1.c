#include <stdio.h>

#define QUEUE_SIZE 10
#define next(a) (((a)+1)%QUEUE_SIZE)

int init_queue(void);
void print_queue(void);
int enqueue(int val);
int dequeue(void);

int queue[QUEUE_SIZE];
int front;
int rear;

int print_menu(void);

int main(void)
{
	int tmp;

	
	for(;;)
	{
		tmp = print_menu();

		switch(tmp)
		{
			case 1:
				printf("Value Input>");
				scanf("%d",&tmp);
				enqueue(tmp);
				printf("Enqueued:%d\n",tmp);
				break;
			case 2:
				tmp = dequeue();
				printf("Dequeued:%d\n",tmp);
				break;
			case 3:
				print_queue();
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

void print_queue(void)
{
	int i;

	printf("front = %d, rear = %d\n",front,rear);

	for(i=0;i<QUEUE_SIZE;i++)
	{
		printf("%3d",i);
	}

	printf("\n");

	for(i=0;i<QUEUE_SIZE;i++)
	{
		printf("%3d",queue[i]);
	}

	printf("\n");
}

int enqueue(int val)
{
	if(front==next(rear))
	{
		printf("queue is full.\n");
		return 1;
	}

	queue[rear] = val;
	rear = next(rear);

	return 0;
}

int dequeue(void)
{
	int val;

	if(front==rear)
	{
		printf("queue is empty.\n");
		return 0;
	}

	val = queue[front];
	front = next(front);

	return val;
}

int init_queue(void)
{
	front = rear = 0;
}
