#include <stdio.h>

void func(char c, ...)
{
    printf("%c", c);
    return;
}

int main(void)
{
    func('a');
    return 0;
}
