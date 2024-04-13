// 6.	Se ingresa una edad, mostrar por pantalla alguna de las siguientes leyendas:

/*
    variable edad
    usuario ingresa edad
    3 if
    1 else
    mostrar 

*/

#include<iostream>

using namespace std;

int main()
{
    int age;
    cout << "Ingrese su edad: ";
    cin >> age;

    if(age <= 12)
        cout << "menor";

    else if (age > 12 && age < 19)
        cout << "cadete";
    
    else if(age > 18 && age < 26)
        cout << "juvenil";

    else
        cout << "mayor";

    return 0;
}