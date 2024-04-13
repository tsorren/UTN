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


int main()
{
    boleta alumno;
    int alumnoSize = sizeof(boleta);

    FILE* f = fopen("archivos/DIAFINALES.DAT", "wb");


    cout << "Ingrese los datos de la boleta a cargar:" << endl;
    cout << "Nombre y apellido del alumno (sin espacio, con guión bajo): ";
    cin >> alumno.nombreCompleto;

    while(strcmp(alumno.nombreCompleto, "x") != 0)
    {
        cout << "Nro de legajo: ";
        cin >> alumno.legajo;
        cout << "Código de materia: ";
        cin >> alumno.codigoDeMateria;
        
        cout << "Fecha del examen: " << endl;
        cout << "  Día: ";
        cin >> alumno.fecha.dia;
        cout << "  Mes: ";
        cin >> alumno.fecha.mes;
        cout << "  Año: ";
        cin >> alumno.fecha.año;
        
        fwrite(&alumno, alumnoSize, 1, f);

        cout << endl << "Ingrese los datos de la boleta a cargar:" << endl;
        cout << "Nombre y apellido del alumno (sin espacio, con guión bajo): ";
        cin >> alumno.nombreCompleto;
    }
    fclose(f);

    return 0;
}