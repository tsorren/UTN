/*
    Dado 3 valores determinar e imprimir una leyenda según sea: "Forman un triangulo" o "No forman triangulo"

    Condicion para formar triangulo:
    Lado mayor > sumatoria de lados menores


    leer 3 valores enteros de lados
    verificar si cumplen con la condicion para ser triangulo
    imprimir leyenda

*/

#include<iostream>

using namespace std;

int main()
{
    int a, b, c = 0;
    int x, y, z = 0;
    cout << "Ingrese la longitud del primer lado: ";
    cin >> a;

    cout << "Ingrese la longitud del segundo lado: ";
    cin >> b;

    cout << "Ingrese la longitud del tercer lado: ";
    cin >> c;

    //Conseguir lado mayor

    if ((a > b) && (a > c))
    {
        x = a;
        y = b;
        z = c;
    }

    else if ((b > a) && (b > c))
    {
        x = b;
        y = a;
        z = c;
    }

    else 
    {
        x = c;
        y = a;
        z = b;
    }

    cout << "Lados: A: " << a << " - B: " << b << " - C: " << c << endl;
    cout << "Lado mayor: " << x << endl;
    cout << "Lados menores: " << y << " - " << z << endl;
    
    if (x <= (y+z))
    {
        cout << "Forman un triángulo" << endl;
    }
    
    else 
    {
        cout << "No forman un triángulo" << endl;
    }

    return 0;
}


