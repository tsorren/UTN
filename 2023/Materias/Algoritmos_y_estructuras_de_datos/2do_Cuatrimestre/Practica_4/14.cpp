/*
    Idem  Ejercicio  Nro.  13,  pero  el  listado  de  alumnos  por  división  debe  realizarse  ordenado 
    creciente por división y decreciente por número de legajo. 
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

using namespace std;

struct reg
{
    char apellidoNombre[35+1];
    int legajo;
    int division;
};

struct nodo
{
    reg info;
    nodo* sgte;
};

struct vecReg
{
    nodo* pila;
    int cantAlumnos;
};

void CargarArchivo(FILE*);
int CantidadDeRegistros(FILE*);
void Burbujeo(reg[], int);
void OrdenarArchivo(FILE*);

void Push(nodo* &, reg);
reg Pop(nodo* &);

void InvertirOrden(nodo* &);
void MostrarDivision(vecReg, int);

int main()
{
    FILE* f = fopen("archivos/ej13_alumnos.dat", "rb+");

    reg regActual;
    int regSize = sizeof(reg);

    vecReg divisiones[100];

    for(int i = 0; i < 100; i++)
    {
        divisiones[i].pila = NULL;
        divisiones[i].cantAlumnos = 0;
    }

    //CargarArchivo(f);
    OrdenarArchivo(f);
    int indice;
    while(fread(&regActual, regSize, 1, f))
    {
        indice = regActual.division - 1;
        Push(divisiones[indice].pila, regActual);
        divisiones[indice].cantAlumnos++;        
    }

    for(int i = 0; i < 100; i++)
    {
        InvertirOrden(divisiones[i].pila);
        MostrarDivision(divisiones[i], i);
    }

    fclose(f);
}

void CargarArchivo(FILE* f)
{
    reg regActual;
    int regSize = sizeof(reg);
    cout << "Division: ";
    cin >> regActual.division;

    while(regActual.division > 0 && regActual.division < 101)
    {
        cout << "Legajo: ";
        cin >> regActual.legajo;

        cout << "Apellido y Nombre: ";
        cin >> regActual.apellidoNombre;

        fwrite(&regActual, regSize, 1, f);
        cout << endl;

        cout << "Division: ";
        cin >> regActual.division;
    }

    fseek(f, 0, SEEK_SET);
    return;
}

int CantidadDeRegistros(FILE* f)
{
    fseek(f, 0, SEEK_END);
    int cant = ftell(f) / sizeof(reg);
    fseek(f, 0, SEEK_SET);
    return cant;
}

void Burbujeo(reg vec[], int tam)
{
    int i, j;
    reg aux;
    for(i = 1; i < tam; i++)
    {
        for(j = 1; j <= tam - i; j++)
        {
            if(vec[j-1].legajo < vec[j].legajo)
            {
                aux = vec[j-1];
                vec[j-1] = vec[j];
                vec[j] = aux;
            }
        }
    }
    return;
}

void OrdenarArchivo(FILE* f)
{
    int regSize = sizeof(reg);
    int cantReg = CantidadDeRegistros(f);
    reg vec[cantReg];
    fread(vec, regSize, cantReg, f);

    Burbujeo(vec, cantReg);

    fseek(f, 0, SEEK_SET);
    fwrite(vec, regSize, cantReg, f);
    fseek(f, 0, SEEK_SET);

    return;
}

void Push(nodo* &pila, reg val)
{
    nodo* n = new nodo();
    n->info = val;
    n->sgte = pila;

    pila = n;
    return;
}

reg Pop(nodo* &pila)
{
    nodo* n = new nodo();
    reg val;
    val = pila->info;
    pila = pila->sgte;

    delete n;
    return val;
}

void InvertirOrden(nodo* &pila)
{
    nodo* aux = NULL;
    while(pila != NULL)
        Push(aux, Pop(pila));

    pila = aux;
    return;
}

void MostrarDivision(vecReg div, int divNro)
{
    reg regActual;
    if(div.pila != NULL)
    {
        cout << "División " << divNro + 1 << ":" << endl;
        while(div.pila != NULL)
        {
            regActual = Pop(div.pila);
            cout << "    Legajo: " << regActual.legajo << endl;
            cout << "    Nombre: " << regActual.apellidoNombre << endl; 
            cout << endl;
        }
    }
    return;
}