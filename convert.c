#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
int passed = 0;
void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);
/*int main()
{
    char bin[33];
    sub_convert(8,2,bin);
    printf("%s",bin);
} */

void div_convert(uint32_t n, int base, char *out) 
{
    // Accounting for base case
    if (n == 0)
    {
        strcpy(out,"0");
        return;
    }
    // Setting up temporary buffer
    char buffer[100];
    int pos = 0;

    // Division algorithm
    int remainder;
    while (n>0)
    {
       remainder = n % base;
       n /= base;
       
       // Converting from digit to character
       if (remainder <10)
       {
            buffer[pos] = '0' + remainder;
       }
       else
       {
            buffer[pos] = 'A' + (remainder-10);
       }
       pos++;
    }
    // Ending buffer string
    buffer[pos] = '\0';
 
    // Creating final string
    char final[65];

    // Reversing string in buffer
    int length = strlen(buffer);
    for (int i=0; i<length; i++)
    {
        final[i] = buffer[pos-(i+1)];
    }
    final[length+1] = '\0';

    // Outputting final result
    strcpy(out,final);
}
void sub_convert(uint32_t n, int base, char *out)
{
    // Handle zero case
    if (n ==0)
    {
        strcpy(out,"0");
        return;
    }
    // Final string allocation
    char final[60];
    int pos = 0;

    int exp = 0;
    int mult = 0;
    int num;

    // Subtraction algorithm
    while (pow(base,exp+1)<= n)
    {
        exp++;
    }
    do 
    {
        num = pow(base,exp);
        if (n==0)
        {
            mult = 0;
        }
        else 
        {
            while (num*(mult+1)<=n)
            {
                mult++;
            }
        }
        
        n -= num*mult;

        // Building final string
        if (mult <10)        
        {
            final[pos] = '0' + mult;
        }
        else
        {
            final[pos] = 'A' + (mult-10);
        }
        pos++;
        exp--;  
    }
    while (exp>= 0);
    final[pos] = '\0';
    strcpy(out,final);
    
    /*while (n>base)
    {
        int
        

        // Extracting each digit by subtracting multiples of powers
        while (pow(base,exp+1)<= n)
        {
            exp++;
        }
        printf("%d\n",exp);
        int num = pow(base,exp);
        while (num*(mult+1)<n)
        {
            mult++;
        }
        printf("%d\n",mult);
        n -= num*mult;
        
        
        if (mult <10)        
        {
            final[pos] = '0' + mult;
        }
        else
        {
            final[pos] = 'A' + (mult-10);
        }
        pos++;  
    }

    if (n<10)
    {
        final[pos] = '0' + n;
    }
    else
    {
        final[pos] = 'A' + (n-10);
    }
    final[pos+1] = '\0';
    strcpy(out,final); */
}
void print_tables(uint32_t n)
{
    int shift_check = n*8;
    int mask_check;
    if (n>255)
    {
        mask_check = 255;
    }
    else 
    {
        mask_check = n;
    }
    

    char bin[33], oct[12], hex[9];

    div_convert(n,2,bin);
    div_convert(n,8,oct);
    div_convert(n,16,hex);

    printf("Original: Binary=%s Octal=%s Decimal=%d Hex=%s\n", bin, oct, n, hex);

    uint32_t shift = n << 3;
    div_convert(shift,2,bin);
    div_convert(shift,8,oct);
    div_convert(shift,16,hex);
    
    printf("Left shift by 3: Binary=%s Octal=%s Decimal=%d Hex=%s\n", bin, oct, shift, hex);

    uint32_t mask = n & 0xFF;
    div_convert(mask,2,bin);
    div_convert(mask,8,oct);
    div_convert(mask,16,hex);

    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%d Hex=%s ", bin, oct, mask, hex);
    
    char result[5];
    if (mask_check == mask && shift_check == shift)
    {
        strcpy(result, "PASS");
        passed++;
    }
    else 
    {
        strcpy(result, "FAIL");
    }
    printf("[%s]\n",result);

}