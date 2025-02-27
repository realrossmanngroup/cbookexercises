countwords_2025.c is the program that the book provides.

countwords_2025_FIXED.c is the program modified with
bugfixes so that it works better. The book's exercise 1-11 
asks us to come up with a methodology for uncovering
problems with the book's program. This program
doesn't tell the difference between normal letters
and jibberish such as : # % or *. 

While we cannot remove all cases of non-words being 
counted as words, we can remove obvious cases. 
If I type jibberish such as &^*&@^*%@%^@% @(^@&(^  #@@## , 
the program counts that as if I typed three words; even though those
are not words! Adding logic to consider us outside
a word when someone types those random characters
using the ascii manpage removes many such use cases. 

However, this is not foolproof. While we've removed
cases where there is 100% certainty that something
is not a word from being considered, one can still 
type letters of gibberish, such as fuibruirfr
or wrw4fwgwr and the program will consider this a word.

To get around this, I would need to add the ability
to check each word against a dictionary. this is 
chapter 1. when I complete the book, I will come back
to this and come up with a way for this to check
a dictionary for each word & only allow it to be counted
if it is confirmed to be a word. 
