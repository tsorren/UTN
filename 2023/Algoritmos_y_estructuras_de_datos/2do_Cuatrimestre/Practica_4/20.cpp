/*
    Dadas  dos  listas  LISTA  y  LISTB  (nodo  =  registro  +  puntero),  desarrollar  y  codificar  un 
    procedimiento  que  genere  otra  lista  LISTC  por  apareo  del  campo  LEGAJO  del  registro 
    (define orden creciente en ambas). 
    Nota: LISTA y LISTB dejan de ser útiles después del apareo).
*/

#include <iostream>

using namespace std;

struct reg
{
    int legajo;
    int curso;
};

struct nodo
{
    reg info;
    nodo* sgte;
};

nodo* InsertarOrdenado(nodo* &, reg);
reg Pop(nodo* &);

nodo* CargarLista();

nodo* AparearListas(nodo* &, nodo* &);

void MostrarLista(nodo* &);

int main()
{
    nodo* listaA = CargarLista();
    nodo* listaB = CargarLista();
    nodo* listaC = AparearListas(listaA, listaB);

    MostrarLista(listaC);

    return 0;
}

nodo* InsertarOrdenado(nodo* &lista, reg val)
{
    nodo* n = new nodo();
    n->info = val;

    if(lista == NULL || val.legajo < lista->info.legajo)
    {
        n->sgte = lista;
        lista = n;
    }
    else
    {
        nodo* aux = lista;
        while(aux->sgte != NULL && val.legajo > aux->sgte->info.legajo)
            aux = aux->sgte;

        n->sgte = aux->sgte;
        aux->sgte = n;
    }
    return n;
}

reg Pop(nodo* &lista)
{
    nodo* n = lista;
    reg val;
    val = n->info;
    lista = n->sgte;

    delete n;
    return val;
}

nodo* CargarLista()
{
    nodo* lista = NULL;
    reg val;
    cout << "CARGA DE LISTA:" << endl;
    cout << "    Legajo: ";
    cin >> val.legajo;

    while(val.legajo > 0)
    {        
        cout << "    Curso: ";
        cin >> val.curso;
        InsertarOrdenado(lista, val);

        cout << endl;
        cout << "    Legajo: ";
        cin >> val.legajo;
    }
    cout << endl;
    return lista;
}

nodo* AparearListas(nodo* &a, nodo* &b)
{
    nodo* c = NULL;

    while(a != NULL && b != NULL)
    {
        if(a->info.legajo < b->info.legajo)
            InsertarOrdenado(c, Pop(a));
        else
            InsertarOrdenado(c, Pop(b));
    }

    while(a != NULL)
        InsertarOrdenado(c, Pop(a));

    while(b != NULL)
        InsertarOrdenado(c, Pop(b));

    return c;
}

void MostrarLista(nodo* &lista)
{
    reg regActual;
    cout << "LISTA:" << endl;
    while(lista != NULL)
    {
        regActual = Pop(lista);
        cout << "    Legajo: " << regActual.legajo << endl;
        cout << "    Curso: " << regActual.curso << endl;
        cout << endl;
    }
    return;
}