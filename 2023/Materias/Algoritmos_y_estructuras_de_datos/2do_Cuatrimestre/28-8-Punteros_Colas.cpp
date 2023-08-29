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
    nodo* p = new nodo();

    p->info = val;
    p->sgte = NULL;

    if(fte == NULL)
        fte = p;
    
    else
        fin->sgte = p;

    fin = p;

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