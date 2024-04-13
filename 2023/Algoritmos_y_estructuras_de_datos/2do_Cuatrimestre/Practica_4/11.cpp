/*
    Dada una cola (nodo = registro + puntero), imprimirla en orden natural si tiene más de 100 
    nodos, caso contrario imprimirla en orden inverso.
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
    nodo* fte;
    nodo* fin;
};

void Queue(nodo* &, nodo* &, int);
int Unqueue(nodo* &, nodo* &);

void Push(nodo* &, int);
int Pop(nodo* &);

void CargarCola(nodo* &, nodo* &);
void Procesar(nodo* &, nodo* &);
void MostrarCola(nodo* &, nodo* &);

int main()
{
    cola cola;
    cola.fte = NULL;
    cola.fin = NULL;

    CargarCola(cola.fte, cola.fin);
    Procesar(cola.fte, cola.fin);

    MostrarCola(cola.fte, cola.fin);

    return 0;
}

void Queue(nodo* &fte, nodo* &fin, int val)
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

void Push(nodo* &pila, int val)
{
    nodo* p = new nodo();
    p->info = val;
    p->sgte = pila;

    pila = p;

    return;
}

int Pop(nodo* &pila)
{
    int val;
    nodo* p = pila;
    val = p->info;
    pila = p->sgte;

    delete p;

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
}

void Procesar(nodo* &fte, nodo* &fin)
{
    int cant = 0;
    nodo* pila = NULL;
    nodo* aux = NULL;

    while(fte != NULL)
    {
        Push(pila, Unqueue(fte, fin));
        cant++;
    }
    if(cant > 10)
    {
        while(pila != NULL)
            Queue(fte, fin, Pop(pila));
        
        return;
    }

    while(pila != NULL)
    {
        Push(aux, Pop(pila));
    }
    while(aux != NULL)
    {
        Queue(fte, fin, Pop(aux));
    }
    return;
}

void MostrarCola(nodo* &fte, nodo* &fin)
{
    int i = 0;
    while(fte != NULL)
    {
        cout << "Pos " << i << ": " << Unqueue(fte, fin) << endl;
        i++;
    }
    cout << endl;
}