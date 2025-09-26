#include "convert.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global variable for tracking test number
extern int passed;

int main()
{

    FILE *testfile = fopen("a2_test.txt","r");
    if ( testfile == NULL ) 
    {
        printf ("Error : Could not open file \n") ;
        return 1;
    }
    
    // Allocating buffer space
    char buff[100];
    int test = 0;
    
    // Reading testfile line by line
    while (fgets(buff,100,testfile)!= NULL)
    {
        // Checking that line is not to be ignored
        if (buff[0] == 'o' || buff[0] == 't' || buff[0] == 'h')
        {
            // Tracking test number
            test++;

            char a[33];
            int b;
            char func[30];
            char compare[33];
            char output[33];
            char result[5];
            
            
            // Separate instructions for string inputs
            if (buff[0] == 'o' || buff[0] == 'h')
            {
                // String reading format
                sscanf(buff, "%s %s %s", func,a,compare);

                // Choosing which function to use
                if (func[0] == 'o')
                {
                    if (func[7] == 'b')
                    {
                        oct_to_bin(a,output);
                    }
                    else
                    {
                        oct_to_hex(a,output);
                    }
                }
                else 
                {
                    hex_to_bin(a,output);
                }
            }
            else 
            {
                // Integer reading format
                sscanf(buff,"%s %d %s", func, &b, compare);

                // Choosing which function to use
                if (func[3] == 's')
                {
                    to_sign_magnitude(b,output);
                }

                else if (func[3] == 'o')
                {
                    to_ones_complement(b,output);
                }

                else 
                {
                    to_twos_complement(b,output);
                }
                
            }

            // Comparing output of function to test value
            if (!strcmp(output,compare))
            {
                strcpy(result,"PASS");
                passed++;
            }
            else 
            {
                strcpy(result,"FAIL");
            }

            // Printing final results to screen
            if (func[0]=='t')
            {
                printf("Test %d: %s(%d) -> Expected: \"%s\", Got: \"%s\" [%s]\n", test,func,b,compare,output,result);
            }
            else 
            {
                printf("Test %d: %s(\"%s\") -> Expected: \"%s\", Got: \"%s\" [%s]\n", test,func,a,compare,output,result);
            }
        }
    }
    printf("Summary: %d/%d tests passed\n",passed,test);
    fclose(testfile);
}
