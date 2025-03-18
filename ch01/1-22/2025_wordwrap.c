#include <stdio.h>
#define MAXLINELENGTH 10000
#define RIGHTMARGIN 60

int wordwrap(char s[], int linelength);

void main()
{

    char typedinput[MAXLINELENGTH];
    int c, linelength;
    c = linelength = 0;

    while (c != EOF)
    {

        // take user input until they hit enter
        for (int i = 0; (((c = getchar()) != EOF) && (i < MAXLINELENGTH)); i++)
        {

            if (c != '\n')
            {
                typedinput[i] = c; // record typed input
                linelength = i;    // update linecount
            }
            else
            {
                typedinput[i] = '\0'; // put null terminator at end of line.
                linelength = i;

                break; // leave loop on  hitting enter
            }
        }

        // print the line without doing any wrapping if it is within the margin
        if (linelength <= RIGHTMARGIN)
        {
            printf("\n");
            for (int x = 0; x <= linelength; x++)
            {
                printf("%c", typedinput[x]);
            }
            printf("\n");
        }
        // word wrap the line if it goes past the margin
        else
        {
            printf("\n");
            wordwrap(typedinput, linelength);
            printf("\n");
        }
    }
}

int wordwrap(char s[], int linelength)
{

    int beginning, end, breakpoint, line_number;
    beginning = 0;
    end = RIGHTMARGIN;
    breakpoint = 0;
    line_number = 0;

    // keep chopping away at
    while ((linelength - breakpoint) >= RIGHTMARGIN) // keep going until we are at the last line
    {

        // find a break point where we can splitt he line
        for (int place_in_line = beginning; place_in_line <= (beginning + end); place_in_line++)
        {
            if ((s[place_in_line] == ' ') || (s[place_in_line] == '\t'))
            {
                breakpoint = place_in_line;
            }
        }

        // print line if breakpoint
        if (breakpoint > beginning)
        {
            for (int place_in_line = beginning; place_in_line <= breakpoint; place_in_line++)
            {
                printf("%c", s[place_in_line]);
            }

            printf("\n");                 // line break
            beginning = (breakpoint + 1); // next line must begin 1 character after we broke
        }

        // use hyphen to break line if someone uses a 61+ character word as a troll
        else
        {

            for (int place_in_line = beginning; place_in_line <= (beginning + (RIGHTMARGIN - 1)); place_in_line++)
            {
                printf("%c", s[place_in_line]);
            }
            printf("-");  // print hyphen at end of line
            printf("\n"); // line break

            beginning = (beginning + RIGHTMARGIN); // get ready for next line to begin where you broke.
        }
    }

    // print last line after splitting is done
    if ((linelength - breakpoint) < RIGHTMARGIN)
    {

        for (int place_in_line = beginning; place_in_line <= (beginning + linelength); place_in_line++)
        {
            printf("%c", s[place_in_line]);
        }
    }
}
