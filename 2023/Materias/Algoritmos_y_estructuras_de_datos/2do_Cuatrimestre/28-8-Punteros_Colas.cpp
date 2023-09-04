#include<iostream>

using namespace std;

struct nodo
{
    int info;
    nodo* sgte;
};


int main()
{
    nodo* colaFTE = NULL;
    nodo* colaFIN = NULL;

}

void queue(nodo* &fte, nodo* &fin, int val)
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

int unqueue(nodo* &fte, nodo* &fin)
{
    int x;
    nodo* p = fte;

    x = p->info;
    fte = p->sgte;

    if(fte == NULL)
        fin = NULL;

    delete p;
    return x;
}