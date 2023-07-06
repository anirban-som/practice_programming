#include <stdio.h>

extern int a; //declaration. indicates that int a is defined somewhere else.

int main(void)
{
    a++;
    printf("a=[%d]\n", a);
    return 0;
}
