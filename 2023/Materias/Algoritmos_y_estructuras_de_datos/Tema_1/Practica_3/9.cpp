/*
    Dado un archivo binario ‘ACTASFINALES.dat’ que contiene las actas de los exámenes 
    finales de las distintas materias, ordenado por libro y folio y con el siguiente diseño  

    a. Libro (6 digitos) // Conjunto de examenes
    b. Folio ( 1..999)   // Examen, conjunto de estudiantes
    c. Fecha (aaaammdd) 
    d. Código materia (6 dígitos) 
    e. Legajo (10 digitos) 
    f. Apellido y nombre (20 caracteres) 
    g. Nota (1..10, 0 indica ausente)

    Se pide desarrollar todos los pasos necesarios para realizar un algoritmo que grabe 
    un archivo ‘TOTALES.dat’ ordenado por libro y folio con el siguiente diseño: 

    Libro (6 digitos) 
    Folio ( 1..999) 
    Total alumnos inscriptos (1..20) 
    Total alumnos ausentes (1..20) 
    Total alumnos aprobados (1..20) 
    Total alumnos desaprobados (1..20)


*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

struct acta
{
    int libro;
    int folio;
    char fecha[8+1];
    int codigoMateria;
    int legajo;
    char apellidoNombre[20+1];
    int nota;
};

struct output
{
    int libro;
    int folio;
    int alumInscriptos;
    int alumAusentes;
    int alumAprobados;
    int alumDesaprobados;
};

void CargarArchivo(FILE*);
void MostrarActas(FILE*);
int CalcularTamañoActas(FILE*);
void LeerArchivo(FILE*, acta[], int);
void OrdenarArchivo(FILE*, acta[], int);

int CalcularTamañoFolios(acta[], int);
void ProcesarDatos(acta[], int, output[], int);

void GrabarArchivo(FILE*, output[], int);
void MostrarTotales(FILE*);

int main()
{
    int actasTam = 0;
    int outputsTam = 0;

    FILE* actasFile = fopen("archivos/ej9_ACTASFINALES.dat", "rb+");
    FILE* outputFile = fopen("archivos/ej9_TOTALES.dat", "wb+");

    //CargarArchivo(actasFile);
    MostrarActas(actasFile);
    
    actasTam = CalcularTamañoActas(actasFile);
    acta actas[actasTam];

    LeerArchivo(actasFile, actas, actasTam);
    OrdenarArchivo(actasFile, actas, actasTam);

    outputsTam = CalcularTamañoFolios(actas, actasTam);
    output outputs[outputsTam];

    ProcesarDatos(actas, actasTam, outputs, outputsTam);

    GrabarArchivo(outputFile, outputs, outputsTam);

    MostrarTotales(outputFile);
    
    fclose(actasFile);
    fclose(outputFile);
    return 0;
}

void CargarArchivo(FILE* f)
{
    int libroActual = 0;
    int folioActual = 0;
    int codigoMateriaActual = 0;
    int legajoActual = 0;
    char apellidoNombreActual[20+1] = "PLACEHOLDER";
    int notaActual = 0;

    acta actaActual;
    int actaSize = sizeof(acta);


    strcpy(actaActual.fecha, "AAAAMMDD");
    strcpy(actaActual.apellidoNombre, "PLACEHOLDER");
    
    cout << "Libro " << libroActual << endl;
    cout << "  Folio " << folioActual << endl;
    cout << "    Nota: ";
    cin >> notaActual;
    while(notaActual > -1)
    {
        actaActual.libro = libroActual;
        actaActual.codigoMateria = codigoMateriaActual;

        while(notaActual > -1)
        {            
            actaActual.folio = folioActual;
            while(notaActual > -1)
            {
                legajoActual++;
                actaActual.legajo = legajoActual;
                actaActual.nota = notaActual;
                
                fwrite(&actaActual, actaSize, 1, f);
                cout << "    Nota: ";
                cin >> notaActual;

            }            
            folioActual++;
            cout << "  Folio " << folioActual << endl;
            cout << "    Nota: ";
            cin >> notaActual;
        }
        codigoMateriaActual += 10;
        libroActual++;
        folioActual = 0;
        cout << endl << "Libro " << libroActual << endl;
        cout << "  Folio " << folioActual << endl;
        cout << "    Nota: ";
        cin >> notaActual;
    }
    return;
}

void MostrarActas(FILE* f)
{
    cout << "-------------------------------------------" << endl;
    cout << "ACTAS: " << endl;
    fseek(f, 0, SEEK_SET);
    acta a;
    int aSize = sizeof(acta);
    fread(&a, aSize, 1, f);
    while(!feof(f))
    {
        cout << "Libro: " << a.libro << endl;
        cout << "  Folio: " << a.folio << endl;
        cout << "  Fecha:" << a.fecha << endl;
        cout << "  Codigo de materia: " << a.codigoMateria << endl;
        cout << "    Legajo: " << a.legajo << endl;
        cout << "    Apellido y Nombre: "<< a.apellidoNombre << endl;
        cout << "    Nota: " << a.nota << endl << endl; 
        fread(&a, aSize, 1, f);
    }
    cout << "-------------------------------------------" << endl << endl;
    fseek(f, 0, SEEK_SET);
    return;
}

int CalcularTamañoActas(FILE* f)
{
    fseek(f, 0, SEEK_END);
    int dist = ftell(f) / sizeof(acta);
    fseek(f, 0, SEEK_SET);

    return dist;
}

void LeerArchivo(FILE* f, acta a[], int aTam)
{
    fseek(f, 0, SEEK_SET);
    fread(a, sizeof(acta), aTam, f);
    fseek(f, 0, SEEK_SET);

    return;
}

void OrdenarArchivo(FILE* f, acta a[], int aTam)
{
    int i, j;
    acta aux;
    for(i = 1; i < aTam; i++)
    {
        for(j = 1; j <= aTam - i; j++)
        {
            if((a[j-1].libro > a[j].libro) || 
                (a[j-1].libro == a[j].libro && a[j-1].folio > a[j].folio))
            {
                aux = a[j-1];
                a[j-1] = a[j];
                a[j] = aux;
            }
        }
    }
    fseek(f, 0, SEEK_SET);
    fwrite(a, sizeof(acta), aTam, f);
    fseek(f, 0, SEEK_SET);
    
    return;
}

int CalcularTamañoFolios(acta a[], int aTam)
{
    int contador = 0;
    int folioActual = -1;
    for(int i = 0; i < aTam; i++)
    {
        if(folioActual != a[i].folio)
        {
            folioActual = a[i].folio;
            contador++;
        }
    }
    return contador;
}

void ProcesarDatos(acta a[], int aTam, output o[], int oTam)
{
    int folioActual = -1;
    int notaActual = -1;
    int j = -1;
    for(int i = 0; i < aTam; i++)
    {
        notaActual = a[i].nota;
        if(folioActual != a[i].folio)
        {
            j++;
            folioActual = a[i].folio;
            o[j].libro = a[i].libro;
            o[j].folio = a[i].folio;
            o[j].alumInscriptos = 0;
            o[j].alumAusentes = 0;
            o[j].alumAprobados = 0;
            o[j].alumDesaprobados = 0;
        }

        o[j].alumInscriptos++;

        if(notaActual == 0)
        {
            o[j].alumAusentes++;
        }
        else if(notaActual < 6)
        {
            o[j].alumDesaprobados++;
        }
        else
        {
            o[j].alumAprobados++;
        }
    }

    return;
}

void GrabarArchivo(FILE* f, output o[], int tam)
{
    fseek(f, 0, SEEK_SET);
    fwrite(o, sizeof(output), tam, f);
    return;
}

void MostrarTotales(FILE* f)
{    
    cout << "-------------------------------------------" << endl;
    cout << "TOTALES: " << endl;
    fseek(f, 0, SEEK_SET);
    output oActual;
    int oSize = sizeof(output);
    
    fread(&oActual, oSize, 1, f);
    while(!feof(f))
    {
        cout << "Libro: " << oActual.libro << endl;
        cout << "Folio: " << oActual.folio << endl;
        cout << "Total alumnos inscriptos: " << oActual.alumInscriptos << endl;
        cout << "Total alumnos ausentes: " << oActual.alumAusentes << endl;
        cout << "Total alumnos aprobados: " << oActual.alumAprobados << endl;
        cout << "Total alumnos desaprobados: " << oActual.alumDesaprobados << endl << endl;
        fread(&oActual, oSize, 1, f);
    }
    cout << "-------------------------------------------" << endl;
    return;
}