#include <stdio.h>
#include <stdlib.h>

void main()
{
    /* output histogram based on word count */

    // input from keyboard
    int c;

    // store count of use of each character
    int ascii[130];
    // initialize array with 0 values

    for (int x = 0; x < 129; x++)
    {
        ascii[x] = 0;
    }
    int highestcount = 0;

    while ((c = getchar()) != EOF)
    {
        ++ascii[c];
        if (ascii[c] > highestcount)
        {
            highestcount = ascii[c];
        }
    }
    // MAKE THE HISTOGRAM
    printf("\n\n");
    printf("CHARACTER\nTYPED:\n");

    for (int asciinumber = 0; asciinumber < 128; asciinumber++)
    {
        if (ascii[asciinumber] > 0)
        {

            if ((asciinumber == 10) || (asciinumber == 13))
            {

                printf("\nnewline\t\t| ");
                for (int x = 1; x <= (ascii[10] + ascii[13]); x++)
                {
                    printf("*  ");
                }
            }
            else if (asciinumber == 9)
            {

                printf("\ntab\t\t| ");
                for (int x = 1; x <= ascii[9]; x++)
                {
                    printf("*  ");
                }
            }
            else if (asciinumber == 32)
            {

                printf("\nspace\t\t| ");
                for (int x = 1; x <= ascii[32]; x++)
                {
                    printf("*  ");
                }
            }
            else
            {
                printf("\n%c\t\t| ", asciinumber);
                for (int x = 1; x <= ascii[asciinumber]; x++)
                {
                    printf("*  ");
                }
            }
        }
    }

    // dashes between graph & x axis legend
    printf("\n");
    printf("\t\t  ");
    for (int bottomcount = 0; bottomcount < highestcount; bottomcount++)
    {
        printf("___");
    }
    // x axis legend
    printf("\n\t     ");
    for (int bottomcount = 0; bottomcount <= highestcount; bottomcount++)
    {
        printf("%3.0d", bottomcount);
    }
    // label for x axis

    printf("\n\n\t\tCHARACTER COUNT\n\n");
    printf("\n\n");
}