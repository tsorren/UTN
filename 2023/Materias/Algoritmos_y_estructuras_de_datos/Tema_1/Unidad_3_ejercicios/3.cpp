/*
 
    Imprima un programa que imprima los números del 1 al 4 en una misma línea, hágalo de las
    formas siguientes:
    a. Utilizando un solo operador de inserción de flujo
    b. Una única sentencia con 4 operadores de inserción de flujo
    c. Utilizando cuatro sentencias

*/

#include <iostream>

using namespace std;

int main()
{
    cout << "1, 2, 3, 4\n";
    
    cout << "1, " << "2, " << "3, " << "4\n";
    
    cout << "1, ";
    cout << "2, ";
    cout << "3, ";
    cout << "4" << endl;


    return 0;
}

