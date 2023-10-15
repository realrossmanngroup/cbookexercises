Let's say a line is stupidly long and it's not readable on screen before it makes its way off like this one

ok first thing's first. 

1) Determine how long is too long. 60 characters?  store to toolong

2) store line in char array, and count up howlong++

3) once howlong gets over toolong, wait for a blank or a tab

4) make new char array and start putting crap there 

5) repeat whatever you did before

6) continue ad nauseum until you run out of new arrays ?

wait a second. instead of constantly using new arrays, why not just use the same array and keep track of where in the array these lines are? hm. maybe try that after i get the first idea to work.

7) print the new character arrays at EOF


1) determine how long is too long, 60 chars, store to TOOLONG

2) store line in char array and howlong++ while doing that, make for loop in a way where newline breaks it

3) after you hit ENTER/newline, run program that will split that shit up into character arrays 

	4) somewhere in here you're going to tell it to 
		a) set beginning to 0
		b) find a blank/tab while s[STARTFROMHERE] > toolong , figure out how to iterate STARTFROMHERE up 1 consistently
if c[startfromhere] != blank or tab, startfromhere++
else c[startfromhere] -1 = choppoint

		c) record location of beginning to choppoint
		d) make char array with that using a for loop probably, print that
		e) figure out how to start again but from choppoint. 
		f) 
		d) reset program


		c) find character that is NOT a blank, record location
		d) count from s[recordedlocation] + toolong. 
		e) find blank character/tab again
		
