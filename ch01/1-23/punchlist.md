This first if line at line 103 isn't working as expected. if comment[a][y] is equal to a "/" AND comment[a][y + 1] is equal to an "*", then the else statement should run. However, the else statement is running when comment[a][y] is equal to a "/" and comment[a][y + 1] is equal to a "/". It doesn't seem to care about what comes after the && :( and I can't figure out why :( 

When my program sees a "//" , which is a single line comment, it seems to think it has entered a MULTI LINE COMMENT "/*", and it waits until it sees a */ to get out of it. 

when it takes in itself as an input, it's supposed to only respond when it sees /*. However, on line 47 of this program, it sees this single line comment(//) as a multiline comment(/*)!!!! 

my if statement on line 103 and my else on line 110 is at fault here, which is confirmed by the printout of my debugcode I have on line 112. If I pipe my program's output to a file, I get the following:

"DEBUGOUTPUT we just entered a comment on the original line: nocomment[46][4] is �, comment[46][4] is / (should be a slash), comment[46][5] is / (should be an asterisk) "

It thinks it's entered a comment when it sees a //, when it should only think it's entered a comment when it's seen a /* (I haven't entered the logic in yet for a single line comment!)

It remembers its state as in a comment as the line changes, until it gets to */ on line 49, column 128, as can be seen from this debugcode output from line 140:

"DEBUGOUTPUT leavingcomment on NEW line: nocomment[48][0] is �, comment[48][127] is * (should be an asterisk) and comment[48][128] is / (should be a slash) "




