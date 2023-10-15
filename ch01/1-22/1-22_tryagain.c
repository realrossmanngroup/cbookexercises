#include <stdio.h>

#define MAXLINE 1000
#define LINELENGTH 60 /*how long before we cut off the line?*/

int main()
{
    int howfarin;               /*store where in line*/
    int endposttruncate;        /*end of line, go back from here, this part will go onto the next line with word wrap*/
    int endpretruncate;         /*end of line, go back to here, this stays on line 1 when word wrapped*/
    int line2nullterminatorpos; /*where the null terminator goes on line 2*/
    int c, i, j, k, l;          /*for for loop*/
    int startfromhere, beginning;
    int choppoint;            /*where we are cutting the line*/
    char s[MAXLINE];          /*store what we typed*/
    char line1array[MAXLINE]; /*store line 1*/
    char line2array[MAXLINE]; /*store line 2*/

    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; i++) /* get text as long as it's smaller than MAXLINE*/
    {
        howfarin++;
        s[i] = c; /*store text as char array*/
        if (howfarin > LINELENGTH)
        {
            if (s[i] == ' ' || s[i] == '\t')
            {
                endposttruncate = i;
                i--;
                while (s[i] != EOF)
                {
                    i--;
                    if (s[i] == ' ' || s[i] == '\t')
                    {
                        endpretruncate = i;
                        s[endpretruncate + 1] = '\0'; /*add null terminator to the end of line 1*/
                        break;
                    }
                }
            }
        }
    }
    for (j = 0; j <= endpretruncate; j++)
    { /*add truncated line to array for line 1*/
        line1array[j] = s[j];
        printf("line %d code, line1array[%d] is %c, s[%d] is %c\n", __LINE__, j, line1array[j], j, s[j]);
    }
    printf("%s\n", line1array);
    for (l = 0, k = endpretruncate; l <= endposttruncate - endpretruncate, k <= endposttruncate; l++, k++)
    {
        line2array[l] = s[k];
    }
}