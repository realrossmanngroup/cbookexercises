1) determine linelength
2) get characters and assign to array
3) Keep track of how far in you are with a variable called howfarin that goes up as you add a character.
4) once howfarin has passed linelength, keep going until you find a blank/tab, and record it to a variable called endposttruncate
5) go backwards until you find a blank or a tab, and record its location to endpretruncate
6) add line from 0 to endpretruncate to line1array
7) print line1array with a \n at the end
8) find, from endpretruncate to endposttruncate. 
9) add that to line2array
10) erase line 1 ARRAY
11 copy line2 array to line1array
12) get size of line1array, add 1 to it, and subtract it from linelength. define howfarin as equal to this. 
13) go back to step 3, and pray for the love of god that this actually works

-------------------
The one above doesn't have it in a function.

1) Get the line, assign it to char array, and figure out how long it is 
2) While the line is greater than linelength, run a function that 
----MAKE THIS INTO A FUNCTION

a) cuts the line to the longest thing that is under linelength
b) takes the line from the cut point, and rewrites that to a new character array
c) empties the original character array
d) copies the new character array to the original array 
---^^^
