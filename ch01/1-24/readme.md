exercise 1-24 is for the creation of a program that finds mismatched (), {}, and [] in C programs. 

I added a bunch of updates, wherewefail.md is where I need to pick up from when I get back to work on this. I am using `testprog.c` as my input to `1-24_correction_v1.c` which is the program for this exercise.

`1-24_correction_v2.c` fixed the stringinorout function as well as made the program massively more efficient when debuglogging by keeping track of how long each line is, and only iterating up to that point. 

`1-24_correction_v3.c` fixes all of my issues with strings, cleans up variable names, and fixes multiline comment detection. It properly checks for parenthesis. Now I need to copy that code for brackets, curly braces, quotes, etc.

I tried with `1-24_correction_v4.c` to make a function. However, according to my debugoutput, when I pass the line & column of my program array to my function to check whether it is a ( or a ), it thinks I am always at 0. Regardless of the actual value of line & column, my debugoutput shows line & column being 0. I have 0 initialized all of my arrays and made sure they're not out of bounds. I don't know what I am missing. :( 
edit: I declared line & column twice. I started thinking about this as I fell asleep and figured it out and woke up to fix it. Fun!
