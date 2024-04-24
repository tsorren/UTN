#include <stdio.h>
#include <Windows.h>

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
    printf("\x1b[2J");
    draw('o');
    return 0;
}