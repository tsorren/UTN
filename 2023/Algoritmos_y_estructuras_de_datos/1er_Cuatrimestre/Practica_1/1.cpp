// 1.	Dados dos valores enteros A y B, informar la suma, la resta y el producto.


/*

    1: Entrada de datos
        pedirle al usuario enteros A y B

    2: Procesamiento
        suma resta y producto

    3: Salida de datos
        mostrar los resultados

*/

#include <iostream>

using namespace std;

int main()
{
    //Enteros
    int a, b;

    cout << "Ingrese un valor entero para A: ";
    cin >> a;

    cout << "Ingrese un valor entero para B: ";
    cin >> b;

    cout << endl << "La suma entre A y B es: " << a + b << endl;
    cout << "La diferencia entre A y B es: " << a - b << endl;
    cout << "El producto entre A y B es: " << a * b << endl;

    return 0;
}