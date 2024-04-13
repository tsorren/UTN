/*

   Dado un curso se conoce el número de legajo y nota (0..10) de los alumnos.
        •informar de cada curso la cantidad de alumnos que tuvieron como nota 0, 1, ...,9, 10
    Si el nro de legajo es 0, se deja de procesar nueva información.
*/

#include <iostream>

using namespace std;

struct alumno
{
    int nLegajo; 
    int nota;
};

struct curso
{
    alumno alumno[100];
};

int main()
{
    curso K1029;
    int i = 0;

    int notas[11] = {0};
    int notaActual;

    cout << "Alumno 1:" << endl;
    cout << "Ingrese el numero de legajo: ";
    cin >> K1029.alumno[i].nLegajo;

    while(K1029.alumno[i].nLegajo != 0)
    {
        cout << "Ingrese la nota: ";
        cin >> K1029.alumno[i].nota;
        notaActual = K1029.alumno[i].nota;

        notas[notaActual]++;

        i++;
        
        cout << endl << "Alumno " << i+1 << endl;
        cout << "Ingrese el numero de legajo: ";
        cin >> K1029.alumno[i].nLegajo;
    }

    cout << endl;

    for(int k = 0; k < 11; k++)
    {
        if(notas[k] != 0)
        {
            cout << "Alumnos con nota " << k << ": " << notas[k] << endl;
        }
    }

    return 0;
}