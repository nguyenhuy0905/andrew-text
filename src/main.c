#include <stddef.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("argc: %d, argv: ", argc);
    for (int i = 0; i < argc; ++i) {
        printf("%s ", *(argv + i));
    }
    printf("\n");
    int retval = fflush(stdout);
    return retval;
}
