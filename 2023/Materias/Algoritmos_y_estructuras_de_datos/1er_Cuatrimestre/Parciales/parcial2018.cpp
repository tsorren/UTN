//2.
#include<iostream>
using namespace std;

struct Datos
{
    int curso; // 3 digitos
    char alumno[30+1];
    int legajo; // 6 digitos
    char turno;
};

struct TipoAl
{
    Datos datos;
    int compañerosDeGrupo;
};

int N = 1000;

void inicializarVector(TipoAl alumnos[])
{
    int i = 0;
    while(i < N)
    {
        alumnos[i].datos.curso = 0;
        i++;
    }
}

void leerArchivo(FILE* f, TipoAl alumnos[], int CANT)
{
    /*
    int alumnosPorCurso[30];
    int gruposPorCurso[30];
    int pupCurso;
    */

    fseek(f, 0, SEEK_END);
    int cantAlumnosTotal = ftell(f) / sizeof(Datos);

    fseek(f, 0, SEEK_SET);
    int i = 0;
    while(fread(&alumnos[i].datos, sizeof(Datos), 1, f))
    {
        alumnos[i].compañerosDeGrupo = CANT;
        //pupCurso = (alumnos[i].datos.curso) / 10;
        //alumnosPorCurso[pupCurso]++;
        i++;
    }
    /*
    for(int k = 0; k < 30; k++)
    {
        gruposPorCurso[k] = alumnosPorCurso[k] / CANT;
    }
    */
    BurbujeoAlumnosPorCursoLegajo(alumnos, cantAlumnosTotal); // Aclarar tipo de burbujeo sin programar
    
}
/*
void informarResultados(TipoAl alumnos[])
{
    int i = 0;
    int cursoActual = 0;
    
    int j = 1;
    int cantGrupos;
    int cantGruposTotal = 0;

    while(alumnos[i].datos.curso != 0)
    {
        if(cursoActual != alumnos[i].datos.curso)
        {
            cantGrupos = j / alumnos[i-1].compañerosDeGrupo;
            cantGruposTotal += cantGrupos;
            cout << "Cantidad de grupos conformados: " << cantGrupos << endl;

            j = 1;
            cursoActual = alumnos[i].datos.curso;
            cout << "CURSO: K" << alumnos[i].datos.curso << endl;
            cout << "Legajos:" << endl;
        }
        cout << "   " << alumnos[i].datos.legajo;
        j++;
        i++;
    }
    cout << "TOTAL DE GRUPOS: " << cantGruposTotal << endl;
}
*/
void informarResultados(TipoAl alumnos[])
{
    int i = 0;
    int j = 0;
    int cursoActual = 0;
    
    int cantGrupos;
    int cantGruposTotal = 0;
    int alPorGrupo = alumnos[0].compañerosDeGrupo;

    while(alumnos[i].datos.curso != 0)
    {
        cursoActual = alumnos[i].datos.curso;
        while(cursoActual == alumnos[j+i].datos.curso && alumnos[j+i].datos.curso != 0)
        {
            j++;
        }
        cantGrupos = j / alPorGrupo;
        cantGruposTotal += cantGrupos;
        cout << "CURSO: K" << alumnos[i].datos.curso << endl;
        cout << "Cantidad de grupos conformados: " << cantGrupos << endl;
        cout << "Legajos:" << endl;
        while(cursoActual == alumnos[i].datos.curso && alumnos[i].datos.curso != 0)
        {
            cout << "   " << alumnos[i].datos.legajo << endl;
        }        
        
        j = 0;
        i++;
    }
    cout << "TOTAL DE GRUPOS: " << cantGruposTotal << endl;
}
void BurbujeoAlumnosPorCursoLegajo(TipoAl al[], int N)
{
    int i, j;
    TipoAl aux;
    for(i = 1; i < N; i++)
    {
        for(j = 1; j <= (N-1); j++)
        {
            if((al[j-1].datos.curso > al[j].datos.curso) || 
            (al[j-1].datos.curso == al[j].datos.curso && al[j-1].datos.legajo > al[j].datos.legajo))
            {
                aux = al[j-1];
                al[j-1] = al[j];
                al[j] = aux;
            }
        }
    }
    return;
}