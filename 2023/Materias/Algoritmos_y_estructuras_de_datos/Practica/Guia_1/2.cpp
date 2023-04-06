// 2.	Dado un numero entero de la forma (AAAAMMDD), que representa una fecha valida 

/*

    Recibir entero de formato AAAAMMDD (Es valido)
    
    Procesar como string, separar en 3

    Mostrar dia, mes y año con switch o if

*/


#include <iostream>
#include <string>

using namespace std;

int main()
{
    //char list_of_months[12][11] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"}; 
    char date[8];
    
    //cout << "Ingrese una fecha expresada en numeros enteros, con el formato de AAAAMMDD: ";

    cin >> date;
    
    char year[5] = {'\0'};
    char month[3] = {'\0'};
    char day[3] = {'\0'};

    for(int i = 0; i < 8; i++)
    {
        if (i < 4)
            year[i] = date[i];

        else if (i < 6)
            month[i-4] = date[i];

        else if (i < 8)
            day[i-6] = date[i];
    }

    cout << "La fecha es: " << day << " del " << month << " del " << year;

    return 0;
}