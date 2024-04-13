/*
    Dado un conjunto (<100) de valores enteros de los cuales el último es cero y no
    debe procesarse:
    a. informe el valor mínimo, su posición dentro del conjunto, si el mínimo no es
    único, informar todas las posiciones donde se encuentre.

    b. informe el producto de los elementos impares que ocupen posición par.
*/
#include <iostream>

using namespace std;

struct minimo
{
    int valor;
    int posiciones[100];
    int cantidadDePosiciones;
};

void ProcesamientoDeDatos(int[], const int, int &, minimo &, int &);

void InformarMinimo(minimo);
void InformarProducto(int);

int main()
{
    const int tamañoFisico = 100;
    int conjunto[tamañoFisico] = {0};
    int tamañoLogico = 0;
    int productoDeElementos = 0;

    minimo valorMinimo = {0, {0}, 0};

    ProcesamientoDeDatos(conjunto, tamañoFisico, tamañoLogico, valorMinimo, productoDeElementos);

    if (valorMinimo.cantidadDePosiciones != 0)
    {
        InformarMinimo(valorMinimo);
        InformarProducto(productoDeElementos);
    }
    else
    {
        cout << "El conjunto no posee elementos" << endl;
    }

    return 0;
}

void ProcesamientoDeDatos(int conj[], const int tFisico, int &tLogico, minimo &min, int &prod)
{
    int i = 0;
    int valor;

    cout << "Ingrese el valor del elemento " << i + 1 << ": ";
    cin >> valor;

    while ((valor != 0) && (i < tFisico))
    {
        conj[i] = valor;

        // Minimo del conjunto
        if (min.valor > valor)
        {
            min = {valor, {i}, 1}; // Nuevo Minimo
        }
        else if (min.valor == valor)
        {
            min.posiciones[min.cantidadDePosiciones] = i;
            min.cantidadDePosiciones++;
        }

        // Producto de elementos pares y valor impar
        if (((i % 2) == 0) && (valor % 2 != 0)) // valor % 2 puede ser == 0, == 1 o == -1
        {
            if (prod != 0)
            {
                prod *= valor;
            }
            else
            {
                prod = valor;
            }
        }

        i++;
        cout << "Ingrese el valor del elemento " << i + 1 << ": ";
        cin >> valor;
    }
    return;
}

void InformarMinimo(minimo min)
{
    cout << endl
         << "El valor mínimo del conjunto es " << min.valor << endl;

    if (min.cantidadDePosiciones == 1)
    {
        cout << "Se encuentra en la posición " << min.posiciones[0] << endl
             << "Es único" << endl;
        return;
    }
    // Else tacito

    cout << "Se encuentra en las posiciones ";

    for (int i = 0; i < min.cantidadDePosiciones; i++)
    {
        cout << min.posiciones[i];

        if (i != min.cantidadDePosiciones - 1)
        {
            cout << ", ";
        }

        else
        {
            cout << endl;
        }
    }
    return;
}

void InformarProducto(int prod)
{
    cout << endl << "El producto de los elementos impares que ocupan posición par en el conjunto es: " << prod << endl;
    return;
}