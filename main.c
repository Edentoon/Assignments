#include "convert.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int passed = 0;

int main()
{
    FILE *testfile = fopen("a1_test_file.txt","r");
    if ( testfile == NULL ) 
    {
        printf ("Error : Could not open file \n") ;
        return 1;
    }
    FILE *outputfile = fopen("output.txt","a");
    char buff[100];
    int test = 1;
    

    while (fgets(buff,100,testfile)!= NULL)
    {
        // Checking for which function to test
        if (buff[0] == 'd' || 's' || 'p')
        {
            uint32_t a,b;
            char func[11];
            char compare[32];
            char output[32];
            char result[4];

            // Separate instructions for div and sub convert
            if (buff[0] == 'd' | 's')
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
                if (compare == output)
                {
                    strcpy(result,"PASS");
                    passed++;
                }
                else 
                {
                    strcpy(result,"FAIL");
                }

                // Printing final results to file
                fprintf(outputfile,"Test %d: %s(%d,%d) -> Expected: \"%s\", Got: \"%s\" [%s]\n", test,func,a,b,compare,output,result);
                fclose(outputfile);
            }
            else 
            {
                // Print tables reading format
                sscanf(buff,"%s %d %s", func, &a, compare);
                fprintf(outputfile, "Test %d: %s(%d) -> ");
                print_tables(a); 
            }
            test++;
        }
        
    }
    fprintf(outputfile,"Summary: %d/%d tests passed\n",passed,test);
    fclose(outputfile);
}
