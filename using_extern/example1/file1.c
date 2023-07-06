#include <stdio.h>

extern int a;

int main(void)
{
    a++;
    printf("a=[%d]\n", a);
    return 0;
}
