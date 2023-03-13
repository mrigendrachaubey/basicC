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

int main()
{
	create();
	//add_node();
	//delete_node();
	//clear_sll();
	return 0;
}
