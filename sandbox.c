#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    char *str1 = "Hello, World\n";
    char str2[15] = {
        72, 101, 108, 108, 111, 44, 32, 87,
        111, 114, 108, 100, 33, 10, 0
        };
    fputs(str1, stdout);
    fputs(str2, stdout);
}
