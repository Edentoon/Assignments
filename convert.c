#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

void div_convert(uint32_t n, int base, char *out);
void sub_convert(uint32_t n, int base, char *out);
void print_tables(uint32_t n);

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

    // Subtraction algorithm
    while (n>base)
    {
        int exp = 0;
        int mult = 1;
        

        // Extracting each digit by subtracting multiples of powers
        while (pow(base,exp+1)< n)
        {
            exp++;
        }
        int num = pow(base,exp);
        while (num*(mult+1)<n)
        {
            mult++;
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
    strcpy(out,final);
}
void print_tables(uint32_t n)
{
    FILE *output = fopen("output.txt","a");
    char masked[33];
    char shifted[33];
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
    sprintf(masked,"%d",mask_check);
    sprintf(shifted,"%d",shift_check);

    char bin[33], oct[12], hex[9];

    div_convert(n,2,bin);
    div_convert(n,8,oct);
    div_convert(n,16,hex);

    fprintf(output,"Original: Binary=%s Octal=%s Decimal=%d Hex=%s\n", bin, oct, n, hex);

    uint32_t shift = n << 3;
    div_convert(shift,2,bin);
    div_convert(shift,8,oct);
    div_convert(shift,16,hex);
    
    fprintf(output,"Left shift by 3: Binary=%s Octal=%s Decimal=%d Hex=%s\n", bin, oct, shift, hex);

    uint32_t mask = n & 0xFF;
    div_convert(mask,2,bin);
    div_convert(mask,8,oct);
    div_convert(mask,16,hex);

    fprintf(output,"AND with 0xFF: Binary=%s Octal=%s Decimal=%d Hex=%s ", bin, oct, mask, hex);
    
    char result[4];
    if (masked == mask && shifted == shift)
    {
        strcpy(result, "PASS");
        passed++;
    }
    else 
    {
        strcpy(result, "FAIL");
    }
    fprintf(output, "[%s]\n",result);
    fclose(output);

}