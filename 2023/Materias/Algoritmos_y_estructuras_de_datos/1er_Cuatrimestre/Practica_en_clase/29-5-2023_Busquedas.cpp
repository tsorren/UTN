#include <iostream>

using namespace std;

// esta funcion devuelve la pos o -1 si no esta
int busquedaSecuencial(int vector[], int N, int buscado)
{
    int i = 0;
    while (i < N && vector[i] != buscado)
    {
        i++;
    }
    if (i == N)
    {
        return -1;
    }

    return i;
}

// esta funcion devuelve la pos o -1 si no esta
int busquedaBinaria(int vector[], int N, int buscado)
{
    int primero = 0;
    int ultimo = N - 1;
    int medio;
    while (primero <= ultimo)
    {
        medio = (primero + ultimo) / 2;
        if (vector[medio] == buscado)
        {
            return medio;
        }
        else if (vector[medio] > buscado)
        {
            ultimo = medio - 1;
        }
        else
        {
            primero = medio + 1;
        }
    }

    return -1;
}

int main()
{
    return 0;
}