/*
Dado el archivo binario generado en el ejercicio anterior,
desarrolle un programa que genere un archivo ordenado por número de legajo
(cada registro debe tener los campos legajo y apellido y nombre)
para todos los alumnos que se inscribieron una o más veces.
Cada legajo debe ocupar una posición única y predecible en el archivo.
El intervalo de los legajos es 80001 a 110000, pueden no presentarse todos los legajos.


*/

#include <iostream>
#include <cstring>

using namespace std;

struct fecha
{
        int dia;
        int mes;
        int año;
};

struct boleta
{
    int legajo;
    int codigoDeMateria;

    fecha fecha;

    char nombreCompleto[25+1];
};

struct registro
{
    int legajo;
    char nombreCompleto[25+1];
};

int main()
{
    FILE* input = fopen("archivos/DIAFINALES.DAT", "rb");
    FILE* output = fopen("archivos/DATOSORDENADOS.DAT", "wb+");

    boleta alumno;
    registro reg;

    int legajoActual;

    int sizeAlumno = sizeof(boleta);
    int sizeReg = sizeof(registro);
    int sizeLegajo = sizeof(int);

    while(fread(&alumno, sizeAlumno, 1, input))
    {
        reg.legajo = alumno.legajo;
        strcpy(reg.nombreCompleto, alumno.nombreCompleto);

        fseek(output, (reg.legajo - 80001) * sizeReg, SEEK_SET);
        fread(&legajoActual, sizeLegajo, 1, output);

        if(legajoActual != reg.legajo)
        {
            fseek(output, (reg.legajo - 80001) * sizeReg, SEEK_SET);
            fwrite(&reg, sizeReg, 1, output);
        }
        else
        {
            cout << "El alumno " << reg.nombreCompleto << " ya existe en la lista" << endl;
        }

    }
    fclose(input);

    fseek(output, 0, SEEK_SET);
    while(fread(&reg, sizeReg, 1, output))
    {
        if(reg.legajo >= 80001 && reg.legajo <= 110000)
        {
            cout << "Legajo: " << reg.legajo << endl << "Nombre: " << reg.nombreCompleto << endl << endl;
        }
    }
    fclose(output);
    return 0;
}