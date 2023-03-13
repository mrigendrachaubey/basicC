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
	sll *nde, *tmpnode;
	tmpnode = head;

	for(int i = 0; i < 5; i++)
	{
		nde = malloc(sizeof(sll));
		nde->data = 5+i;
		while(tmpnode->next != NULL)
			tmpnode = tmpnode->next;
		tmpnode->next = nde;
	}
}

void show_sll()
{
	sll *tmpnode;
	tmpnode = head;
	while (tmpnode != NULL)
	{
		printf("%d ", tmpnode->data);
		tmpnode = tmpnode->next;
	}
	printf("\n");
}

void delete_node(int node_to_delete)
{
	sll *tmpnode = head;
	sll *deletenode;
	for (int i = 1; i < node_to_delete-1;i++)
		tmpnode = tmpnode->next;
	deletenode = tmpnode->next;
	tmpnode->next = tmpnode->next->next;
	printf("deleting %d at pos %d\n", deletenode->data, node_to_delete);
	free(deletenode);
}

int main()
{
	create();
	add_node();
	show_sll();
	delete_node(3);
	show_sll();
	return 0;
}
