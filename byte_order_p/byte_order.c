#include <stdio.h>
#include <stdint.h>

void print_bits_16(uint16_t num)
{
    uint16_t a=0x8000; /*[1000 0000 0000 0000]*/
    uint8_t i=0;
    printf("bit representation = [");
    for (i=0; i<16; i++) {
        printf("%u", ((a&num)?1:0));
        if (((i+1)%4) == 0) {
            printf(" ");
        } 
        a = a>>1;
    }
    printf("]\n");
}

int main()
{
    uint16_t a=37733; /*[1001 0011 0110 0101]*/
    uint8_t *ptr=(uint8_t *)&a;
    uint16_t x=0,y=0;

    printf("a=[%u]\n", a);
    print_bits_16(a);

    x = ((uint16_t)*((const uint8_t *)(ptr) + 0) << 8);
    //printf("x=[%u]\n", x);
    //print_bits_16(x);

    y = ((uint16_t)*((const uint8_t *)(ptr) + 1) << 0); 
    //printf("y=[%u]\n", y);
    //print_bits_16(y);

    a = x | y;
    printf("After byte swap, a=[%u]:\n", a);
    print_bits_16(a);

    return 0;
}
