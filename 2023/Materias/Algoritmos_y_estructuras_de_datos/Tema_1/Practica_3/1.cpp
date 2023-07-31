/*
    Se conoce de cada alumno de un curso los siguientes datos: legajo (8digitos) y las notas de 
    2 parciales (0..10), que finaliza con un legajo negativo.  //While
    Se pide desarrollar un programa que ingrese los datos de los alumnos por teclado y grabe 
    un archivo binario CURSO.BIN con una línea por cada alumno, con el número de legajo y su  // struct legajo, promedio
    promedio (real). // float

*/

#include <iostream>

using namespace std;

struct structAlumno
{
    int legajo;
    float promedio;
};

float CalcularPromedio(float, float);

int main()
{
    structAlumno alumno;
    int tamAlumno = sizeof(structAlumno);
    int legajo;
    float nota1;
    float nota2;
    float promedio;
    FILE* f = fopen("archivos/ej1_CURSO.BIN", "wb");;

    cout << "CARGA DE DATOS:" << endl << endl;
    cout << "Ingrese el legajo del alumno: ";
    cin >> legajo;

    
    while(legajo != 0)
    {
        cout << "   Ingrese la nota de su primer parcial: ";
        cin >> nota1;
        cout << "   Ingrese la nota de su segundo parcial: ";
        cin >> nota2;

        promedio = CalcularPromedio(nota1, nota2);
        cout << "Su promedio es: " << promedio << endl << endl;
        
        alumno.legajo = legajo;
        alumno.promedio = promedio;

        fwrite(&alumno, tamAlumno, 1, f);
        
        cout << "Ingrese el legajo del alumno: ";
        cin >> legajo;
        
    }
    fclose(f);
    cout << endl << "LA CARGA DE DATOS HA FINALIZADO" << endl;

    return 0;
}

float CalcularPromedio(float n1, float n2)
{
    return (n1+n2)/2;
}