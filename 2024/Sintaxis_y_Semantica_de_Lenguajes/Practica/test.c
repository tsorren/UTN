#include <stdio.h>

void draw(char c)
{
    printf("\x1b[H");
    for (int i = 0; i < 240; i++)
        putchar(i % 5 ? ' ' : c);
    
    printf("\n");
    printf("\n");
}
int main(void)
{
    printf("2");
    return 0;
}
