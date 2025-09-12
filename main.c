#include "convert.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global variable for tracking test number
extern int passed;

int main()
{

    FILE *testfile = fopen("a1_test_file.txt","r");
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
        // Checking for which function to test
        if (buff[0] == 'd' || buff[0] == 's' || buff[0] == 'p')
        {
            // Tracking test number
            test++;

            uint32_t a,b;
            char func[12];
            char compare[33];
            char output[33];
            char result[5];
            
            // Separate instructions for div and sub convert
            if (buff[0] == 'd' || buff[0] == 's')
            {
                // Conversion reading format
                sscanf(buff, "%s %d %d %s", func,&a,&b,compare);

                if (func[0] == 'd')
                {
                    div_convert(a,b,output);
                }
                else 
                {
                    sub_convert(a,b,output);
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
                printf("Test %d: %s(%u,%d) -> Expected: \"%s\", Got: \"%s\" [%s]\n", test,func,a,b,compare,output,result);
                
            }
            else 
            {
                // Print tables reading format
                sscanf(buff,"%s %d %s", func, &a, compare);
                
                printf("Test %d: %s(%d) -> \n",test,func,a);
                print_tables(a); 
            }
        }
    }
    printf("Summary: %d/%d tests passed\n",passed,test);
    fclose(testfile);
}
