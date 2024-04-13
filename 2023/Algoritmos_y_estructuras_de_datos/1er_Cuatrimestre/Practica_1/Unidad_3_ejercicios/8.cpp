/*

    Escriba un programa que reciba un numero entero de 5 digitos, que separe el numero en
    sus digitos y los muestre por pantalla, uno por línea comenzando por el mas significativo en
    la primera línea.

    recibir entero de 5 digitos como char
    iterar cadena imprimiendo cada valor 

*/

#include <iostream>

using namespace std;

int main()
{
    char digitos[5];

    cout << "Ingrese un número entero de 5 digitos: ";
    cin >> digitos;

    int i;
    int n = 5;

    cout << endl;
    
    for(i = 0; i < n; i++)
    {
        cout << digitos[i] << endl;
    }
    cout << endl;

    return 0;
}
