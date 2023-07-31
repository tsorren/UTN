#include <iostream>
#include <cstring>

using namespace std;

struct boleta
{
    int legajo;
    int codigoDeMateria;

    struct fecha
    {
        int dia;
        int mes;
        int año;
    } fecha;

    char nombreCompleto[25+1];
};


int main()
{
    boleta alumno;

    FILE* f = fopen("archivos/DIAFINALES.DAT", "wb+");