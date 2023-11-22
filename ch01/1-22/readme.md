psuedocode.md documents what I wanted the program to do, in plain English.

1-22.c was my first failed attempt. 1-22_tryagain.c was me trying to get it to work for a week, but still failing. 

1-22_tryagain_v2.c was when I realized I needed to collect the characters into the char array separately from the loop where I try to figure out where I am. This took a week and a half to figure out. Shame & flog me accordingly, I earned it. 

I can't lie, this is just frustration after misery. around v4-v5 I had segmentation faults. around v6-v7 I was erasing an array improperly because I did the thing again where I was referring to a memory address instead of the actual size of a character array, so I was erasing the entire memory space and wiping out the variable endofinput to 0 when I erased the s array. 

At v8 it worked but still had a bunch of debug code in it and the last line was full of shit since I forgot to wipe the w2 array after each use. It doesn't matter when the first line is longer than 60 characters but it matters a lot when it is. 

Around v9 it finally worked. 

This was hell on earth, and if I had half a brain or any sense of dignity I'd pretend I got it right the first time and clean up the garbage files. But, I don't want to do that. I want to look back on this someday and laugh when I am a much better programmer.

3 months ago, I thought exercise 1-13 and 1-14 were actually impossible, and now I laugh at how simple they are. I hope in the future, I can laugh at this as well.
