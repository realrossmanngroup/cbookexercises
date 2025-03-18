#include <stdio.h>
#define MAXLINE 10000

int wordwrap(char s[], int linelength);

void main()
{

    char typedinput[MAXLINE];
    int c, linelength;
    c = linelength = 0;
    // printf("\n[%d] debug before while loop\n", __LINE__);
    while (c != EOF)
    { // loop until we end program
        // printf("\n[%d] debug begin while loop\n", __LINE__);

        for (int i = 0; (((c = getchar()) != EOF) && (i < MAXLINE)); i++)
        {
            // printf("\n[%d] debug begin getchar; c is %c i is %d\n", __LINE__, c, i);

            if (c != '\n')
            {
                typedinput[i] = c; // record typed input
                linelength = i;    // update linecount
            }
            else
            {
                typedinput[i] = '\0'; // put null terminator at end of line.
                linelength = i;

                // printf("\n[%d] debug newline end loop i is %d\n", __LINE__, i);
                break; // leave loop on new line
            }
        }
        // printf("\n[%d] debug outside while before checking linelength which is %d\n", __LINE__, linelength);

        if (linelength <= 60)
        {
            printf("\n");
            for (int x = 0; x <= linelength; x++)
            {
                printf("%c", typedinput[x]);
            }
            printf("\n");
        }
        else
        {
            printf("\n");
            wordwrap(typedinput, linelength); // print everything wordwrapped
            // repeat loop}
            printf("\n");
        }
    }
}

int wordwrap(char s[], int linelength)
{
    // printf("\n[%d] debug print line at beginning of wordwrap when linelength = %d: %c\n", __LINE__, linelength, s[linelength - 2]);

    int beginning, end, breakpoint, line_number;
    beginning = 0;
    end = 60;
    breakpoint = 0;
    line_number = 0;

    while ((linelength - breakpoint) >= 60) // keep going until we are at the last line
    {
        // printf("\n[%d] inside while inside wordwrap linelength is %d\n", __LINE__, linelength);

        for (int place_in_line = beginning; place_in_line <= (beginning + end); place_in_line++) // find breakpoint
        {
            if ((s[place_in_line] == ' ') || (s[place_in_line] == '\t'))
            {
                breakpoint = place_in_line;
            }
        }
        // printf("\n[%d] debug  breakpoint counter ends at %d\n", __LINE__, breakpoint);

        if (breakpoint > beginning)
        { // print line
            for (int place_in_line = beginning; place_in_line <= breakpoint; place_in_line++)
            {
                printf("%c", s[place_in_line]);
            }
            // printf("\n[%d] debug print line after breaking it linelength is %d breakpoint is %d\n", __LINE__, linelength, breakpoint);
            printf("\n");           // line break
            beginning = (breakpoint + 1); // next line must begin 1 character after we broke

            // printf("\n[%d] debug print line after changing counts linelength is %d breakpoint is %d\n", __LINE__, linelength, breakpoint);
        }
        else
        { // print line forcibly hyphenating it if the word is longer than 60. 

            for (int place_in_line = beginning; place_in_line <= (beginning + 59); place_in_line++)
            {
                printf("%c", s[place_in_line]);
            }
            printf("-");  // print hyphen at end of line
            printf("\n"); // line break

            beginning = (beginning + 60); // get ready for next line to begin where you broke.

            
        }
    }
    if ((linelength - breakpoint) < 60)
    { // print last line after splitting
        // printf("\n[%d] debug last line before print beginning is %d linelength is %d\n", __LINE__, beginning, linelength);

        for (int place_in_line = beginning; place_in_line <= (beginning + linelength); place_in_line++)
        {
            printf("%c", s[place_in_line]);
        }
        // printf("\n[%d] debug last line after splitting should be here, linelength is %d breakpoint is %d\n", __LINE__, linelength, breakpoint);
    }
}


// COMMENTED VERSION BELOW:

/*
int wordwrap(char s[], int linelength);

void main()
{

    char typedinput[MAXLINE];
    int c, linelength;
    c = linelength = 0;
    printf("\n[%d] debug before while loop\n", __LINE__);
    while (c != EOF)
    { // loop until we end program
        printf("\n[%d] debug begin while loop\n", __LINE__);

        for (int i = 0; (((c = getchar()) != EOF) && (i < MAXLINE)); i++)
        {
            printf("\n[%d] debug begin getchar; c is %c i is %d\n", __LINE__, c, i);

            if (c != '\n')
            {
                typedinput[i] = c; // record typed input
                linelength = i;    // update linecount
            }
            else
            {
                typedinput[i] = '\0'; // put null terminator at end of line.
                linelength = i;

                printf("\n[%d] debug newline end loop i is %d\n", __LINE__, i);
                break; // leave loop on new line
            }
        }
        printf("\n[%d] debug outside while before checking linelength which is %d\n", __LINE__, linelength);

        if (linelength <= 60)
        {
            printf("\n");
            for (int x = 0; x <= linelength; x++)
            {
                printf("%c", typedinput[x]);
            }
            printf("\n");
        }
        else
        {
            printf("\n");
            wordwrap(typedinput, linelength); // print everything wordwrapped
            // repeat loop}
            printf("\n");
        }
    }
}

int wordwrap(char s[], int linelength)
{
    printf("\n[%d] debug print line at beginning of wordwrap when linelength = %d: %c\n", __LINE__, linelength, s[linelength - 2]);

    int beginning, end, breakpoint, line_number;
    beginning = 0;
    end = 60;
    breakpoint = 0;
    line_number = 0;

    while ((linelength - breakpoint) >= 60) // keep going until we are at the last line
    {
        printf("\n[%d] inside while inside wordwrap linelength is %d\n", __LINE__, linelength);

        for (int place_in_line = beginning; place_in_line <= (beginning + end); place_in_line++) // find breakpoint
        {
            if ((s[place_in_line] == ' ') || (s[place_in_line] == '\t'))
            {
                breakpoint = place_in_line;
            }
        }
        printf("\n[%d] debug  breakpoint counter ends at %d\n", __LINE__, breakpoint);

        if (breakpoint > beginning)
        { // print line
            for (int place_in_line = beginning; place_in_line <= breakpoint; place_in_line++)
            {
                printf("%c", s[place_in_line]);
            }
            printf("\n[%d] debug print line after breaking it linelength is %d breakpoint is %d\n", __LINE__, linelength, breakpoint);
            printf("\n");           // line break
            beginning = (breakpoint + 1); // next line must begin 1 character after we broke

            printf("\n[%d] debug print line after changing counts linelength is %d breakpoint is %d\n", __LINE__, linelength, breakpoint);
        }
        else
        { // print line forcibly hyphenating it if the word is longer than 60.

            for (int place_in_line = beginning; place_in_line <= (beginning + 59); place_in_line++)
            {
                printf("%c", s[place_in_line]);
            }
            printf("-");  // print hyphen at end of line
            printf("\n"); // line break

            beginning = (beginning + 60); // get ready for next line to begin where you broke.


        }
    }
    if ((linelength - breakpoint) < 60)
    { // print last line after splitting
        printf("\n[%d] debug last line before print beginning is %d linelength is %d\n", __LINE__, beginning, linelength);

        for (int place_in_line = beginning; place_in_line <= (beginning + linelength); place_in_line++)
        {
            printf("%c", s[place_in_line]);
        }
        printf("\n[%d] debug last line after splitting should be here, linelength is %d breakpoint is %d\n", __LINE__, linelength, breakpoint);
    }
}



*/