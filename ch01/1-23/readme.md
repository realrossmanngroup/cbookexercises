This exercise is supposed to get rid of comments in C programs.

1-23_delete.c was me trying to figure out how to get the filename from the user and open a file properly after I do that. I had some debugging to do here. I was getting trolled by my while loop, it iterated i too far up. I thought I had to add the null terminator to i + 1, but I only had to add it to i. The while loop is supposed to not work if there is a new line. However, I asked the while loop to check if (filename[i] = getc(stdin)) !=\n, and when it does that, it... adds a new line to my damn character array. This is fixed by adding the null terminator on line 16 at i, rather than i + 1.

1-23_delete_v2.c is more of the same. 

1-23_delete_v3.c is where I try to get the program to load a file of the user's choosing, and then copy its contents to a string array that has multiple lines. I ask it to print the array at the end to ensure it is bit for bit accurate to whatever input the user has. 

The getting rid of comments I figured is going to be a lot of work, so I started experimenting on the basic syntax of dealing with strings in experimenting.c. I should've deleted this since this was a play file I was changing all the time as I experimented with formatting. I didn't realize you couldn't just print a multi-line-string-array in C without a for loop with printf. 

experimenting2.c is where I started working on code to find comments, remove what is inside the comment field, and get out of them - all while copying it to another array. 

Before tackling the beast of getting this to work on MULTIPLE LINES, I wanted to get it to work on one line first - that's what experimenting2.c is for. Now that works, and my brain is done for the day, so I will figure the rest out later. 

I took experimenting2.c and tried smashing it in with nested for loops, but I forgot to make y reset to 0 on a new line, so it doesn't work. 

1-23_delete_v4.c is where I continued and tried to fix it so it works. Remember, each time a - the line I am on, goes up, I need x & y, which are keeping track of where I am IN the line as I search for a comment to reset to 0. 

1-23_delete_v5.c is without debug output. It has to iterate, but more importantly, I used if w = OUT instead of if w == OUT, so it wasn't checking when I went to another line whether I was in or out of a comment. On multi-line comments, I need to check if I am in or out of them - I can't just start from scratch. If I was in a multi line comment and I go to a new line, I still need to delete the rest, if my goal is to delete comments, until I get to a */

1-23_delete_v6.c is when I realized after all of this work that there's 2 ways to do comments in C, // and /* */ - and I only had it set up to do one. This one should be simple though!

At some point I messed up code switching back and forth between 4, 5, and 6. Further, since I was working late at night, I wasn't using version control to properly save them. I got it back to working with no single line comments in 1-23_delete_v7.c

1-23_delete_v10.c fixes where it looks through the entire line rather than looking to the null terminator. but still dies at a single line comment, which is "//"

1-23_delete_v10.c is an interesting case now. 

This first if line at line 103 in 1-23_delete_v10.c isn't working as expected when I feed it a copy of itself to remove comments from. if comment[a][y] is equal to a "/" AND comment[a][y + 1] is equal to an "*", then the else statement should run. However, the else statement is running when comment[a][y] is equal to a "/" and comment[a][y + 1] is equal to a "/". It doesn't seem to care about what comes after the && :( and I can't figure out why :( 

When my program sees a "//" , which is a single line comment, it seems to think it has entered a MULTI LINE COMMENT "/*", and it waits until it sees a */ to get out of it. 

when it takes in itself as an input, it's supposed to only respond when it sees /*. However, on line 47 of this program, it sees this single line comment(//) as a multiline comment(/*)!!!! 

my if statement on line 103 and my else on line 110 is at fault here, which is confirmed by the printout of my debugcode I have on line 112. If I pipe my program's output to a file, I get the following:

"DEBUGOUTPUT we just entered a comment on the original line: nocomment[46][4] is �, comment[46][4] is / (should be a slash), comment[46][5] is / (should be an asterisk) "

It thinks it's entered a comment when it sees a //, when it should only think it's entered a comment when it's seen a /* (I haven't entered the logic in yet for a single line comment!)

It remembers its state as in a comment as the line changes, until it gets to */ on line 49, column 128, as can be seen from this debugcode output from line 140:

"DEBUGOUTPUT leavingcomment on NEW line: nocomment[48][0] is �, comment[48][127] is * (should be an asterisk) and comment[48][128] is / (should be a slash) "




