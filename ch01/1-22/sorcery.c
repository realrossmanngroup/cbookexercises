#include <stdio.h>

#define MAXLINE 1000
#define LINELENGTH 60 /* how long before we cut off the line? */

int main()
{
    int c, i, j, k;
    char s[MAXLINE];
    char line1array[MAXLINE];
    char line2array[MAXLINE];

    i = 0;

    // Capture user input
    while (i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0'; // Null-terminate the string

    // Check if line length exceeds LINELENGTH
    if (i > LINELENGTH)
    {
        int foldPos = LINELENGTH;
        
        // Find the nearest space or tab before LINELENGTH to fold at
        while (foldPos > 0 && s[foldPos] != ' ' && s[foldPos] != '\t')
        {
            foldPos--;
        }

        if (foldPos == 0) // Couldn't find a space/tab, so fold at LINELENGTH
            foldPos = LINELENGTH;

        // Populate line1array
        for (j = 0; j < foldPos; j++)
        {
            line1array[j] = s[j];
        }
        line1array[j] = '\0'; // Null-terminate

        // Populate line2array
        k = 0;
        for (j = foldPos; s[j] != '\0'; j++)
        {
            line2array[k++] = s[j];
        }
        line2array[k] = '\0'; // Null-terminate

        printf("%s\n", line1array);
        printf("%s\n", line2array);
    }
    else // If the line is shorter than LINELENGTH, print as is
    {
        printf("%s\n", s);
    }

    return 0;
}
