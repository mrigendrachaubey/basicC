#include <stdio.h>

int Addition(int a, int b)
{
    int c = a + b;
    return c;
}

void show_num(int a)
{
    printf("show_num %d\n", a);
}

int main()
{
    int a, b;
    int (*IP) (int, int);
    void (*p)(int);
    printf("Enter Two Numbers : ");
    scanf ("%d %d", &a, &b);
    IP = Addition;
    p = show_num;
    int result = (*IP) (a, b);
    (*p)(a);
    printf("Result  : %d\n", result);
    return 0;
}


