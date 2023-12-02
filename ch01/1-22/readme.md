`1-22_completed_exercise.c` is the completed exercise, fully working. 

`psuedocode.md` documents what I wanted the program to do, in plain English. I went through three iterations of psuedocode before I got it to work. 

This was hard. I was stuck on this for almost two months and gave up for days at a time, not doing any work on it. If I had half a brain or a sense of dignity I'd pretend I got it right the first time and clean up all of the old garbage files; but I want to look back on this someday and laugh when I am a far better programmer at the progress I made. 3 months ago, I thought exercise 1-13 and 1-14 were impossible, and now they seem simple. I hope in the future, I can laugh at this too.

`1-22.c` was my first failed attempt. 1-22_tryagain.c was me trying to get it to work for a week, but still failing. 

`1-22_tryagain_v2.c` was when I realized I needed to collect the characters into the char array separately from the loop where I try to figure out where I am. This took a week and a half to figure out. Doh. :( 

around v4-v5 I had segmentation faults annd infinite loops. I wanted my loop to run as long as the number of characters in the array was greater than the LINELENGTH which is 60 characters. I was using sizeof(s) / sizeof(s[0]) to try and calculate the size of the array. However, sizeof(s) / sizeof(s[0]) is always going to return 1000, which is the number of characters that CAN fit in the loop, not how many are actually in there. So, I set a while loop to run as long as 1000 > 60, which is... never going to stop looping, because 1000 will never stop being greater than 60. 

Around `1-22_tryagain_v6_god_bless_america.c` I didn't realize that on line 104 I set a loop erasing array s to go up until sizeof(s) which is 1000, rather than < which would've been sizeof(s) - 1, so I was not erasing 0 to 999, i was erasing 0 to 1000, which is 1 over the array. This means I am writing to memory space outside the array, which was erasing my endofinput variable which was crucial for line splitting. I debugged this by spamming printf everywhere in my program to figure out exactly where endofinput was being erased to 0 to find my misake. 

At `1-22_tryagain_v8_after_fix.c` it worked but still had a bunch of debug code in it and the last line was full of garbage since I forgot to wipe the w2 array after each use. I thought arrays that were declared inside of functions wiped themselves after each use, but they don't, so there was junk left over in there. Since the last line is going to be less than 60 characters, if there's anything left in there from the prior array splicing it would be written after the last line, and junk would be left. Code was added to always erase w2 in my function. 

Around `1-22_tryagain_v9_after_fix.c` it finally worked, but it's messy, and it still doesn't act properly if you type a line with no tabs and no spaces. That breaks the program.

`1-22_tryagain_v10.c` is cleaned up, and also intelligently deals with trolling input - if someone tries to break the program by entering a line with no spaces, it will still work. 

