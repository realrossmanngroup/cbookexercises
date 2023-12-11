`
CHARACTER	( ( ( ( ( ( ) ) ) ( ) 
ARRAYPOSITION	1 2 3 4 5 6 6 5 4 7 
OPENCOUNTER	1 2 3 4 5 6       7 4
CLOSECOUNTER	            1 2 3 	
`
This is a different approach:

each open parenthesis will iterate up `opencounter`
each open parenthesis will add one to array `paren_open_count[opencounter]++`
as long as `max_open` less than `opencounter, `max_open = opencounter`
each closed parenthesis will add one to closecounter 
each closed parenthesis will make us do `paren_close_count[(max_open + 1) - closecounter]++` 
    
line 1 represents the parenthesis, 
line 2 represents what position in the array keeping track of whether they are open/closed we should be adding to. this is how we WANT to track them
line 3 represents how the counter counting open parenthesis will see them. 
line 4 represents how the counter counting closed parenthesis will see them

we need to find a formula to make the counter math match what we want to go into the array. we also need a way to tell which open parenthesis goes with which closed one.

The only way to make this happen seems to be to scan the document and figure out how many open and closed parenthesis there are to begin with, and count from there. as i showed above, i will just wind up overwriting positions if i try to do parenclose[(max_open + 1) - closecounter]++  , which is why this all works like shit.

This entire time, I have been wondering why the program works, but fails if I have different instances of mismatched parenthesis. I've been trying to push a ping pong ball down with one finger inside a bucket of water, and wondering why it keeps popping back up. 

1) let opencounter = max_open AFTER DOING AN INITIAL COUNT! let's say we have NINE total!
2) let closecounter = 0 and go up each time we find a parenthesis, BEFORE adding to an array. 
3) let 

`
CHARACTER	( ( ( ( ( ( ) ) ) ( ) 
ARRAYPOSITION	9 8 7 6 5 4 4 5 6 3 6
OPENCOUNTER	9 8 7 6 5 4       3  
CLOSECOUNTER	            1 2 3   6	
`
  
    
line 1 represents the parenthesis, 
line 2 represents what position in the array keeping track of whether they are open/closed we should be adding to. this is how we WANT to track them
line 3 represents how the counter counting open parenthesis will see them. 
line 4 represents how the counter counting closed parenthesis will see them


EVERYTHING ABOVE IS WRONG. START OVER.
-------------------------------------------

/*play area*/

OPENCOUNTER HAS TO BE COUNTING DOWN FROM THE MAX_OPEN
`
CHARACTER   	( ( ( ( ( ( ) ) ) ( ) ) ) ) ( ) ( )     // THIS REPRESENTS THE CHARACTERS AS THEY ARE IN THE CODE I AM REVIEWING
ARRAYPOSITION	9 8 7 6 5 4 4 5 6 3 3 7 8 9 2 2 1 1  //THIS REPRESENTS WHERE I NEED IT TO BE IN THE ARRAY
OPENCOUNTER	    9 8 7 6 5 4       3         2   1
CLOSECOUNTER	            1 2 3   4 5 6 7   8   9
`

1) we set opencounter equal to max_open after counting the entire doc

2) we find each open parenthesis 

3) we iterate openstatus[opencounter]++ 

4) we store openline[opencounter] = column

5) we store opencolumn[opencounter] = line

6) we iterate opencounter-- DOWN

7) LASTCHAR = OPEN //ADD VARIABLE FOR EACH CHARACTER TYPE TO TRACK THIS, USE BOOLEAN

1) if you see a closed one, closestatus[opencounter - closecounter]++
2) LASTCHAR = CLOSE

3) we count up closecounter++ AFTER iterating the closestatus array up
equal to closecounter[opencounter + closecounter]++. 


Note how when our first ) shows up, 
even though we need its array position to be 2, [opencounter + closecounter] 
would be 2 + 1, which is 3, instead of 2. We would need 2 + 0 to get to 2, 2 + 1
to get to 3 for the next openparenthesis, etc. 
 which we need to get to 2. the 
way to do this with a mathmatical formula that is consistent is to iterate 
closestatus up at a position in the array equal to closestatus[opencounter + closecounter]++
AFTER we detect a closed parenthesis, but BEFORE iterating closecounter++ up


*/
MAXOPEN = 9

CHARACTER   	( ( ( ( ( ( ) ) ) ( ) ) ) ) ( ) ( )     
ARRAYPOSITION	9 8 7 6 5 4 4 5 6 3 3 7 8 9 2 2 1 1  
OPENCOUNTER	    9 8 7 6 5 4       3         2   1
CLOSECOUNTER	            1 2 3   4 5 6 7   8   9


                            maxopen - ((maxopen - opencounter) + closecounter)
                            9 - (9 - 4) + (0)

                              maxopen - ((maxopen - opencounter) + closecounter)
                              9 - ( 9 - 4) + (1)                             

                                        maxopen - ((maxopen - opencounter) + closecounter)
                                        9 - (9 - 3) + 5
/*
                                    


