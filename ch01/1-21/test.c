#include <stdio.h>

int f(char s[]) {
    printf("Size inside the function: %d\n", sizeof(s));
}

int main() {
    char s[] = "Hello, here is my super fancy string!\n";
    printf("Size outside the function: %d\n", sizeof(s));
    f(s);
}
