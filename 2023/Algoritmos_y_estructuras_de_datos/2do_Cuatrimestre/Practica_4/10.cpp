/*
    Dadas  dos  colas  COLA  y  COLB  (nodo  =  registro  +  puntero),  desarrollar  y  codificar  un 
    procedimiento que genere una única cola  COLAB a partir de ellas. (Primero los nodos de 
    COLA y luego los de COLB). 
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
    int info;
    nodo* sgte;
};

struct cola
{
    nodo* fte;
    nodo* fin;
};

void Queue(nodo* &, nodo* &, info);
int Unqueue(nodo* &, nodo* &);

void CargarCola(nodo* &, nodo* &);
void ApareoCola(nodo* &, nodo* &, nodo* &, nodo* &, nodo* &, nodo* &);
void MostrarCola(nodo* &, nodo* &);

int main()
{
    cola colaA;
    cola colaB;
    cola colaAB;

    colaA.fte = NULL;
    colaA.fin = NULL;
    colaB.fte = NULL;
    colaB.fin = NULL;
    colaAB.fte = NULL;
    colaAB.fin = NULL;

    CargarCola(colaA.fte, colaA.fin);
    CargarCola(colaB.fte, colaB.fin);

    ApareoCola(colaA.fte, colaA.fin, colaB.fte, colaB.fin, colaAB.fte, colaAB.fin);

    MostrarCola(colaAB.fte, colaAB.fin);

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

void ApareoCola(nodo* &aFTE, nodo* &aFIN, nodo* &bFTE, nodo* &bFIN, nodo* &abFTE, nodo* &abFIN)
{
    while(aFTE != NULL)
    {
        Queue(abFTE, abFIN, Unqueue(aFTE, aFIN));
    }
    while(bFTE != NULL)
    {
        Queue(abFTE, abFIN, Unqueue(bFTE, bFIN));
    }
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