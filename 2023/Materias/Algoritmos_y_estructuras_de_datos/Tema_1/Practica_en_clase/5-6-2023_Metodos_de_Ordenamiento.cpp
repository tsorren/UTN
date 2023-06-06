#include <iostream>
#include <cstring>

using namespace std;

struct alumno
{
    int curso;
    char nombre[16+1];
};

void MostrarVector(alumno[], int);

void Burbuja(int[], int);
void BurbujaStruct(alumno[], int); // Se puede realizar una sobrecarga de funciones
void BurbujaAlfabetica(alumno[], int); // Alfabeticamente, creciente
void BurbujaCompuesta(alumno[], int); // Curso y alfabeticamiente creciente

void CorteDeControl(alumno[], int); // Curso y alfabeticamiente creciente
// Para mayor seguridad, "const alumno[]"

int main()
{
    alumno alumnos[7] = {{1, "Pedro"}, {2, "Juan"}, {1, "Pepe"}, {2, "Matias"},
                        {1, "Agustin"}, {2, "Alex"}, {1, "Gabriel"}};

    BurbujaCompuesta(alumnos, 7);

    MostrarVector(alumnos, 7);

    CorteDeControl(alumnos, 7);

    

    return 0;
}

void MostrarVector(alumno vector[], int N)
{
    int i;

    for(i = 0; i < N; i++)
    {
        cout << vector[i].curso << ", " << vector[i].nombre << endl;
    }
    cout << endl;
}

void Burbuja(int vector[], int N)
{
    int i, j;
    int aux;

    for (i = 1; i < N; i++)
    {
        for (j = 1; j <= N - 1; j++)
        {
            // [j-1] > [j] Ordenamiento creciente
            // [j-1] < [j] Ordenamiento decreciente
            if (vector[j - 1] > vector[j])
            {
                aux = vector[j - 1];
                vector[j - 1] = vector[j];
                vector[j] = aux;
            }
        }
    }
}

void BurbujaStruct(alumno vector[], int N)
{
    int i, j;
    alumno aux;

    for (i = 1; i < N; i++)
    {
        for (j = 1; j <= N - 1; j++)
        {
            // [j-1] > [j] Ordenamiento creciente
            // [j-1] < [j] Ordenamiento decreciente
            if (vector[j - 1].curso > vector[j].curso)
            {
                aux = vector[j - 1];
                vector[j - 1] = vector[j];
                vector[j] = aux;
            }
        }
    }
}

void BurbujaAlfabetica(alumno vector[], int N)
{
    int i, j;
    alumno aux;

    for (i = 1; i < N; i++)
    {
        for (j = 1; j <= N - 1; j++)
        {
            // strcmp() == 1 Ordenamiento creciente
            // strcmp() == -1 Ordenamiento decreciente
            if (strcmp(vector[j - 1].nombre, vector[j].nombre) == 1)
            {
                aux = vector[j - 1];
                vector[j - 1] = vector[j];
                vector[j] = aux;
            }
        }
    }
}

void BurbujaCompuesta(alumno vector[], int N)
{
    int i, j;
    alumno aux;

    for (i = 1; i < N; i++)
    {
        for (j = 1; j <= N - 1; j++)
        {
            // strcmp() == 1 Ordenamiento creciente
            // strcmp() == -1 Ordenamiento decreciente
            if(vector[j - 1].curso > vector[j].curso ||
                (vector[j-1].curso == vector[j].curso &&
                (strcmp(vector[j-1].nombre, vector[j].nombre) == 1)))
            {
                aux = vector[j - 1];
                vector[j - 1] = vector[j];
                vector[j] = aux;
            }
        }
    }
}

void CorteDeControl(alumno vector[], int N) // Para mayor seguridad, "const alumno[]"
{
    int i = 0;

    int cursoActual;
    int cantidad, cantidadTotal = 0;

    
    cout << "TITULO" << endl << endl;

    while(i < N) //Mientras haya datos
    {
        cursoActual = vector[i].curso;
        cantidad = 0;
        cout << "    Curso " << cursoActual << ":" << endl;
        while(i < N && cursoActual == vector[i].curso)
        {
            cout << "    " << vector[i].nombre << endl;
            i++;
            cantidad++;
            cantidadTotal++;
        }
        // cantidadTotal += cantidad;
        cout << "        Total de alumnos en este curso: " << cantidad << endl << endl;
    }
    cout << "Total de alumnos procesados: " << cantidadTotal << endl;
}