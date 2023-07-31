/*
    Dados los siguientes registros crear un vector de 20 posiciones sin orden. Para el caso 
    a imprimir: 
    
    a. La posición 8 del vector, campo dia 
    b. La posición 0 del vector campo nombre 
    
    c. La posición del LEGAJO 456789 y sus calificaciones 
    d. La posición del primer apellido “xxxxx”, el legajo, el nombre y las notas, para lo cual 
    se le pide que programe una función. 
    e. considere que el vector se encuentra ordenado, utilice la función de búsqueda 
    binaria para encontrar el legajo del punto c, utilice los parámetros correctamente.
*/
#include <iostream>
#include <cstring>

using namespace std;

struct structFecha
{
    int dia;
    int mes;
    int año;
};

struct structRegistro
{
    char nombre[20+1];
    structFecha fechaNacimiento;
};

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

void SepararInfo();

void CargarRegistros(structRegistro[], int);

void CargaDeAlumnos(structAlumno[], int);
int BusquedaSecuencial(structAlumno[], int, int);
int BusquedaSecuencial(structAlumno[], int, char[]);
int BusquedaBinaria(structAlumno[], int, int);

void InformarAlumno(structAlumno[], int, int);

int main()
{
    
    structRegistro reg[20];
    CargarRegistros(reg, 20);
    // punto a
    cout << "El campo \"dia\" de la posición 8 del vector es: " << reg[8].fechaNacimiento.dia << endl;
    
    // punto b
    cout << "El campo \"nombre\" de la posición 0 del vector es: " << reg[0].nombre << endl;

    SepararInfo();
    
    // punto c
    const int cantDeAlumnos = 10;
    int legajoBuscado = 456789;
    int alumnoBuscado;
    char apellidoBuscado[20] = "Guzman"; 
    structAlumno alumnos[cantDeAlumnos];
    
    CargaDeAlumnos(alumnos, cantDeAlumnos);
    SepararInfo();

    alumnoBuscado = BusquedaSecuencial(alumnos, cantDeAlumnos, legajoBuscado);
    InformarAlumno(alumnos, cantDeAlumnos, alumnoBuscado);
    SepararInfo();

    // punto d
    alumnoBuscado = BusquedaSecuencial(alumnos, cantDeAlumnos, apellidoBuscado);
    InformarAlumno(alumnos, cantDeAlumnos, alumnoBuscado);
    SepararInfo();


    // punto e
    alumnoBuscado = BusquedaBinaria(alumnos, cantDeAlumnos, legajoBuscado);
    InformarAlumno(alumnos, cantDeAlumnos, alumnoBuscado);
    SepararInfo();

    return 0;
}

void SepararInfo()
{    
    cout << endl <<  "-----------------------------" << endl << endl;
    return;
}

void CargarRegistros(structRegistro reg[], int N)
{
    for(int i = 0; i < N; i++)
    {
        cout << "Registro " << i << ":" << endl;
        cout << "   Ingrese el nombre: ";
        cin >> reg[i].nombre;

        cout << "   Fecha de nacimiento:" << endl;
        cout << "     Día: ";
        cin >> reg[i].fechaNacimiento.dia;

        cout << "     Mes: ";
        cin >> reg[i].fechaNacimiento.mes;

        cout << "     Año: ";
        cin >> reg[i].fechaNacimiento.año;
        cout << endl;
    }
    SepararInfo();


    return;
}

void CargaDeAlumnos(structAlumno alumno[], int N)
{
    cout << "Cantidad de alumnos a cargar: " << N << endl
         << endl;
    int i;
    for (i = 0; i < N; i++)
    {
        cout << "Alumno " << i + 1 << "°: " << endl;

        cout << "Ingrese su número de legajo: ";
        cin >> alumno[i].legajo;

        
        cout << "Ingrese su nombre: ";
        cin >> alumno[i].nombreCompleto.nombre;

        cout << "Ingrese su apellido: ";
        cin >> alumno[i].nombreCompleto.apellido;
        

        cout << "Ingrese su primera nota: ";
        cin >> alumno[i].calificaciones.nota1;

        cout << "Ingrese su segunda nota: ";
        cin >> alumno[i].calificaciones.nota2;

        cout << "Ingrese su tercera nota: ";
        cin >> alumno[i].calificaciones.nota3;

        cout << endl;
    }
    
    return;
}

int BusquedaSecuencial(structAlumno vec[], int N, int legajoBuscado)
{
    int i;
    for(i = 0; i < N; i++)
    {
        if(vec[i].legajo == legajoBuscado)
        {
            return i;
        }
    }
    return -1;
}

int BusquedaSecuencial(structAlumno vec[], int N, char apellidoBuscado[])
{
    int i;
    for(i = 0; i < N; i++)
    {
        if(strcmp(vec[i].nombreCompleto.apellido, apellidoBuscado) == 0)
        {
            return i;
        }
    }
    return -1;
}

int BusquedaBinaria(structAlumno alumno[], int N, int legajoBuscado)
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

void InformarAlumno(structAlumno alumno[], int N, int alumnoBuscado)
{
    if (alumnoBuscado != -1)
    {
        cout << "Alumno: " << endl;
        cout << "   Nombre: " << alumno[alumnoBuscado].nombreCompleto.apellido << " " << alumno[alumnoBuscado].nombreCompleto.nombre << endl;
        cout << "   Legajo: " << alumno[alumnoBuscado].legajo << endl;
        cout << "   Posición: " << alumnoBuscado << " (Alumno " << alumnoBuscado + 1 << ")" << endl;
        cout << "   Calificaciones: "
             << alumno[alumnoBuscado].calificaciones.nota1 << ", "
             << alumno[alumnoBuscado].calificaciones.nota2 << ", "
             << alumno[alumnoBuscado].calificaciones.nota3 << endl;
    }
    else
    {
        cout << "El alumno no pertenece a la lista." << endl;
    }
    return;
}