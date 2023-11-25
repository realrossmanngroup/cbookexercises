This exercise is supposed to get rid of comments in C programs.

1-23_delete.c was me trying to figure out how to get the filename from the user and open a file properly after I do that. I had some debugging to do here. I was getting trolled by my while loop, it iterated i too far up. I thought I had to add the null terminator to i + 1, but I only had to add it to i. The while loop is supposed to not work if there is a new line. However, I asked the while loop to check if (filename[i] = getc(stdin)) !=\n, and when it does that, it... adds a new line to my damn character array. This is fixed by adding the null terminator on line 16 at i, rather than i + 1.

1-23_delete_v2.c is more of the same. 

1-23_delete_v3.c is where I try to get the program to load a file of the user's choosing, and then copy its contents to a string array that has multiple lines. I ask it to print the array at the end to ensure it is bit for bit accurate to whatever input the user has. 

The getting rid of comments I figured is going to be a lot of work, so I started experimenting on the basic syntax of dealing with strings in experimenting.c. I should've deleted this since this was a play file I was changing all the time as I experimented with formatting. I didn't realize you couldn't just print a multi-line-string-array in C without a for loop with printf. 

experimenting2.c is where I started working on code to find comments, remove what is inside the comment field, and get out of them - all while copying it to another array. 

Before tackling the beast of getting this to work on MULTIPLE LINES, I wanted to get it to work on one line first - that's what experimenting2.c is for. Now that works, and my brain is done for the day, so I will figure the rest out later. 


