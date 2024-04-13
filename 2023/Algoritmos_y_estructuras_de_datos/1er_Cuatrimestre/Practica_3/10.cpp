/*
    Dado el archivo ‘ALUMNOS.dat’ con los datos personales de alumnos ordenado por legajo, 
    con el siguiente diseño: 
    a. Legajo (8 digitos) 
    b. Apellido y nombre ( 30 caracteres) 
    c. Domicilio (20 caracteres) 
    d. Código postal (4 digitos) 
    e. Teléfono (10 caracteres) 
    f. Año de ingreso (4 digitos) 

    Y otro archivo sin orden que el mencionado llamado ‘NOVEDADES.dat’, con cantidad 
    máxima de registros es 100.
    Posee las actualizaciones (altas, bajas, y modificaciones) a ser aplicadas,
    donde cada registro contiene además de todos los campos de Alumnos.dat,
    un código de operación (‘A’= Alta, ‘B’= Baja, ‘M’= Modificación). 
    Se pide desarrollar todos los pasos necesarios para realizar un programa que genere un 
    archivo actualizado ‘ALUMACTU.dat’ con el mismo diseño.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

struct alumno
{
    int legajo;
    char apellidoNombre[30+1];
    char domicilio[20+1];
    int codigoPostal;
    char telefono[10+1];
    int añoDeIngreso;
};

struct novedad
{
    alumno al;
    char codigoDeOp;
};

void CargarAlumnos(FILE*);
void CargarNovedades(FILE*);

int CalcularTamaño(FILE*, int);

void LeerArchivo(FILE*, alumno[], int, int);
void LeerArchivo(FILE*, novedad[], int, int);

void OrdenarPorLegajo(FILE*, alumno[], int, int);
void OrdenarPorLegajo(FILE*, novedad[], int, int);

// int BusquedaBinaria(novedad[], int, int, char&);
void ActualizarAlumnos(FILE*, alumno[], int, novedad[], int);
void MostrarDatosActualizados(FILE*);

int main()
{
    FILE* alumFile = fopen("archivos/ej10_ALUMNOS.dat", "rb+");
    FILE* novFile = fopen("archivos/ej10_NOVEDADES.dat", "rb+");
    FILE* actFile = fopen("archivos/ej10_ALUMACTU.dat", "wb+");

    const int alumnoStructSize = sizeof(alumno);
    const int novedadStructSize = sizeof(novedad);
    
    // CargarAlumnos(alumFile);
    // CargarNovedades(novFile);

    int alumnosTam = CalcularTamaño(alumFile, alumnoStructSize);
    alumno alumnos[alumnosTam];

    LeerArchivo(alumFile, alumnos, alumnosTam, alumnoStructSize);
    OrdenarPorLegajo(alumFile, alumnos, alumnosTam, alumnoStructSize);

    int novedadesTam = CalcularTamaño(novFile, novedadStructSize);
    novedad novedades[novedadesTam];

    LeerArchivo(novFile, novedades, novedadesTam, novedadStructSize);
    OrdenarPorLegajo(novFile, novedades, novedadesTam, novedadStructSize);

    ActualizarAlumnos(actFile, alumnos, alumnosTam, novedades, novedadesTam);
    
    MostrarDatosActualizados(actFile);

    fclose(alumFile);
    fclose(novFile);
    fclose(actFile);

    return 0;
}

void CargarAlumnos(FILE* f)
{
    fseek(f, 0, SEEK_SET);
    alumno al;
    int alSize = sizeof(alumno);

    strcpy(al.apellidoNombre, "PLACEHOLDER");
    strcpy(al.domicilio, "PLACEHOLDER");
    al.codigoPostal = -1;
    strcpy(al.telefono, "PLACEHLDR");
    al.añoDeIngreso = -1;

    cout << "CARGA DE ALUMNOS: " << endl;
    cout << "  Legajo: ";
    cin >> al.legajo;

    while(al.legajo != -1)
    {
        fwrite(&al, alSize, 1, f);
        cout << "  Legajo: ";
        cin >> al.legajo;
    }
    cout << endl;
    fseek(f, 0, SEEK_SET);

    return;
}

void CargarNovedades(FILE* f)
{
    fseek(f, 0, SEEK_SET);
    novedad nov;
    int novSize = sizeof(novedad);

    cout << "CARGA DE NOVEDADES: " << endl;
    cout << "  Legajo: ";
    cin >> nov.al.legajo;
    while(nov.al.legajo != -1)
    {
        cout << "  Código de operación (A, B, M): ";
        cin >> nov.codigoDeOp;
        if(nov.codigoDeOp != 'B')
        {
            cout << "  Apellido y Nombre: ";
            cin >> nov.al.apellidoNombre;
            
            cout << "  Domicilio ";
            cin >> nov.al.domicilio;
            
            cout << "  Código Postal ";
            cin >> nov.al.codigoPostal;
            
            cout << "  Teléfono ";
            cin >> nov.al.telefono;
            
            cout << "  Año de Ingreso ";
            cin >> nov.al.añoDeIngreso;

        }
        fwrite(&nov, novSize, 1, f);
        cout << endl << "  Legajo: ";
        cin >> nov.al.legajo;
    }
    cout << endl;
    fseek(f, 0, SEEK_SET);

    return;
}


int CalcularTamaño(FILE* f, int size)
{
    fseek(f, 0, SEEK_END);
    int dist = ftell(f) / size;
    fseek(f, 0, SEEK_SET);

    return dist;
}

void LeerArchivo(FILE* f, alumno a[], int aTam, int size)
{
    fseek(f, 0, SEEK_SET);
    fread(a, size, aTam, f);
    fseek(f, 0, SEEK_SET);

    return;
}

void LeerArchivo(FILE* f, novedad n[], int nTam, int size)
{
    fseek(f, 0, SEEK_SET);
    fread(n, size, nTam, f);
    fseek(f, 0, SEEK_SET);

    return;
}


void OrdenarPorLegajo(FILE* f, alumno a[], int aTam, int size)
{
    int i, j;
    alumno aux;
    for(i = 1; i < aTam; i++)
    {
        for(j = 1; j <= aTam - i; j++)
        {
            if(a[j-1].legajo > a[j].legajo)
            {
                aux = a[j-1];
                a[j-1] = a[j];
                a[j] = aux;
            }
        }
    }

    fseek(f, 0, SEEK_SET);
    fwrite(a, size, aTam, f);
    fseek(f, 0, SEEK_SET);

    return;
}

void OrdenarPorLegajo(FILE* f, novedad n[], int nTam, int size)
{
    int i, j;
    novedad aux;
    for(i = 1; i < nTam; i++)
    {
        for(j = 1; j <= nTam - i; j++)
        {
            if(n[j-1].al.legajo > n[j].al.legajo)
            {
                aux = n[j-1];
                n[j-1] = n[j];
                n[j] = aux;
            }
        }
    }

    fseek(f, 0, SEEK_SET);
    fwrite(n, size, nTam, f);
    fseek(f, 0, SEEK_SET);

    return;
}

void ActualizarAlumnos(FILE* f, alumno al[], int alTam, novedad nov[], int novTam)
{
    int i = 0;
    int j = 0;
    int k = 0;

    alumno alActual;
    novedad novActual;

    int alSize = sizeof(alumno);

    fseek(f, 0, SEEK_SET);

    while(i < alTam && j < novTam)
    {
        alActual = al[i];
        novActual = nov[j];
        // al actual, nov actual, legajo mayor o menor, codigo de OP, escribir en archivo iterar
        if(alActual.legajo < novActual.al.legajo)
        {
            fwrite(&alActual, alSize, 1, f);
            i++;
            k++;
        }
        else if(alActual.legajo == novActual.al.legajo)
        {
            if(novActual.codigoDeOp == 'B')
            {
                i++;
                j++;
            }
            if(novActual.codigoDeOp == 'M')
            {
                alActual = novActual.al;
                fwrite(&alActual, alSize, 1, f);
                i++;
                j++;
                k++;
            }
        }
        else if(novActual.codigoDeOp == 'A')
        {
            alActual = novActual.al;
            fwrite(&alActual, alSize, 1, f);
            j++;
            k++;
        }
    }
    while(i < alTam)
    {
        alActual = al[i];
        fwrite(&alActual, alSize, 1, f);
        i++;
        k++;
    }
    cout << endl << k << endl;
    return;
}

void MostrarDatosActualizados(FILE* f)
{
    alumno al;
    int alSize = sizeof(al);
    fseek(f, 0, SEEK_SET);
    fread(&al, alSize, 1, f);

    int i = 1;
    while(!feof(f))
    {
        cout << "Alumno " << i << ":" << endl;
        cout << "    Legajo: " << al.legajo << endl;
        cout << "    Apellido y Nombre: " << al.apellidoNombre << endl;
        cout << "    Domicilio: " << al.domicilio << endl;
        cout << "    Código Postal: " << al.codigoPostal << endl;
        cout << "    Teléfono: " << al.telefono << endl;
        cout << "    Año de Ingreso: " << al.añoDeIngreso << endl << endl;

        i++;
        fread(&al, alSize, 1, f);
    }
    return;
}