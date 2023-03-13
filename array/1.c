/*
sizeof int:4
diff: 1 &arr+1: 140728422198648 &arr: 140728422198636
diff: 12 &arr+1: 140728422198648 &arr: 140728422198636
diff: 1 &arr+1: 140728422198648 &arr: 140728422198636
*/
#include <stdio.h>

int main()
{
        int arr[3] = {1, 2, 3};
        long int a= &arr;
        long int b= &arr+1;
        long int *c= &arr;
        long int *d= &arr+1;
        printf("sizeof int:%d\n", sizeof(int));
        printf("diff: %ld &arr+1: %ld &arr: %ld\n", (&arr+1) - (&arr), &arr+1, &arr);
        printf("diff: %ld &arr+1: %ld &arr: %ld\n", b-a, b, a);
        printf("diff: %ld &arr+1: %ld &arr: %ld\n", d-c, d, c);
        return 0;
}
