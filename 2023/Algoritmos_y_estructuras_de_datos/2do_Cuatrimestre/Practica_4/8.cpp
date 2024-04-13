/*
    Dada  una  cola  (nodo  =  registro  +  puntero),  desarrollar  y  codificar  un  procedimiento  que 
    elimine 2 nodos de la misma (indicar con un parámetro 'S'/'N' si ello fue‚ o no posible)
*/
#include <iostream>

using namespace std;

struct nodo
{
    int info;
    nodo* sgte;
};

struct cola
{
    nodo* FTE;
    nodo* FIN;
};

void Queue(nodo* &, nodo* &, int);
int Unqueue(nodo* &, nodo* &);

void CargarCola(nodo* &, nodo* &);
char EliminarNodos(nodo* &, nodo* &, int);

int main()
{
    cola cola;
    cola.FIN = NULL;
    cola.FTE = NULL;
    int cant = 2;

    CargarCola(cola.FTE, cola.FIN);
    char retorno = EliminarNodos(cola.FTE, cola.FIN, cant);

    cout << "¿Se pudo eliminar " << cant << " nodos? " << retorno;
    return 0;
}

void Queue(nodo* &fte, nodo* &fin, int val)
{
    nodo* n = new nodo();
    n->info = val;
    n->sgte = NULL;

    if(fte == NULL && fin == NULL)
        fte = n;
    else 
        fin->sgte = n;

    fin = n;

    return;
}

int Unqueue(nodo* &fte, nodo* &fin)
{
    int val;
    nodo* n = fte;
    val = fte->info;
    fte = fte->sgte;

    if(fte == NULL)
        fin = NULL;

    delete n;
    return val;
}

void CargarCola(nodo* &fte, nodo* &fin)
{
    int val;
    cout << "Valor a cargar: ";
    cin >> val;

    while(val > -1)
    {
        Queue(fte, fin, val);
        cout << "Valor a cargar: ";
        cin >> val;
    }
    cout << endl;
    return;
}

char EliminarNodos(nodo* &fte, nodo* &fin, int cant)
{
    for(int i = 0; i < cant; i++)
    {
        if(fte != NULL)
            Unqueue(fte, fin);
        else
            return 'N';
    }
    return 'S';
}