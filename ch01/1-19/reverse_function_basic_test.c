#include <stdio.h>
/*declare reverse function which reverses the text in a character array*/
char *reverse(char b[], int sizeofarray);

int main()
{
/*Set a char array s[] to hello world with a null terminator*/
    char s[12];

    s[0] = 'h';
    s[1] = 'e';
    s[2] = 'l';
    s[3] = 'l';
    s[4] = 'o';
    s[5] = ' ';
    s[6] = 'w';
    s[7] = 'o';
    s[8] = 'r';
    s[9] = 'l';
    s[10] = 'd';
    s[11] = '\0';

/*set *reversed to the reverse of s*/

    printf("this is going to print the full char array of s[]: %s\n", s);

    printf("this is going to print the full char array of reversed, after I use the reverse function to reverse s[]: %s\n", reverse(s, sizeof(s) / sizeof(s[0])));
}

/*define reverse function which reverses the text in a character array*/
char* reverse(char b[], int sizeofarray)
{
    int i, j; /*variables for loop. One will count down, one will count up.*/
    char* t = (char*) malloc(sizeofarray * sizeof(char));
    for (i = 0, j = sizeofarray - 2; i <= sizeofarray - 2, j >= 0; i++, j--) /*Set loop to count i up and j down; i up from 0, and j down from the end of the array */
    {
        if (b[i] != '\0') /*Only copy stuff over if it isn't null terminated - I don't want to put the null terminator at the beginning of my new character array!*/
        {
            t[j] = b[i]; /*set last character of new array as equal to first character of old array, and keep going until loop ends*/
            printf("%c is b[%d] and %c is t[%d]\n", b[i], i, t[j], j); /*print what's going on for debugging purposes*/
        }
        else
        {
            t[sizeofarray -1] = '\0'; /*when we DO get to a null terminator(end of first character array), make sure to put a null terminator on the END of the new char array*/
        }
    }
    return t;
}
