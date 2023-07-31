/*
    Se dispone de un conjunto de boletas de inscripción de alumnos a examen en el mes de mayo.
    Cada boleta tiene los siguientes datos:
        nombre y apellido,
        número de legajo,
        código de materia,
        día,
        mes,
        año del examen.
    Los datos finalizan con un nombre y apellido =”x”.
    Desarrollar un programa que a partir del ingreso de las boletas mencionadas,
    por teclado, genere un archivo binario de inscripción de alumnos a exámenes finales DIAFINALES.DAT,
    según el siguiente diseño:
        a. Nro. de legajo (8 dígitos)
        b. Código de materia (6 dígitos)
        c. Día del examen (1..31)
        d. Mes del examen (1..12)
        e. Año del examen (4 dígitos)
        f. Nombre-Apellido (25caract)

    Dado el archivo binario generado en el ejercicio anterior,
    desarrolle un programa que solicitando por teclado un código de materia permita seleccionar
    todos los registros que se anotaron para rendirla y los grabe en otro archivo (MATFINALES.DAT), con el mismo diseño.
*/

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

    FILE* input = fopen("archivos/DIAFINALES.DAT", "rb");
    FILE* output = fopen("archivos/MATFINALES.DAT", "wb+");

    int codigoDeseado;

    cout << "Ingrese el código de materia deseado: ";
    cin >> codigoDeseado;

    int size = sizeof(boleta);
    while(fread(&alumno, size, 1, input))
    {
        if(alumno.codigoDeMateria == codigoDeseado)
        {
            fwrite(&alumno, size, 1, output);
        }
    }
    fclose(input);

    cout << endl << "Se ha creado un archivo \"MATFINALES.DAT\" que contiene los alumnos que deben rendir esa materia" << endl;
    cout << endl << "Los alumnos inscriptos a finales son: " << endl;

    fseek(output, 0, SEEK_SET);
    while(fread(&alumno, size, 1, output))
    {
        cout << "   " << alumno.nombreCompleto << endl;
    }
    cout << endl;
    fclose(output);

    return 0;
}