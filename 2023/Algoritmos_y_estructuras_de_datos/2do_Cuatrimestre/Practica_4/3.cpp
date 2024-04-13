/*
    Dada una pila y un valor X,
    desarrollar un procedimiento que inserte
    el valor X en la última posición de la pila
    y la retorne. (Definir parámetros y codificar).
*/

#include <iostream>

using namespace std;

struct nodo
{
    int info;
    nodo* sgte;
};

void Push(nodo* &, int);
int Pop(nodo* &);

void CargarPila(nodo* &);
void CargarAlFinal(nodo* &, int);
void MostrarPila(nodo* &);

int main()
{
    nodo* pila = NULL;
    int val;

    CargarPila(pila);

    cout << "Ingrese el valor a cargar: ";
    cin >> val;
    CargarAlFinal(pila, val);
    MostrarPila(pila);

    return 0;
}

void Push(nodo* &pila, int info)
{
    nodo* p = new nodo();
    p->info = info;
    p->sgte = pila;
    pila = p;

    return;
}

int Pop(nodo* &pila)
{
    int x;
    nodo* p = pila;
    x = p->info;
    pila = p->sgte;
    delete p; // Libera el espacio de la variable, deja de ser zombie

    return x;
}

void CargarPila(nodo* &pila)
{
    int val = 0;
    cout << "Valor: ";
    cin >> val;
    while(val > -1)
    {
        Push(pila, val);
        cout << "Valor: ";
        cin >> val;
    }
    return;
}

void CargarAlFinal(nodo* &pila, int val)
{
    nodo* aux = NULL;

    while(pila != NULL)
    {
        Push(aux, Pop(pila));
    }
    Push(aux, val);

    while(aux != NULL)
    {
        Push(pila, Pop(aux));
    }
    return;
}

void MostrarPila(nodo* &pila)
{
    int i = 0;
    int val;
    while(pila != NULL)
    {
        val = Pop(pila);
        cout << i << ": " << val << endl;
        i++;
    }
}
