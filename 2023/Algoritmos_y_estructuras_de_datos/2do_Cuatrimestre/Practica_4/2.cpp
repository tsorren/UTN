/*
   Dada una pila y dos valores X e I,
   desarrollar un procedimiento que inserte el valor X en la posición I
   de la pila si es posible. (Definir parámetros y codificar).
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
int ConseguirTamañoPila(nodo* &);

char CargarEnPosicion(nodo* &, int, int);

void MostrarPila(nodo* &);


int main()
{
    nodo* pila = NULL;
    int val;
    int pos;

    CargarPila(pila);

    cout << "Ingrese el valor a cargar: ";
    cin >> val;

    cout << "Ingrese la posición donde se cargará el valor: ";
    cin >> pos;

    char resultado = CargarEnPosicion(pila, val, pos);
    cout << endl << "Resultado: " << resultado << endl;

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


char CargarEnPosicion(nodo* &pila, int val, int pos)
{
    nodo* aux = NULL;

    for(int i = 0; i < pos; i++)
    {
        Push(aux, Pop(pila));
        if(pila == NULL)
            return 'N';
    }
    Push(aux, val);

    while(aux != NULL)
    {
        Push(pila, Pop(aux));
    }

    return 'S';
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
