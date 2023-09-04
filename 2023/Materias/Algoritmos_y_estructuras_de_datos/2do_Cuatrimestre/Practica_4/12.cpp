/*
    Dadas dos colas COLA y COLB (nodo = registro + puntero), desarrollar y codificar un 
    procedimiento que genere otra cola COLAB por apareo del campo ARRIBO del registro 
    (define orden creciente en ambas). 
    Nota: COLA y COLB dejan de ser útiles después del apareo.
*/

#include <iostream>

using namespace std;

struct info
{
    int ARRIBO;
    char tipo;
};

struct nodo
{
    info info;
    nodo* sgte;
};

struct cola
{
    nodo* fte;
    nodo* fin;
};

void Queue(nodo* &, nodo* &, info);
info Unqueue(nodo* &, nodo* &);

void CargarCola(nodo* &, nodo* &);
//void OrdenarCola(nodo* &, nodo* &); ASUMO QUE YA ESTÁ ORDENADA, debería meter todo en vector y ordenar
void ApareoCola(nodo* &, nodo* &, nodo* &, nodo* &, nodo* &, nodo* &);

void MostrarCola(nodo* &, nodo* &);

int main()
{
    cola cA;
    cola cB;
    cola cAB;

    cA.fte = NULL;
    cA.fin = NULL;
    cB.fte = NULL;
    cB.fin = NULL;
    cAB.fte = NULL;
    cAB.fin = NULL;

    CargarCola(cA.fte, cA.fin);
    CargarCola(cB.fte, cB.fin);

    ApareoCola(cA.fte, cA.fin, cB.fte, cB.fin, cAB.fte, cAB.fin);

    MostrarCola(cAB.fte, cAB.fin);

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
    info val;
    val.tipo = 'N';
    cout << "Valor a cargar: ";
    cin >> val.ARRIBO;

    while(val.ARRIBO > -1)
    {
        Queue(fte, fin, val);
        cout << "Valor a cargar: ";
        cin >> val.ARRIBO;
    }
    cout << endl;

    return;
}

void ApareoCola(nodo* &aFTE, nodo* &aFIN, nodo* &bFTE, nodo*& bFIN, nodo* &abFTE, nodo* &abFIN)
{
    int v1, v2;
    while(aFTE != NULL && bFTE != NULL)
    {
        v1 = aFTE->info.ARRIBO;
        v2 = bFTE->info.ARRIBO;

        if(v1 < v2)
            Queue(abFTE, abFIN, Unqueue(aFTE, aFIN));

        else
            Queue(abFTE, abFIN, Unqueue(bFTE, bFIN));
    }
    while(aFTE != NULL)
        Queue(abFTE, abFIN, Unqueue(aFTE, aFIN));

    while(bFTE != NULL)
        Queue(abFTE, abFIN, Unqueue(bFTE, bFIN));

    return;
}

void MostrarCola(nodo* &fte, nodo* &fin)
{
    int i = 0;
    while(fte != NULL)
    {
        cout << "Pos " << i << ": " << Unqueue(fte, fin).ARRIBO << endl;
        i++;
    }
    cout << endl;
}