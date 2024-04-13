/*
    Dado un triangulo representado por sus lados L1, L2, L3, determinar e imprimir una leyenda según sea: equilátero, isóceles, o escaleno.

    Condiciones:
        Equilátero:     3 lados iguales
        Isóceles:       2 lados iguales
        Escaleno:       0 lados iguales


    Recibir 3 valores enteros, que representan longitudes de lados

    Comparar lados del triangulo
    Si (a == b) o (a == c) ->   Isóceles
        else ->                 Escaleno
    Si (a == b) y (a == c) ->   Equilátero
    

    Mostrar en pantalla la leyenda pertinente


*/

#include<iostream>

using namespace std;

int main()
{
    int a, b, c = 0;

    cout << "Ingrese la medida del lado 1: ";
    cin >> a;

    cout << "Ingrese la medida del lado 2: ";
    cin >> b;

    cout << "Ingrese la medida del lado 3: ";
    cin >> c;
    
    if ((a == b) && (a == c))
    {
        cout << "El triángulo es Equilátero" << endl;
    }

    else if ((a == b) || (a == c))
    {
        cout << "El triángulo es Isóceles" << endl;
    }
    else
    {
        cout << "El triángulo es Escaleno" << endl;
    }



    return 0;
}
