/*
   Write a C program to find out if the underlying
   architecture is little endian or big endian.
 */

#include <stdio.h>
int main()
{
    unsigned int x = 0x76543210;
    char *c = (char *)&x;

    printf("*c is: 0x%x\n", *c);
    if (*c == 0x10)
    {
        printf("Underlying architecture is little endian. \n");
    }
    else
    {
        printf("Underlying architecture is big endian. \n");
    }

    return 0;
}
/*

int x = 0x76543210;
char *c = (char*) &x;

Big endian format:
------------------
Byte address  | 0x01 | 0x02 | 0x03 | 0x04 |
              +++++++++++++++++++++++++++++
Byte content  | 0x76 | 0x54 | 0x32 | 0x10 |

Little endian format:
---------------------
Byte address  | 0x01 | 0x02 | 0x03 | 0x04 |
              +++++++++++++++++++++++++++++
Byte content  | 0x10 | 0x32 | 0x54 | 0x76 |

*/