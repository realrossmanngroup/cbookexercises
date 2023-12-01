The problem lies in parenthesis detection - specifically, it not finding the closed ones. It doesn't because it doesn't handle string detection properly. Below, it still thinks I am in a string, when I am not!

Fix this to have a working program. Then, move on to detecting brackets and curly braces. that will be easy once this part works. 

```
DEBUG line 194: program[32][9] is c, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][10] is u, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][11] is r, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][12] is r, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][13] is e, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][14] is n, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][15] is t, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][16] is c, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][17] is h, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][18] is a, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][19] is r, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][20] is  , stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][21] is =, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][22] is =, stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][23] is  , stringliteral is 1, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][24] is ', stringliteral is 0, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][25] is \, stringliteral is 0, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][26] is n, stringliteral is 0, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][27] is ', stringliteral is 0, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][28] is ), stringliteral is 0, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][29] is  , stringliteral is 0, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][30] is &, stringliteral is 0, charliteral is 1, comment is 1, singlelinecomment is 1
DEBUG line 194: program[32][31] is &, stringliteral is 0, charliteral is 1, comment is 1, singlelinecomment is 1
```
