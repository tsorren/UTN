/*
    Desarrollar un procedimiento que ingrese
    por teclado un conjunto de Apellidos y Nombre de alumnos
    y los imprima en orden inverso al de ingreso. (Definir parámetros y codificar).
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

struct nodo
{
    char apellidoNombre[32+1];
    nodo* sgte;
};

void Push(nodo* &, char[]);
void Pop(nodo* &, char[]);

void CargarPila(nodo* &);
void InvertirOrden(nodo* &);
void MostrarPila(nodo* &);

int main()
{
    nodo* pila = NULL;
    CargarPila(pila);

    InvertirOrden(pila);

    MostrarPila(pila);

    return 0;
}

void Push(nodo* &pila, char val[])
{   
    nodo* p = new nodo();

    strcpy(p->apellidoNombre, val);
    p->sgte = pila;

    pila = p;

    return;
}

void Pop(nodo* &pila, char val[])
{
    nodo* p = pila;
    strcpy(val, pila->apellidoNombre);

    pila = pila->sgte;

    delete p;

    return;
}

void CargarPila(nodo* &p)
{
    char val[32+1];
    cout << "Ingrese apellido y nombre: ";
    cin >> val;
    while(val[0] != '-')
    {
        Push(p, val);

        cout << "Ingrese apellido y nombre: ";
        cin >> val;
    }
}

void InvertirOrden(nodo* &p)
{
    nodo* aux = NULL;
    char valActual[32+1];
    while(p != NULL)
    {
        Pop(p, valActual);
        Push(aux, valActual);
    }
    p = aux;
}

void MostrarPila(nodo* &p)
{
    int i = 0;
    char valActual [32+1];
    while(p != NULL)
    {
        Pop(p, valActual);

        cout << "Pos " << i << ": " << valActual << endl;
        i++;
    }
    cout << endl;
}