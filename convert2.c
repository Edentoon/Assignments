#include <string.h>
#include <stdio.h>
#include <math.h>

void oct_to_bin(const char *oct, char *out)
{
    int i = 0;
    int pos = 0;
    char buffer[100];
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
    pos=0;
    char reverse[100];
    while (index >= 0)
    {
        double exp;
        int dig = 0;
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
    if (num<0)
    {
        num*= -1;
        out[0] = '1';
    }
    else 
    {
        out[0]= '0';
    }
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
    if (num<0)
    {
        new_num *=-1; 
    }
    
    for (i; i<32; i++)
    {
        out[i] = (new_num >> 31-i) & 1 ? '1':'0';
    }
    
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
    for (i; i<32; i++)
    {
        out[i] = (num >> 31-i) & 1 ? '1':'0';
    }
    out[i++] = '\0';
}