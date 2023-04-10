//3.	Realizar la suma de todos los números pares entre 2 y 10000

/*
    variable acumulador
    for loop
    mostrar resultado

*/

#include<iostream>

using namespace std;

int main()
{
    int acc = 0;

    for(int i = 2; i < 10000; i+=2)
    {
        acc += i;
    }

    cout << "La suma de todos los numeros pares entre 2 y 10000 es: " << acc;


    return 0;
}