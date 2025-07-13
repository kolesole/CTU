/*#include <stdio.h>

int main() {
    int result, a = 4, b = 4;
    asm volatile (
        "mov %1, %%eax;"
        "add %2, %%eax;"
        "mov %%eax, %0;"
        : "=r"(result)
        : "r"(a), "r"(b)
        : "cc"
    );

    printf("%d\n", result);

    return 0;
}*/

#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Hello world\n");
    return 0;
}
