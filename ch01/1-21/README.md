`2025_replace_spaces_with_tabs.c` replaces spaces with tabs assuming a tab length of 8. once we get to 8 spaces, it will place a tab where the first space was, and then go back to counting spaces.

I ran `gdb` to ensure that I was getting proper output. in xfce4-terminal, tabs do not show up as 8 spaces. i wanted to make sure the output was correct. i tried with 8 spaces between words, then 9, then 10, and confirmed with gdb that it works and puts the proper amount of tabs & spaces. see check below:

```
[louis@bauerframe 1-21]$ gcc -g 2025_replace_spaces_with_tabs.c -o replace_tabs
[louis@bauerframe 1-21]$ gdb ./replace_tabs 
GNU gdb (GDB) 16.2
Copyright (C) 2024 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-pc-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./replace_tabs...
(gdb) break oldgetline
Breakpoint 1 at 0x120f: file 2025_replace_spaces_with_tabs.c, line 36.
(gdb) run
Starting program: /home/louis/Documents/programming_practice/cbookexercises/ch01/1-21/replace_tabs 

This GDB supports auto-downloading debuginfo from the following URLs:
  <https://debuginfod.archlinux.org>
Enable debuginfod for this session? (y or [n]) y
Debuginfod has been enabled.
To make this setting permanent, add 'set debuginfod enabled on' to .gdbinit.
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/usr/lib/libthread_db.so.1".

Breakpoint 1, oldgetline (s=0x7fffffffe150 "", lim=1000)
    at 2025_replace_spaces_with_tabs.c:36
36	    i = 0;

(gdb) continue
Continuing.
test        eight         nine          ten
test	eight	 nine	  ten


Breakpoint 1, oldgetline (s=0x7fffffffe150 "test\teight\t nine\t  ten", lim=1000)
    at 2025_replace_spaces_with_tabs.c:36
36	    i = 0;
(gdb) print s[0]
$1 = 116 't'
(gdb) print s[1]
$2 = 101 'e'
(gdb) print s[2]
$3 = 115 's'
(gdb) print s[3]
$4 = 116 't'
(gdb) print s[4]
$5 = 9 '\t'
(gdb) print s[5]
$6 = 101 'e'
(gdb) print s[6]
$7 = 105 'i'
(gdb) print s[7]
$8 = 103 'g'
(gdb) print s[8]
$9 = 104 'h'
(gdb) print s[9]
$10 = 116 't'
(gdb) print s[10]
$11 = 9 '\t'
(gdb) print s[11]
$12 = 32 ' '
(gdb) print s[12]
$13 = 110 'n'
(gdb) print s[13]
$14 = 105 'i'
(gdb) print s[14]
$15 = 110 'n'
(gdb) print s[15]
$16 = 101 'e'
(gdb) print s[16]
$17 = 9 '\t'
(gdb) print s[17]
$18 = 32 ' '
(gdb) print s[18]
$19 = 32 ' '
(gdb) print s[19]
$20 = 116 't'
(gdb) print s[20]
$21 = 101 'e'
(gdb) print s[21]
$22 = 110 'n'
(gdb) print s[22]
$23 = 0 '\000'
(gdb) ]
```
