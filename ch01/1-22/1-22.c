#include <stdio.h>

#define MAXLINE 1000
#define TOOLONG 60 /*how long before we cut off the line?*/

int main()
{
    int howlong;    /*store how long this*/
    int c, i, k, l; /*for for loop*/
    int startfromhere, beginning;
    int choppoint;         /*where we are cutting the line*/
    char s[MAXLINE];       /*store what we typed*/
    char chopped[MAXLINE]; /*store chopped line temporarily */

    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF; i++) /* get text as long as it's smaller than MAXLINE*/
    {
        howlong++;
        s[i] = c; /*store text as char array*/
        printf("line %d storing typed text %c to s[%d]\n", __LINE__, s[i], i);
        if (c == '\n')
        {
            s[i] = '\0';
            printf("line %d added null terminator to s[%d] \n", __LINE__, i);
            break;
        }
    }

    beginning = 0;
    startfromhere = 0;
    choppoint = 0;
    while (s[startfromhere] != '\0')
    {
        printf("line %d while loop running, startfromhere is %d and s[%d] is %c \n", __LINE__, startfromhere, startfromhere, s[startfromhere]);
        if (startfromhere > TOOLONG - choppoint)
        {
            if (s[startfromhere] == ' ' || s[startfromhere] == '\t')
            {
                printf("line %d code ran, %d is startfromhere, %d is choppoint, %d is beginning \n", __LINE__, startfromhere, choppoint, beginning);
                /* debug code only */
            }
            else
            {
                choppoint = startfromhere - 1;
                printf("line %d code ran\n", __LINE__); /* testing debug code*/
                /* THIS IS WRITTEN IN PSUEDOCODE FOR MY BENEFIT, DON'T ACTUALLY TRY TO COMPILE THIS GARBAGE!!!*/
                for (l = 0, k = beginning; l <= choppoint - beginning, k <= choppoint; l++, k++)
                {
                    chopped[l] = s[k];
                    printf("line %d code ran\n", __LINE__);
                }
                printf("%s\n", chopped); /* print all the text from that to that */
                beginning = choppoint;
                startfromhere = choppoint;
            }
        }
        startfromhere++;
    }
}
