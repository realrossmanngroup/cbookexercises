`1-19.c` doesn't work, and I can't figure it out. EDIT: I was using sizeof to find the size of the array because my reverse function that I came up with needed this information. However, sizeof was measuring the side of a POINTER, not the array. DOH!!!

I learned with the following code what I did wrong:

```
#include <stdio.h>

int f(char s[]) {
    printf("Size inside the function: %d\n", sizeof(s));
}

int main() {
    char s[] = "Hello, here is my super fancy string!\n";
    printf("Size outside the function: %d\n", sizeof(s));
    f(s);
}
```

`1-19_fixed.c` works but still required me to mess with malloc to return the reversed item. 

`1-19_external_global_variable_version.c` was an easier version once I realized I could use global variables. I did not know how to do that before so I spent an hour googling and learning how malloc works & dynamic memory assignment works so I could get my function to return a character array without knowing the size of it ahead of time, when all I had to do was declare a global variable. :( So technically both programs work but the external variable version is "simpler" to me even if it results in more lines of code. I feel more comfortable being able to actually store the reversed text in a variable.

This function still sucks because it requires the user to specify the length of the array to reverse a string, so that's what `1-19_external_variable+better_reverse.c` is for. This one has a proper reverse function that only requires 1 argument, the character array you are looking to reverse.

Having 3 programs here is probably silly but I want to be able to look back at my progress later and remember struggling at this exercise so when I am smarter later I can smile at it. 
