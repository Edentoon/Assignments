#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
// Global variable for passed tests
int passed = 0;

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
    final[length] = '\0';

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

    uint64_t exp = 0;
    uint64_t mult = 0;
    uint64_t num;

    // Subtraction algorithm
    while (pow(base,exp+1)<= n)
    {
        exp++;
    }

    do 
    {
        num = pow(base,exp);
        
        while (num*(mult+1)<=n)
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
        if (exp == 0)
        {
            break;
        }
        exp--;
        mult=0;  
    }
    while (exp>= 0);

    // Finishing string
    final[pos] = '\0';
    strcpy(out,final);
}

void print_tables(uint32_t n)
{
    // Mathematical tests for bit operations
    uint32_t shift_check = n*8;
    uint32_t mask_check;

    if (n>255)
    {
        mask_check = 255;
    }
    else 
    {
        mask_check = n;
    }
    
    char bin[50], oct[12], hex[9];

    div_convert(n,2,bin);
    div_convert(n,8,oct);
    div_convert(n,16,hex);

    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);

    uint32_t shift = n << 3;
    div_convert(shift,2,bin);
    div_convert(shift,8,oct);
    div_convert(shift,16,hex);
    
    printf("Left shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, shift, hex);

    uint32_t mask = n & 0xFF;
    div_convert(mask,2,bin);
    div_convert(mask,8,oct);
    div_convert(mask,16,hex);

    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, mask, hex);
    
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

void oct_to_bin(const char *oct, char *out)
{
    int i = 0;
    int pos = 0;
    char buffer[100];

    // Comparing each bit shift to one to convert
    while (oct[i] != '\0')
    {
        int oct_dig = oct[i] - '0';
        buffer[pos] = (oct_dig >> 2) & 1 ? '1':'0';
        pos++;
        buffer[pos] = (oct_dig >> 1) & 1 ? '1':'0';
        pos++;
        buffer[pos] = (oct_dig >> 0) & 1 ? '1':'0';
        pos++;
        i++;
    }
    buffer[pos] = '\0';
    strcpy(out,buffer);
}

void oct_to_hex(const char *oct, char *out)
{
    int i=0; 
    int pos = 0;
    char buffer[100];

    // Converting to binary first
    while (oct[i] != '\0')
    {
        int oct_dig = oct[i] - '0';
        buffer[pos] = (oct_dig >> 2) & 1 ? '1':'0';
        pos++;
        buffer[pos] = (oct_dig >> 1) & 1 ? '1':'0';
        pos++;
        buffer[pos] = (oct_dig >> 0) & 1 ? '1':'0';
        pos++;
        i++;
    }
    buffer[pos] = '\0';
    int index = strlen(buffer)-1;

    // Resetting position
    pos=0;

    char reverse[100];

    // Converting binary to hex
    while (index >= 0)
    {
        double exp;
        int dig = 0;

        // Converting each binary nibble to decimal
        for (int i = 0;i<4;i++)
        {
            if (index <0)
            {
                break;
            }
            if (buffer[index] == '1')
            {
                exp = pow(2,i);
                dig += exp;
            }
            index--;
        }

        // Converting decimal to hex
        if (dig <10)
        {
            reverse[pos] = '0' + dig;
        }
        else 
        {
            reverse[pos] = 'A' + (dig-10);
        }
        pos++;
    }
    reverse[pos] = '\0';
    
    // Reversing string
    int length = strlen(reverse);
    for (int i=0; i<length; i++)
    {
        out[i] = reverse[pos-(i+1)];
    }
    out[length] = '\0';
}

void hex_to_bin(const char *hex, char *out)
{
    int i = 0;
    int pos = 0;
    char buffer[100];
    int hex_dig;

    while (hex[i] != '\0')
    {

        // Upper, lower, or decimal check and converting into digit
        if (hex[i] >= 'a')
        {
            hex_dig = 10 + (hex[i] - 'a');
        }
        else if (hex[i] >= 'A')
        {
            hex_dig = 10 + (hex[i] - 'A');
        }
        else 
        {
            hex_dig = hex[i] - '0';
        }
        
        // Converting by comparing each shift to one
        buffer[pos] = (hex_dig >> 3) & 1 ? '1':'0';
        pos++;
        buffer[pos] = (hex_dig >> 2) & 1 ? '1':'0';
        pos++;
        buffer[pos] = (hex_dig >> 1) & 1 ? '1':'0';
        pos++;
        buffer[pos] = (hex_dig >> 0) & 1 ? '1':'0';
        pos++;
        i++;
    }
    buffer[pos] = '\0';
    strcpy(out,buffer);
}

void to_sign_magnitude(int num, char *out)
{
    int i = 0;

    // Changing to positive if negative and setting first bit
    if (num<0)
    {
        num*= -1;
        out[0] = '1';
    }
    else 
    {
        out[0]= '0';
    }

    // Converting from binary digits to chars
    for (i; i<32; i++)
    {
        out[i+1] = (num >> 30-i) & 1 ? '1':'0';
    }
    out[i++] = '\0';
}

void to_ones_complement(int num, char *out)
{
    int i = 0;
    int new_num = num;

    // If negative, setting to positive
    if (num<0)
    {
        new_num *=-1; 
    }
    
    for (i; i<32; i++)
    {
        out[i] = (new_num >> 31-i) & 1 ? '1':'0';
    }
    
    // If negative number, flipping all bits of positive version
    if (num <0)
    {
        for (int j = 0; j<32; j++)
        {
            if (out[j] == '0')
            {
                out[j] = '1';
            }
            else 
            {
                out[j] = '0';
            }
        }
    }
    out[i++] = '\0';
}

void to_twos_complement(int num, char*out)
{
    int i = 0;

    // Converting binary dig to chars
    for (i; i<32; i++)
    {
        out[i] = (num >> 31-i) & 1 ? '1':'0';
    }
    out[i++] = '\0';
}
