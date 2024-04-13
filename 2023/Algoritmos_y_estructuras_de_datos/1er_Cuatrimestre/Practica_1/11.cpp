/*

    Dados N valores informar el mayor, el menor y en que posición del conjunto fueron
    ingresados.

    tipo de valor "valores": indefinido -> A decisión del programador -> Entero

    iteración N veces, -> decisión

    posición del conjunto: numero de iteración


*/

#include <iostream>

using namespace std;

int main()
{
    int N = 20;

    int valor;

    int mayor = 0;
    int mayorPos;

    int menor = 0;
    int menorPos;

    int i;
    for(i = 0; i < N; i++)
    {
        cout << i << " - Ingrese un valor: ";
        cin >> valor;

        if(valor > mayor)
        {
            mayor = valor;
            mayorPos = i;
        }
        if (valor < menor || i == 0)
        {
            menor = valor;
            menorPos = i;
        }
    }

    cout << "Mayor numero: " << mayor << " - " << "Posición: " << mayorPos << endl;
    cout << "Menor numero: " << menor << " - " << "Posición: " << menorPos << endl;


    return 0;
}