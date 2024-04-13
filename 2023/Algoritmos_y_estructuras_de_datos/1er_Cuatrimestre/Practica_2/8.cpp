/*
Dado un numero N (<50), y un vector VEC de N valores enteros positivos ordene el
contenido del vector y lo informe, aplicando el procedimiento Burbujeo:
    • en orden ascendente
    • en orden descendente
*/

#include <iostream>

using namespace std;

void CargarVector(int[], int);
void MostrarVector(int[], int);

void BurbujeoAscendiente(int[], int); 
void BurbujeoDescendiente(int[], int);

int main()
{
    const int tamañoFisico = 50;
    int N;

    int VEC[tamañoFisico];

    cout << "Ingrese el tamaño del vector: ";
    cin >> N;

    CargarVector(VEC, N);

    cout << endl << "Burbujeo ascendiente..." << endl;
    BurbujeoAscendiente(VEC, N);
    MostrarVector(VEC, N);

    cout << endl << "Burbujeo descendiente..." << endl;
    BurbujeoDescendiente(VEC, N);
    MostrarVector(VEC, N);

    return 0;
}

void CargarVector(int vector[], int N)
{
    int i;
    for(i = 0; i < N; i++)
    {
        cout << "Ingrese el valor de la posición " << i+1 << ": ";
        cin >> vector[i];
    }
}

void MostrarVector(int vector[], int N)
{
    int i;

    for(i = 0; i < N; i++)
    {
        cout << vector[i] << ", ";
    }
    cout << endl;
}

void BurbujeoAscendiente(int vector[], int N)
{
    int i, j, aux;
    for(i = 1; i < N; i++)
    {
        for(j = 1; j <= N-i; j++)
        {
            if(vector[j-1] > vector[j])
            {
                aux = vector[j-1];
                vector[j-1] = vector[j];
                vector[j] = aux;
            }
        }
    }

    return;
}

void BurbujeoDescendiente(int vector[], int N)
{
    int i, j, aux;
    for(i = 1; i < N; i++)
    {
        for(j = 1; j <= N-i; j++)
        {
            if(vector[j-1] < vector[j])
            {
                aux = vector[j-1];
                vector[j-1] = vector[j];
                vector[j] = aux;
            }
        }
    }

    return;
}
