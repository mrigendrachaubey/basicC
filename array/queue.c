#include <stdio.h>

int rear=-1, front=-1;

int arr[10];


void enqueue(int value)
{
	if(rear < 10)
	{
		rear = rear+1;
		arr[rear] = value;
	}
}

void dequeue()
{
	front = front+1;
	arr[front] = 0;
}

void showqueue()
{
	for(int i =0; i <= rear; i++)
		printf("%d", arr[i]);
	printf("\n");
}

int main()
{
	enqueue(1);
	enqueue(2);
	enqueue(3);
	enqueue(4);
	enqueue(5);
	showqueue();
	dequeue();
	dequeue();
	showqueue();
	return 0;
}
