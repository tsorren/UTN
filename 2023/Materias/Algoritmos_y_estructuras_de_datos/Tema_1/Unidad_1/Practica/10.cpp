/*

    Se ingresa un conjunto de valores float, cada uno de los cuales representan el sueldo
    de un empleado, excepto el ultimo valor que es cero e indica el fin del conjunto. Se
    pide desarrollar un programa que determine e informe:
    • Cuantos empleados ganan menos $ 1.520.
    • Cuantos ganan $1.520 o mas pero menos de $2.780.
    • Cuantos ganan $2.780 o mas pero menos de $5.999.
    • Cuantos ganan $5.999 o mas.

    ----

    Cantidad indefinida de iteraciones -> While
    float sueldo == 0 -> break

    variables:
    float sueldo de empleado N

    Acumular empleados:
        sueldo < 1520
        sueldo >= 1520 && sueldo < 2780
        sueldo >=2780 && sueldo < 5999
        sueldo >= 5999

*/

#include <iostream>

using namespace std;

int main()
{
    float sueldoN;

    int sueldosBasicos = 0;
    int sueldosBajos = 0;
    int sueldosMedios = 0;
    int sueldosAltos = 0;

    int i = 0;

    cout << "Ingrese el sueldo del Empleado " << i + 1 << ": ";
    cin >> sueldoN;

    while(sueldoN != 0)
    {
        if(sueldoN < 1520)
        {
            sueldosBasicos++;
        }
        else if(sueldoN >= 1520 && sueldoN < 2780)
        {
            sueldosBajos++;
        }
        else if(sueldoN >= 2780 && sueldoN < 5999)
        {
            sueldosMedios++;
        }
        else if(sueldoN >= 5999)
        {
            sueldosAltos++;
        }
        i++;
    
        cout << "Ingrese el sueldo del Empleado " << i + 1 << ": ";
        cin >> sueldoN;        
    }

    cout << endl << endl;
    cout << sueldosBasicos << " empleados ganan menos $1.520" << endl;
    cout << sueldosBajos << " empleados ganan $1.520 o mas pero menos de $2.780" << endl;
    cout << sueldosMedios << " empleados ganan $2.780 o mas pero menos de $5.999" << endl;
    cout << sueldosAltos << " empleados ganan $5.999 o mas" << endl;
    cout << endl;

    return 0;
}