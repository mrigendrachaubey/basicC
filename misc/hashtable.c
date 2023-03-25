#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person *)(0xFFFFFFFFFFFFFFFFUL)

typedef struct
{
    char name[MAX_NAME];
    int age;
} person;

person *hash_table[TABLE_SIZE];

void init_hash_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
        hash_table[i] = NULL;
}

unsigned int hash(char *name)
{
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += name[i];
        // printf("%u %c\n", name[i], name[i]);
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    // printf("name %s hash_value %d\n", name, hash_value);
    return hash_value;
}

bool insert_hash_table(person *p)
{
    if (p == NULL)
        return false;
    int index = hash(p->name);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL)
        {
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

person *hash_table_lookup(char *name)
{
    int index = hash(name);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (index + i) % TABLE_SIZE;
        if ((hash_table[try] != NULL) && (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0))
        {
            return hash_table[try];
        }
    }
    return NULL;
}

person *hash_table_delete(char *name)
{
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (index + i) % TABLE_SIZE;
        if ((hash_table[try] != NULL) && (strncmp(hash_table[try]->name, name, TABLE_SIZE) == 0))
        {
            person *tmp = hash_table[try];
            // printf("%d\n", try);
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    }
}

void print_table()
{
    printf("START\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
            printf("\t%i\t----\n", i);
        else if (hash_table[i] == DELETED_NODE)
            printf("\t%d\t<deleted>\n", i);
        else
            printf("\t%d\t%s\n", i, hash_table[i]->name);
    }
    printf("END\n");
}

int main(void)
{
    init_hash_table();
    print_table();

    person Jacob = {.name = "Jacob", .age = 21};
    person Kate = {.name = "Kate", .age = 22};
    person Mpho = {.name = "Mpho", .age = 23};
    person Sarah = {.name = "Sarah", .age = 24};
    person Edna = {.name = "Edna", .age = 24};
    person Maren = {.name = "Maren", .age = 25};
    person Eliza = {.name = "Eliza", .age = 26};
    person Robert = {.name = "Robert", .age = 27};
    person Jane = {.name = "Jane", .age = 28};
    person David = {.name = "David", .age = 29};

    printf("result %d\n", insert_hash_table(&Jacob));
    printf("result %d\n", insert_hash_table(&Kate));
    printf("result %d\n", insert_hash_table(&Mpho));
    printf("result %d\n", insert_hash_table(&Sarah));
    printf("result %d\n", insert_hash_table(&Edna));
    printf("result %d\n", insert_hash_table(&Maren));
    printf("result %d\n", insert_hash_table(&Eliza));
    printf("result %d\n", insert_hash_table(&Robert));
    printf("result %d\n", insert_hash_table(&Jane));
    printf("result %d\n", insert_hash_table(&David));

    print_table();

    // lookup for a name
    person *tmp = hash_table_lookup("Mpho");
    if (tmp != NULL)
        printf("Mpho found\n");
    else
        printf("Mpho Not found\n");
    tmp = hash_table_lookup("Nikhil");
    if (tmp != NULL)
        printf("Nikhil found\n");
    else
        printf("Nikhil Not found\n");

    hash_table_delete("Mpho");
    hash_table_delete("Robert");
    print_table();
    // printf("%d\n", hash())
    return 0;
}