#include <stdio.h>
#include <stdint.h>

typedef enum {
    false=0,
    true=1
}bool;

void showbits(uint32_t num)
{
    uint32_t i=1<<31;
    uint8_t j=0;
    /*
     * i<<31 => [1000 0000 0000 0000 0000 0000 0000 0000]
     * i=i/2 => right shift of i by one bit
     * */
    //for(i=i<<31; i>0; i=i/2) {
    printf("%u = [", num);
    while(i>0) {
        printf("%u", ((num&i)?1:0));
        i = i>>1;
        j++;
        if (j%4 == 0) {
            printf(" ");
        }
    }
    printf("]\n");
}

/*
 * toggle index'th bit(from the LSB) of a given number.
 * LSB => 0th index
 * */
uint32_t toggle_index_bit(uint32_t num, uint8_t bit_index)
{
    return(num ^ (1 << bit_index));
}


/*
 * clear bit_index bit of a given number, from the LSB.
 * LSB => 0th index
 * */
uint32_t clear_index_bit(uint32_t num, uint8_t bit_index)
{
    return(num & (~(1 << bit_index)));
}

/*
 * set bit_index bit of a given number, from the LSB.
 * LSB => 0th index
 * */
uint32_t set_index_bit(uint32_t num, uint8_t bit_index)
{
    return(num | (1 << bit_index));
}

/*
 * If we subtract a power of 2 numbers by 1 then all unset bits 
 * after the only set bit become set; and the set bit becomes unset.
 * For example for 4 ( 100) and 16(10000), we get the following after subtracting 1 
 * 3 –> 011 
 * 15 –> 01111
 *
 * So, if a number n is a power of 2 then bitwise & of n and n-1 will be zero.
 * We can say n is a power of 2 or not based on the value of n&(n-1).
 * And then to make this program for input 0, we have to add extra check like below:
 * x && (!(x & (x - 1)))
 * 
 * */

bool is_power_of_two(uint32_t num)
{
    return(num && !(num & (num-1)));
}

int main()
{
    uint32_t num1=0, num2=0;

    printf("enter the number: ");
    scanf("%d", &num1);
    showbits(num1);
    
    printf("enter which bit has to be set: ");
    scanf("%d", &num2);
    num1 = set_index_bit(num1, num2);
    showbits(num1);
    
    printf("enter which bit has to be cleared: ");
    scanf("%d", &num2);
    num1 = clear_index_bit(num1, num2);
    showbits(num1);

    printf("enter which bit has to be toggled: ");
    scanf("%d", &num2);
    num1 = toggle_index_bit(num1, num2);
    showbits(num1);

    printf("enter number to check if that is power of 2: ");
    scanf("%d", &num2);
    printf("%u is %spower of 2\n", num2, (is_power_of_two(num2)? "\0" : "NOT "));

    return 0;
}
