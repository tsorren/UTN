/*
    En un club social se abrieron las inscripciones de los socios distintos deportes, 
    codificados de 1 a 20, y de cada inscripción se conoce número de socio y código de 
    deporte. 
    Las inscripciones finalizan con un número de socio igual a 0. // While
    Se pide informar: 
    • la cantidad de inscriptos en cada deporte // PUP
    • el código de deporte con la mayor cantidad de inscriptos // MAX

*/

#include <iostream>

using namespace std;

struct inscripcion
{
    int numero;
    int codigo;
};


int MayorCantidadDeInscriptos(int [], int);

int main()
{
    int inscr_a_deportes[20] = {0};
    int deporte_popular;
    inscripcion inscr;

    cout << "INSCRIPCIONES: " << endl;
    cout << "Ingrese el número de socio: ";
    cin >> inscr.numero;

    while(inscr.numero != 0)
    {        
        cout << "Ingrese el código del deporte: ";
        cin >> inscr.codigo;
        inscr_a_deportes[inscr.codigo]++;
        
        cout << endl << "Ingrese el número de socio: ";
        cin >> inscr.numero;
    }

    deporte_popular = MayorCantidadDeInscriptos(inscr_a_deportes, 20);
    cout << "El código de deporte con la mayor cantidad de inscriptos es: " << deporte_popular;

    return 0;
}


int MayorCantidadDeInscriptos(int deportes[], int N)
{
    int max = 0;
    int codigo;
    int i;

    for(i = 0; i < N; i++)
    {
        if(max < deportes[i])
        {
            max = deportes[i];
            codigo = i;
        }
    }
    return codigo;
}