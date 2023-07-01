/*
    Dado un número N (<30), genere e informe un vector VEC de N elementos que 
    contenga los primeros N números naturales pares.
*/
#include <iostream>

using namespace std;

void GeneradorDePares(int[], int);
void MostrarDatos(int[], int);

int main()
{
    const int tamañoFisico = 30;    
    int N; // Tamaño lógico

    int VEC[tamañoFisico] = {0};


    cout << "Ingrese la cantidad (menor que 30) de números pares a generar: ";
    cin >> N;

    GeneradorDePares(VEC, N);
    MostrarDatos(VEC, N);
    return 0;
}

void GeneradorDePares(int vector[], int tamaño)
{
    int i;
    for(i = 0; i < tamaño; i++)
    {
        vector[i] = (i + 1) * 2; // Los numeros naturales no incluyen al cero. Los numeros pares son de la forma 2k -> i+1 = k
    }
    return;
}

void MostrarDatos(int vector[], int tamaño)
{
    int i;

    cout << "Los primeros " << tamaño << " números naturales pares son {";

    for(i = 0; i < tamaño; i++)
    {
        cout << vector[i];

        if(i < (tamaño - 1))
        {
            cout << ", ";
        }

        else
        {
            cout << "}" << endl;
        }
    }   

    return;
}