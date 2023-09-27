/*
    Dada una LISTA (nodo = registro + puntero), imprimirla en orden natural si tiene más de 100 
    nodos, caso contrario imprimiría en orden inverso.
*/
#include <iostream>

using namespace std;

struct nodo
{
    int info;
    nodo* sgte;
};

nodo* InsertarOrdenado(nodo* &, int);
void InsertarDelante(nodo* &, int); // Lo mismo que push
int Pop(nodo* &);

nodo* CargarLista();

int CantidadDeNodos(nodo*);

void InvertirOrden(nodo* &);
void MostrarLista(nodo*);

int main()
{
    nodo* lista = CargarLista();

    if(CantidadDeNodos(lista) < 100)
        InvertirOrden(lista);
    MostrarLista(lista);

    return 0;
}

nodo* InsertarOrdenado(nodo* &lista, int val)
{
    nodo* n = new nodo();
    n->info = val;
    n->sgte = NULL;

    if(lista == NULL || val < lista->info) // InsertarDelante
    {
        n->sgte = lista;
        lista = n;
    }
    else 
    {
        nodo* aux = lista;
        while(aux->sgte != NULL && val > aux->sgte->info)
            aux = aux->sgte;
        
        n->sgte = aux->sgte;
        aux->sgte = n;
    }
    return n;
}

void InsertarDelante(nodo* &lista, int val)
{
    nodo* n = new nodo();
    n->info = val;
    n->sgte = lista;
    lista = n;
    return;
}

int Pop(nodo* &lista)
{
    nodo* n = lista;
    int val;

    val = n->info;
    lista = n->sgte;

    delete n;
    return val;
}

nodo* CargarLista()
{
    nodo* lista = NULL;
    int val;
    cout << "CARGA DE LISTA:" << endl;
    cout << "    Valor a cargar: ";
    cin >> val;

    while(val > -1)
    {
        InsertarOrdenado(lista, val);
    
        cout << "    Valor a cargar: ";
        cin >> val;
    }

    return lista;
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

void InvertirOrden(nodo* &lista)
{
    nodo* aux = NULL;
    while(lista != NULL)
        InsertarDelante(aux, Pop(lista));
    
    lista = aux;
    return;
}

void MostrarLista(nodo* lista)
{
    while(lista != NULL)
        cout << Pop(lista) << endl;

    return;
}