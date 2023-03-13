#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};
typedef struct node sll;
sll *head;

void create()
{
	head = malloc(sizeof(sll));
	head->data = 4;
	head->next = NULL;
}

void add_node()
{
	sll *newnode, *tmpnode;
	tmpnode = head;
	newnode = malloc(sizeof(sll));
	newnode->data = 5;
	while(tmpnode->next != NULL)
		tmpnode = tmpnode->next;
	tmpnode->next = newnode;
	newnode->next = NULL;
}

int main()
{
	create();
	add_node();
	return 0;
}