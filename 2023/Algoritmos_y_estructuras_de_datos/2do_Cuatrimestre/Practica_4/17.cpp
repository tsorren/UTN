/*
    Dada una lista (nodo = registro + puntero), desarrollar y codificar una función que devuelva 
    la cantidad de nodos que tiene.
*/

#include <iostream>

using namespace std;

struct nodo
{
    int info;
    nodo* sgte;
};

void InsertarOrdenado(nodo* &, int);

int CantidadDeNodos(nodo*);

int main()
{
    nodo* lista = NULL;

    for(int i = 0; i < 100; i++)
        InsertarOrdenado(lista, i);

    int cantNodos = CantidadDeNodos(lista);
    cout << "La lista posee " << cantNodos << " nodos"; 

    return 0;
}

int CantidadDeNodos(nodo* lista)
{
    nodo* aux = lista;
    int i = 0;
    while(aux != NULL)
    {
        aux = aux->sgte;
        i++;
    }
    return i;
}

void InsertarOrdenado(nodo* &lista, int val)
{
    nodo* q = lista;
    nodo* n = new nodo();
    n->info = val;
    
    if(lista == NULL || val < lista->info) // Poner al principio
    {
        n->sgte = lista;
        lista = n;
    }
    else 
    {
        while(q->sgte != NULL && q->sgte->info < val)
        {
            q = q->sgte;
        }
        n->sgte = q->sgte;
        q->sgte = n;
    }
}