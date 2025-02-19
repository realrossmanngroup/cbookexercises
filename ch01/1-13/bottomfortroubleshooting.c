
        // find lowest number of words for a char count
        leastwords = mostwords;

        for (int x = 0; x = biggestword; x++)
        {
            if (wordlength[x] < leastwords)
            {
                wordlength[x] = leastwords;
            }
        }

        // find shortest word
        smallestword = biggestword;
        for (int x = leastwords; x = mostwords; x++)
        {
            if (wordlength[x] < smallestword)
            {
                smallestword = x;
            }
        }
    

    // print histogram
    for (int y = mostwords; y = leastwords; y--)
    {
        printf("\n%2d  ", y); //begin the next line with the number of words with x character count
        for (int x = smallestword; x = biggestword; x++)
        {
            if (wordlength[x] >= y)
            {
                printf("##  "); /*if number of words for this charcount equals or
                                exceeds x, create ## for bar graph for histogram*/
            }
        }
    }
    // print bottom legend for histogram
    for (int x = smallestword; x = biggestword; x++)
    {
        printf("%2d  ", x);
    }
    printf("\n\n");
}

/*random brainstorming

we go from top to bottom.
as we go top to bottom, we need to iterate through wordlength[] from bottom to top,
and only print a '#' character IF wordlength[x]

NEW BRAINSTORMING


To print one line at a time, we have to modify the
word counter program to STORE the word.
Once out of a word, it needs to print the contents of the word
and a newline before it returns to in a word.

THIS MEANS WE WILL DO THE FOLLOWING:

1) Create a character array that can store the word

2) Count how many characters are in the word so that we know
how long the for loop to print the word needs to be.
charcount should start at 0, and for loop must end
at < charcount rather than <= charcount

3) initialize char array charcount empty

4) make sure charcount[100] for 99 spaces

5) make sure if word more than 98 characters we
exit program just incase I do something dumb to retain memory safety
6) for loop to print the word with newline character
each time we are OUT of a word
7) initialize charcount as 0 before going back into a word.

*/