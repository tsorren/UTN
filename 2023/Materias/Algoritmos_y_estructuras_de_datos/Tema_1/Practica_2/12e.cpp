/*
    vector de 8 posiciones, ordenado
    encontrar la posición del legajo 456789 y sus calificaciones utilizando una busqueda binaria.
*/
#include <iostream>

using namespace std;

struct structNombreCompleto
{
    char nombre[20];
    char apellido[20];
};

struct structCalificaciones
{
    int nota1;
    int nota2;
    int nota3;
};

struct structAlumno
{
    int legajo;
    structNombreCompleto nombreCompleto;
    structCalificaciones calificaciones;

    /*
    char nombreCompleto[20][2];
    int calificaciones[3];
    */
};

int busquedaBinaria(structAlumno[], int, int);

void cargaDeAlumnos(structAlumno[], int);

int main()
{
    const int cantDeAlumnos = 10;
    int legajoBuscado = 456789;
    int alumnoBuscado;

    structAlumno alumnos[cantDeAlumnos];

    cargaDeAlumnos(alumnos, cantDeAlumnos);

    alumnoBuscado = busquedaBinaria(alumnos, cantDeAlumnos, legajoBuscado);
    if (alumnoBuscado != 1)
    {
        cout << "El alumno con legajo 456789 pertenece a la lista." << endl;
        cout << "Su posición en la lista es: " << alumnoBuscado << " (Alumno " << alumnoBuscado + 1 << ")" << endl;
        cout << "Sus calificaciones son: "
             << alumnos[alumnoBuscado].calificaciones.nota1 << ", "
             << alumnos[alumnoBuscado].calificaciones.nota2 << ", "
             << alumnos[alumnoBuscado].calificaciones.nota3 << endl;
    }
    else
    {
        cout << "El alumno de legajo 456789 no pertenece a la lista." << endl;
    }
    return 0;
}

void cargaDeAlumnos(structAlumno alumno[], int N)
{
    cout << "Cantidad de alumnos a cargar: " << N << endl
         << endl;
    int i;
    for (i = 0; i < N; i++)
    {
        cout << "Alumno " << i + 1 << "°: " << endl;

        cout << "Ingrese su número de legajo: ";
        cin >> alumno[i].legajo;

        /*
        cout << "Ingrese su nombre: ";
        cin >> alumno[i].nombreCompleto.nombre;

        cout << "Ingrese su apellido: ";
        cin >> alumno[i].nombreCompleto.apellido;
        */

        cout << "Ingrese su primera nota: ";
        cin >> alumno[i].calificaciones.nota1;

        cout << "Ingrese su segunda nota: ";
        cin >> alumno[i].calificaciones.nota2;

        cout << "Ingrese su tercera nota: ";
        cin >> alumno[i].calificaciones.nota3;

        cout << endl;
    }
}

int busquedaBinaria(structAlumno alumno[], int N, int legajoBuscado)
{
    int posMinima = 0;
    int posMaxima = N - 1;
    int posMedia;

    int legajoActual;

    while (posMinima <= posMaxima)
    {
        posMedia = (posMinima + posMaxima) / 2;
        legajoActual = alumno[posMedia].legajo;

        if (legajoActual == legajoBuscado)
        {
            return posMedia;
        }
        else
        {
            if (legajoActual < legajoBuscado)
            {
                posMinima = posMedia + 1;
            }
            else
            {
                posMaxima = posMedia - 1;
            }
        }
    }

    return -1;
}
