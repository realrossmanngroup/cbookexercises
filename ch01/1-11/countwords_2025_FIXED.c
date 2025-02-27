#include <stdio.h>
#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */

/* count lines, words, and characters in input */

void main()
{
    int c, nl, nw, nc, state;
    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF)
    {
        ++nc;
        if (c == '\n')
        {
            ++nl;
        }
        if (c == ' ' || c == '\n' || c == '\t' ||
            (c >= 33 && c <= 64) || (c >= 91 && c <= 96)\
             || (c >= 123 && c <= 126))
        /* 
        added logic at the end to not count us as in
        a word when punctuation is entered using ascii.
        if c is a parenthesis, @ symbol, other nonsense,
        it won't consider us inside of a word 
        random characters like parenthesis and 
        pound signs are 33-64, 91-96, and 123-126 in ascii
        */
        {
            state = OUT;
        }
        else if (state == OUT)
        {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}