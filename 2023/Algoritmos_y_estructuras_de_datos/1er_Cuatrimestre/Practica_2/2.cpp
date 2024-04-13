/*
    Ingresar un valor entero N (< 30) y a continuación un conjunto de N elementos. Si el
    último elemento del conjunto tiene un valor menor que 10 imprimir los negativos y en
    caso contrario los demás
*/
#include <iostream>

using namespace std;

void CargaDeDatos(int[], int);
void MostrarDatos(int[], int);

int main()
{
    const int tamañoFisico = 30;
    int N; // Tamaño Lógico

    int conjunto[tamañoFisico] = {0};

    cout << "Ingrese el tamaño (menor que 30) del conjunto a cargar: ";
    cin >> N;

    CargaDeDatos(conjunto, N);
    MostrarDatos(conjunto, N);

    return 0;
}

void CargaDeDatos(int conj[], int tamaño)
{
    int i;
    cout << endl << "Carga de datos:" << endl;
    for (i = 0; i < tamaño; i++)
    {
        cout << "Elemento " << i + 1 << "°: ";
        cin >> conj[i];
    }
    return;
}

void MostrarDatos(int conj[], int tamaño)
{
    bool condicion = conj[tamaño - 1] < 10;
    int i;

    cout << endl;

    if (condicion)
    {
        cout << "Valores negativos del conjunto: " << endl;
    }
    else
    {
        cout << "Valores positivos del conjunto: " << endl;
    }

    for (i = 0; i < tamaño; i++)
    {
        if (condicion)
        {
            if (conj[i] < 0)
            {
                cout << conj[i] << endl;
            }
        }
        else
        {
            if (conj[i] > 0)
            {
                cout << conj[i] << endl;
            }
        }
    }
}