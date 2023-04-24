/*

    Dados 50 números enteros, informar el promedio de los mayores que 100, y la suma de los menores que -10

    Promedio: 
        Sumatorioa de los mayores que 100, divididos la cantidad de números mayores que 100

    2 listas, 1 de enteros mayores a 50, otra de menores a -10
    

*/

/* SOLUCIÓN 1
#include<iostream>

using namespace std;

int main()
{
    int entrada[50];

    int mayores[50] = {0};
    int menores[50] = {0};
    
    int mayoresI = 0;
    int menoresI = 0;
    cout << "Ingrese 50 enteros: " << endl;

    for(int i = 0; i < 50; i++)
    {
        cout << " " << i + 1 << ": ";
        cin >> entrada[i];

        if(entrada[i] > 100)
        {
            mayores[mayoresI] = entrada[i];
            ++mayoresI;   
        }
        else if (entrada[i] < -10)
        {
            menores[menoresI] = entrada[i];
            menoresI++;
        }
    }
    
    int promedioMayores = 0;
    int sumatoriaMenores = 0;

    for(int i = 0; i < mayoresI; i++)
    {
        promedioMayores = promedioMayores + mayores[i];
    }
    promedioMayores = promedioMayores / mayoresI;

    for(int i = 0; i < menoresI; i++)
    {
        sumatoriaMenores = sumatoriaMenores + menores[i];
    }

    cout << "-  " << mayoresI << " Números son mayores que 100, y su promedio es: " << promedioMayores << endl;
    cout << "-  " << menoresI << " Numeros son menores que -10, y su sumatoria es: " << sumatoriaMenores << endl;
    
    return 0;
}

*/

// SOLUCION 2
#include<iostream>

using namespace std;

int main()
{

    int numero;

    int mayores = 0;
    int cMayores = 0;

    int menores = 0;
    int cMenores = 0;

    cout << "Ingrese 50 enteros: " << endl;

    int i;
    for(i = 0; i < 50; i++)
    {
        cout << " " << i + 1 << ": ";
        cin >> numero;

        if(numero > 100)
        {
            mayores += numero;
            cMayores++;
        }
        else if (numero < -10)
        {
            menores += numero;
            cMenores++;
        }
    }
    
    int promedioMayores = mayores/cMayores;

    cout << "-  " << cMayores << " Números son mayores que 100, y su promedio es: " << promedioMayores << endl;
    cout << "-  " << cMenores << " Numeros son menores que -10, y su sumatoria es: " << menores << endl;
    
    return 0;
}

