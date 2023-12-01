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

1-23_delete_v12.c is a redo realizing that else and if don't work the way I thought. I thought if-else worked like this:

```
if((x != 10) && (y != 9){
printf("x is not 10, and y is not 9.");
}

else{printf("x is 10 and y is 9.");}

```

However, this is not true! x could be 10, or y could be 9. only ONE of the if statements has to be BS for the entire thing to be false and for it to move onto the else.

and that's where 2 hours of my life went yesterday. 

.....

1-23_delete_v12.c is a bit complicated now because I had to take into account every single scenario, but I did - including the scenario with single comments. I am confused, becuase I thought I would have to use *continue;* rather than *break;* to get the for loop to iterate again. This is something to look up later.

While I did look up how to use the file commands as the book did not cover this yet, I am proud that I did not look at anyone else's answers, or any answer key, in making this program. This program may be a giant program, but it's my giant program - and I didn't import any library other than stdio.h to make it. I am content. :) 

1-23_delete_v12_singlelinedebug.c is getting single line to work as well as normal comments

1-23_delete_v13.c is where I remove all debug code to make it neater. 

1-23_delete_v14.c is where I make opening a file a neat function and also make the formatting neater so it looks identical after single line comments.
 If the else at line 168 runs, I am in big trouble. I can't get it to run though. I will import larger programs in later to see what happens. 

After all this work, my code does not work if a singleline comment is found inside a multiline comment. I am guilty of nothing other than using a shitty editor. nano betrayed me. Look at vscode_comments.png & nano_comments.png and you'll see what I mean. My code works correctly **ASSUMING THAT THE C COMPILER SEES COMMENTS THE WAY NANO TOLD ME IT DID!** But, it doesn't. nano betrayed me, and because of that, we are back to the drawing board. 

1-23_delete_v15.c is where I put debug code back in & try to figure it out and make it work. Lesson learned - never use nano again. I started using nano when I installed gentoo for the first time in 2003 & nano was the default text editor all of the instruction manuals used for configuring things while installing. 

```
This is an analysis of 1-23_delete_v15.c, my program exercise answer to exercise 1-23, with a punchlist of what I must try to correct and fix. 

I ran my program on ht.c , with output at ht2.c As the debug output I added shows, my program correctly sees that comment[3][4] is a "*" and comment[3][5] is a "/" - these two characters make up a "*/" , which is how you know a multiline comment has ended in C. My program correctly detects that on line 3, a multiline comment begins before the sentence "start main function" which is inside the multiline comment, and that the multiline comment continues until line 4, where it ends. 

However, my program does not print the rest of the line after the multiline comment ends. It leaves out "int c;" in its output code. 

Here is why I think my program should work:

1) line 250 in my code sets w = OUT once it properly detects that a multiline comment has ended. 

2) my while loop at line 232 is set to run when w != OUT, so I should be out of my while loop.

3) Once out of my while loop, I should be back at the if statement at line 141. 

4) This if statement should test as false, since singlelinecomment is not YES. 

5) This should then lead us to the if statement at 146, which would test true, since we set w = OUT on line 250. 

6) This should then lead us to the while lop on line 150, where we go through each character on the line again, checking characters & coping them over. 

7) Line 152's if statement will be false, since there are no more multiline comment beginnings expressed as "/*" or multiline comment endings expressed as "*/" in that line

8) The else if statement on 159 will be checked, and be true, as the characters for the remainder of the line are NOT a "/*", and the characters on this line including "int c;" will be copied over from comment[][] to nocomment[][] as the code on lines 160-166 are run. 

However, this is not what happens. "int c;" from ht.c is present in my input code, it is not inside a comment, but it is missing from my output code at ht2.c

It appears, from my debug output, that what is actually happening is my for loop on line 129 is iterating and taking me to the next line when my code from lines 245-252 correctly detects a "*/" ending the multiline comment in my test input that comes before "int c;" on line 4.

I need to figure out why my for loop is iterating when I do not want it to, and how can I keep it from iterating when a multiline comment ends but there is text after it within the code that I have. 
```

When I broke out of my while loop at line 250, I was iterating the for loop. I needed to have a while loop above it that would then properly process everything that was not a comment. That is what 1-23_delete_v16.c attempts to do.

When I run 1-23_delete_v16.c on ht.c again, I get ht2_v16's_output.c - which works! 

Not to get too excited, I decided to run 1-23_delete_v16.c on itself. 

I will admit, 1-23_delete_v16.c is disgusting. There is a lot of copied & pasted code, meaning that something here should be a function. However, I have spent many hours trying to get this to work and I need to rest my brain. I will come back to this later. 

1-23_delete_v16.c doesn't track whether we are inside a string literal though. 

printf("this is a print statement, I am printing //");

This // is NOT a comment, because it is inside of the quotes. 

Funnily enough, throughout this entire process, I was visually checking to see if it made sense, rather than actually trying to compile the output. That's funny.

What I need to do for v17, is while checking for comments, 

a) add a boolean flag that is flagged when we are outside, or inside, a string literal
b) add a condition to comment checking that does it when insidestringliteral == false

AND IT WORKS 

It took five hours to write a working function for this. five hours.
but it works.

1-23_delete_v17.c can process itself, and then create a file that compiles perfectly with gcc. You can run THAT file through the program it made and it works.

I am done with this exercise. I might go back and make some things into functions at a later date so it is neater and easier to follow, but this was horrible so I am taking a break. My god it works :D

1-23_delete_v18.c was me turning certain elements into functions

1-23_delete_v19.c was where I realized that the statement I was using on line 194 of 1-23_delete_v17.c of `else if ((comment[a][y] != '/') && (comment[a][y + 1] != '*'))` was wrong. By making it a || instead of a &&, I can remove countless lines of junk that checks for a slash on the left, a slash on the right, an asterisk on the left, or an asterisk on the right. Since we've already checked for a singleline comment with //, I am not worried about that. Since we cannot be in a /* multiline comment if the first char isn't a / or the second char isn't equal to a *, we must be safe to copy text over. If the first character *IS* a slash, only one of the above has to be true for the line to be true - the next character not being a * solidifies it for us. The problem with && is that it means that BOTH have to be true for the if to run. Also, my string literal/char literal detection was incomplete

1-23_delete_v20.c was where my coworker broke my program in five seconds by putting a \ at the end of the line, escaping the newline character and tricking my program into believing I was on a new line(and therefore resetting stringliteral back to OUT) when we were still in a string. Well played. 
