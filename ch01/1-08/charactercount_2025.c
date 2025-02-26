#include <stdio.h>

/* Count how many new lines, blank characters, and characters
are present in input*/
void main()
{
    int blanks, chars, lines, c;
    lines = blanks = chars = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            lines++;
        }
        else if (c == ' ')
        {
            blanks++;
        }
        else
        {
            chars++;
        }
    }

    printf("lines: %d\n\nblanks: %d\n\ncharacters: %d\n\n", lines, blanks, chars);
}