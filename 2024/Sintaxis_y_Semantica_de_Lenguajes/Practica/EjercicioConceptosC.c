#include <stdio.h>
#include <stdlib.h>

enum operaciones {abrir, modificar, cerrar};
struct registro { int id; float cant;} registro;

extern float factor;
static float valor = 3.2;

int f1(int param) {
    int abrir;
    static int registro;
    struct registro reg = {3};
    return reg.id + abrir + registro;
}

int main(void)
{
    enum variantes {primera, segunda = 10, tercera};
    struct registro {double x; double y;} segunda;
    union variantes {char a; long b;} primera;

    for (int i = 0; i < tercera; i++) {
    int tmp = f1(i);
    printf("%d\n", tmp);
    }
    final:
        return EXIT_SUCCESS;
}