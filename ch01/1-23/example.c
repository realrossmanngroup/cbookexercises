#include <stdio.h>

int main()
{
    /* this is a multi line comment
    in my "*/" program */
    printf("this is a /* multiline comment */ inside a printf command");
    printf("the comment inside the printf command above is not a comment because it's inside my printf!"); // this is a single line comment that should be removed
}
