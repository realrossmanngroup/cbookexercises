This is an analysis of 1-23_delete_v15.c, my program exercise answer to exercise 1-23, with a punchlist of what I must try to correct and fix. 

As the debug output I added shows, my program correctly sees that comment[3][4] is a "*" and comment[3][5] is a "/" - these two characters make up a "*/" , which is how you know a multiline comment has ended in C. My program correctly detects that on line 3, a multiline comment begins before the sentence "start main function" which is inside the multiline comment, and that the multiline comment continues until line 4, where it ends. 

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