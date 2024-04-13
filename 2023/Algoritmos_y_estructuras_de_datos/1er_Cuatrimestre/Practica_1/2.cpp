// 2.	Dado un numero entero de la forma (AAAAMMDD), que representa una fecha valida 

/*

    Recibir entero de formato AAAAMMDD (Es valido)
    
    Procesar, separar en 3

    Mostrar dia, mes y año

*/


#include <iostream>
#include <string>

using namespace std;

int main()
{     
    int fecha;
    
    cout << "Ingrese una fecha expresada en numeros enteros, con el formato de AAAAMMDD: ";

    cin >> fecha;
    
    int año = fecha / 10000;
    int mes = (fecha / 100) % 100;
    int dia = fecha % 100;


    cout << "La fecha es: " << dia << " del " << mes << " del " << año;

    return 0;
}