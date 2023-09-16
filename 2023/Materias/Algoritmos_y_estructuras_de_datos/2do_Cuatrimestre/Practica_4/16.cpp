/*
    Dado  un  arreglo  de  N  (<  30)  colas  (nodo  =  registro  +  puntero),  desarrollar  y  codificar  un 
    procedimiento que aparee las colas del arreglo en las mismas condiciones que las definidas 
    en el Ejercicio Nro. 12. 
    Nota: Retornar la cola resultante y no mantener las anteriores.
*/

#include <iostream>
#include <cstdlib>

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

void CargarColas(cola[], int);
int CalcularTamaño(nodo* &, nodo* &);
void OrdenarColas(cola[], int);
cola AparearColas(nodo* &, nodo* &, nodo* &, nodo* &);
cola GenerarColaFinal(cola[], int);
void MostrarCola(cola);

int main()
{
    cola vec[30];
    cola colaFinal;
    colaFinal.fte = NULL;
    colaFinal.fin = NULL;

    for(int i = 0; i < 30; i++)
    {
        vec[i].fte = NULL;
        vec[i].fin = NULL;
    }

    CargarColas(vec, 30);
    OrdenarColas(vec, 30);
    colaFinal = GenerarColaFinal(vec, 30);
    MostrarCola(colaFinal);


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
    nodo* n = fte;
    int val;

    val = fte->info;
    fte = fte->sgte;

    if(fte == NULL)
        fin = NULL;

    delete n;

    return val;
}

void CargarColas(cola vec[], int tam)
{
    int val;
    for(int i = 0; i < tam; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            val = rand() % 90;
            Queue(vec[i].fte, vec[i].fin, val);
        }
    }
    return;
}

void Burbujeo(int vec[], int tam)
{
    int i, j, aux;
    for(i = 1; i < tam; i++)
    {
        for(j = 1; j <= tam - i; j++)
        {
            if(vec[j-1] > vec[j])
            {
                aux = vec[j-1];
                vec[j-1] = vec[j];
                vec[j] = aux;
            }
        }
    }
    return;
}

void OrdenarColas(cola vec[], int tam)
{
    int j;
    for(int i = 0; i < tam; i++)
    {
        int colaTam = CalcularTamaño(vec[i].fte,vec[i].fin);
        int aux[colaTam];

        j = 0;
        while(vec[i].fte != NULL)
            aux[j++] = Unqueue(vec[i].fte, vec[i].fin);

        Burbujeo(aux, j);

        for(int k = 0; k < j; k++)
            Queue(vec[i].fte, vec[i].fin, aux[k]);
    }
    return;
}

int CalcularTamaño(nodo* &fte, nodo* &fin)
{
    int tam = 0;
    cola aux;
    aux.fte = NULL;
    aux.fin = NULL;
    while(fte != NULL)
    {
        Queue(aux.fte, aux.fin, Unqueue(fte, fin));
        tam++;
    }

    fte = aux.fte;
    fin = aux.fin;
    return tam;
}

cola AparearColas(nodo* &aFTE, nodo* &aFIN, nodo* &bFTE, nodo* &bFIN)
{
    cola colaFinal;
    colaFinal.fte = NULL;
    colaFinal.fin = NULL;
    int aTam = CalcularTamaño(aFTE, aFIN);
    int bTam = CalcularTamaño(bFTE, bFIN);

    int aVec[aTam];
    int bVec[bTam];

    int i = 0;
    int j = 0;

    while(aFTE != NULL)
    {
        aVec[i++] = Unqueue(aFTE, aFIN);
    }

    while(bFTE != NULL)
    {
        bVec[j++] = Unqueue(bFTE, bFIN);
    }

    //Burbujeo(aVec, aTam);
    //Burbujeo(bVec, bTam);
    i = 0;
    j = 0;
    while(i < aTam && j < bTam)
    {
        if(aVec[i] < bVec[j])
            Queue(colaFinal.fte, colaFinal.fin, aVec[i++]);

        else
            Queue(colaFinal.fte, colaFinal.fin, bVec[j++]);
    }

    while(i < aTam)
        Queue(colaFinal.fte, colaFinal.fin, aVec[i++]);

    while(j < bTam)
        Queue(colaFinal.fte, colaFinal.fin, bVec[j++]);

    return colaFinal;

}

cola GenerarColaFinal(cola vec[], int tam)
{
    cola colaFinal;
    colaFinal.fte = NULL;
    colaFinal.fin = NULL;

    int i;
    for(i = 1; i < tam; i++)
    {
        vec[i] = AparearColas(vec[i-1].fte, vec[i-1].fin, vec[i].fte, vec[i].fin);
    }
    i--;
    //int tamFinal = CalcularTamaño(vec[i].fte, vec[i].fin);
    while(vec[i].fte != NULL)
    {
        Queue(colaFinal.fte, colaFinal.fin, Unqueue(vec[i].fte, vec[i].fin));
    }
    return colaFinal;
}

void MostrarCola(cola cola)
{
    while(cola.fte != NULL)
    {
        cout << Unqueue(cola.fte, cola.fin) << endl;
    }
}