/*

    Utilizando solo lo que hemos desarrollado en esta introduccion escriba un programa que
    calcule los cuadrados y los cubos de los números de 0 a 10 y los muestre por pantalla

    iterar desde el 0 al 10 inclusive
    mostrar su cuadrado y cubo

*/

#include <iostream>

using namespace std;

int main()
{
    int i;
    int n = 11;
    for(i = 0; i < n; i++)
    {
        cout << "El cuadrado de " << i << " es: " << i * i << endl;
        cout << "El cubo de " << i << " es: " << i * i * i << endl;
        cout << endl;
    }

    return 0;
}
