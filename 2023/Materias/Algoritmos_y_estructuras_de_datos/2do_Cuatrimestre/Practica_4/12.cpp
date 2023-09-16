/*
    Dadas dos colas COLA y COLB (nodo = registro + puntero), desarrollar y codificar un 
    procedimiento que genere otra cola COLAB por apareo del campo ARRIBO del registro 
    (define orden creciente en ambas). 
    Nota: COLA y COLB dejan de ser útiles después del apareo.
*/

#include <iostream>

using namespace std;

struct reg
{
    int ARRIBO;
    char tipo;
};

struct nodo
{
    reg info;
    nodo* sgte;
};

struct cola
{
    nodo* fte;
    nodo* fin;
};

void Queue(nodo* &, nodo* &, reg);
reg Unqueue(nodo* &, nodo* &);

void CargarCola(nodo* &, nodo* &);
void OrdenarCola(nodo* &, nodo* &);
cola ApareoCola(nodo* &, nodo* &, nodo* &, nodo* &);

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

    CargarCola(cA.fte, cA.fin);
    OrdenarCola(cA.fte, cA.fin);

    CargarCola(cB.fte, cB.fin);
    OrdenarCola(cB.fte, cB.fin);

    cAB = ApareoCola(cA.fte, cA.fin, cB.fte, cB.fin);

    MostrarCola(cAB.fte, cAB.fin);

    return 0;
}

void Queue(nodo* &fte, nodo* &fin, reg val)
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

reg Unqueue(nodo* &fte, nodo* &fin)
{
    reg val;
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
    reg val;
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

int CantidadDeNodos(nodo* &fte, nodo* &fin)
{
    cola aux;
    aux.fte = NULL;
    aux.fin = NULL;

    int cant = 0;

    while(fte != NULL)
    {
        Queue(aux.fte, aux.fin, Unqueue(fte, fin));
        cant++;
    }
    fte = aux.fte;
    fin = aux.fin;

    return cant;
}

void Burbujeo(reg vec[], int tam)
{
    int i, j;
    reg aux;

    for(i = 1; i < tam; i++)
    {
        for(j = 1; j <= tam - i; j++)
        {
            if(vec[j-1].ARRIBO > vec[j].ARRIBO)
            {
                aux = vec[j-1];
                vec[j-1] = vec[j];
                vec[j] = aux;
            }
        }
    }
    return;
}

void OrdenarCola(nodo* &fte, nodo* &fin)
{
    int vTam = CantidadDeNodos(fte, fin);
    reg vec[vTam];

    int tam = 0;
    while(fte != NULL)
        vec[tam++] = Unqueue(fte, fin);

    Burbujeo(vec, tam);
    for(int i = 0; i < tam; i++)
        Queue(fte, fin, vec[i]);

    return;
}
/*
void ApareoCola(nodo* &aFTE, nodo* &aFIN, nodo* &bFTE, nodo*& bFIN, nodo* &abFTE, nodo* &abFIN)
{
    info v1, v2;
    v1 = Unqueue(aFTE, aFIN);
    v2 = Unqueue(bFTE, bFIN);
    while(aFTE != NULL && bFTE != NULL)
    {
        if(v1.ARRIBO < v2.ARRIBO)
        {
            Queue(abFTE, abFIN, v1);
            v1 = Unqueue(aFTE, aFIN);
        }
        else
        {
            Queue(abFTE, abFIN, v2);
            v2 = Unqueue(bFTE, bFIN);
        }
    }

    while(aFTE != NULL)
    {
        Queue(abFTE, abFIN, Unqueue(aFTE, aFIN));
    }

    while(bFTE != NULL)
    {   
        Queue(abFTE, abFIN, Unqueue(bFTE, bFIN));
    }
    return;
}
*/
cola ApareoCola(nodo* &aFTE, nodo* &aFIN, nodo* &bFTE, nodo*& bFIN)
{
    cola colaAB;
    colaAB.fte = NULL;
    colaAB.fin = NULL;

    int aTam = CantidadDeNodos(aFTE, aFIN);
    int bTam = CantidadDeNodos(bFTE, bFIN);

    reg aVec[aTam];
    reg bVec[bTam];

    int i = 0;
    int j = 0;

    while(aFTE != NULL)
        aVec[i++] = Unqueue(aFTE, aFIN);

    while(bFTE != NULL)
        bVec[j++] = Unqueue(bFTE, bFIN);

    i = 0;
    j = 0;
    while(i < aTam && j < bTam)
    {
        if(aVec[i].ARRIBO < bVec[j].ARRIBO)
            Queue(colaAB.fte, colaAB.fin, aVec[i++]);
        else
            Queue(colaAB.fte, colaAB.fin, bVec[j++]);
    }

    while(i < aTam)
        Queue(colaAB.fte, colaAB.fin, aVec[i++]);

    while(j < bTam)
        Queue(colaAB.fte, colaAB.fin, bVec[j++]);
    
    return colaAB;
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