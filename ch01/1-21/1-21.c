#include <stdio.h>
#define TABLENGTH 5 /*How many spaces is a tab?*/

int main()
{
    int c;           /* collect input here*/
    int i, j;        /* used to create for loop to replace tabs with spaces*/
    int blank;       /*count blanks*/
    int totalblanks; /*store totla blanks at end after removing blanks from tab count*/
    int tabs;        /*count tabs*/
    blank = totalblanks = tabs = 0;
    while ((c = getchar()) != EOF) /*Get input from keyboard until user hits ctrl-D*/
    {
        if (c == ' ') /*If the user puts in a blank, count the blanks*/
        {
            blank++;
            /* printf("blank:%d", blank); */
        }
        else /* If the user has put anything but a tab, we just put on screen what they input*/
        {
            tabs = (blank / TABLENGTH); /*count how many tabs you need by dividing total blanks by number of tabs*/
            totalblanks = (blank - (tabs * TABLENGTH)); /*find remainder and use that to count the blanks*/
            for (i = 0; i < tabs; i++)
            {
                putchar('\t');
            }
            for (i = 0; i < totalblanks; i++)
            {
                putchar(' ');
            }
            putchar(c);
            blank = totalblanks = tabs = 0;
        }
    }
}
