/*
    Escriba un programa que pida al usuario dos números e informe la suma, la resta, el
    producto y el cociente de los mismos
*/

#include<iostream>

using namespace std;

int main()
{
    int a = 0;
    int b = 0;

    cout << "Ingrese un entero: ";
    cin >> a;
    cout << "Ingrese un entero: ";
    cin >> b;

    cout << "Suma: " << a + b << endl << "Resta: " << a - b << endl << "Producto: " << a * b << endl << "Cociente: " << a/b << endl;

    return 0;
}
