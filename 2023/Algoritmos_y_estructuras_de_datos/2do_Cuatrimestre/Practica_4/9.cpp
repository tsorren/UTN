/*
    Dada una cola (nodo = registro + puntero), desarrollar y codificar una función que devuelva 
    la cantidad de nodos que tiene.
*/
#include <iostream>

using namespace std;

struct info
{
    int a;
    int b;
};

struct nodo
{
    info info;
    nodo* sgte;
};

struct cola
{
    nodo* FTE;
    nodo* FIN;
};

void Queue(nodo* &, nodo* &, info);
info Unqueue(nodo* &, nodo* &);

void CargarCola(nodo* &, nodo* &);

int CantidadDeNodos(nodo* &, nodo* &);

int main()
{
    cola cola;
    cola.FTE = NULL;
    cola.FIN = NULL;

    CargarCola(cola.FTE, cola.FIN);
    int cant = CantidadDeNodos(cola.FTE, cola.FIN);

    cout << "La cola tiene " << cant << " nodos" << endl;
    return 0;
}

void Queue(nodo* &fte, nodo* &fin, info val)
{
    nodo* n = new nodo();

    n->info = val;
    n->sgte = NULL;

    if(fte == NULL)
        fte = n;
    
    else
        fin->sgte = n;

    fin = n;

    return;
}

info Unqueue(nodo* &fte, nodo* &fin)
{
    info val;
    nodo* p = fte;

    val = p->info;
    fte = p->sgte;

    if(fte == NULL)
        fin = NULL;

    delete p;
    return val;
}

void CargarCola(nodo* &fte, nodo* &fin)
{
    info val;

    cout << "Valor a cargar: ";
    cin >> val.a;
    val.b = 9;

    while(val.a > -1)
    {
        Queue(fte, fin, val);
        cout << "Valor a cargar: ";
        cin >> val.a;
    }
    return;
}

int CantidadDeNodos(nodo* &fte, nodo* &fin)
{
    int i = 0;
    cola aux;
    aux.FTE = NULL;
    aux.FIN = NULL;

    while(fte != NULL)
    {
        Queue(aux.FTE, aux.FIN, Unqueue(fte, fin));
        i++;
    }
    while(aux.FTE != NULL)
    {
        Queue(fte, fin, Unqueue(aux.FTE, aux.FIN));

    }
    return i;
}