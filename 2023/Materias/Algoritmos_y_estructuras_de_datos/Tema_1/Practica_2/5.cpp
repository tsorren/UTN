/*
    Escriba un programa que permita ingresar la tirada de un par de dados 50 veces
    y muestre una lista donde se vea cuántas veces se dio cada uno de los resultados
    posibles. Por cada tirada se deberán ingresar 2 valores, cada uno representa el valor
    de un dado. El formato de la salida debe ser el siguiente:
    2 salió ... veces
    3 salió ... veces
    . . 12 salió ... veces

    resultados posibles: {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12} 11
*/


#include <iostream>

using namespace std;

int main()
{

    int N = 20;

    int i;
    int dado_1, dado_2, resultado;

    int resultadosRepetidos[11] = {0};

    for(i = 0; i < N; i++)
    {
        cout << "Tirada " << i+1 << ":" << endl;

        cout << "Primer dado: ";
        cin >> dado_1;

        cout << "Segundo dado: ";
        cin >> dado_2;

        resultado = dado_1 + dado_2;
        cout << "Resultado: " << resultado << endl << endl;

        resultadosRepetidos[resultado - 2]++;
    }

    cout << endl << "Resultados: " << endl;

    int resultadoActual;
    for(int k = 0; k < 11; k++)
    {
        resultadoActual = resultadosRepetidos[k];

        if(resultadoActual != 0)
        {
            cout << k + 2 << " salio " << resultadoActual;
            if(resultadoActual == 1)
            {
                cout << " vez" << endl;
            }
            else
            {
                cout << " veces" << endl;
            }
        }
    }

    return 0;
}