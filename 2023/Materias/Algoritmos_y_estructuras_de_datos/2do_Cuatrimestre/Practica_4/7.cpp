/*
    Dada una pila desarrollar un procedimiento que ordene la misma de acuerdo al valor de 
    sus nodos y la retorne. Solo se deben usar pilas. (Definir parámetros y codificar).
*/
#include <iostream>

using namespace std;

struct nodo
{
    int info;
    nodo* sgte;
};

void Push(nodo* &, int);
int Pop(nodo* &);

void CargarPila(nodo* &);
void OrdenarPila(nodo* &);
void MostrarPila(nodo* &);

int main()
{
    nodo* pila = NULL;

    CargarPila(pila);

    OrdenarPila(pila);

    MostrarPila(pila);


    return 0;
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

void CargarPila(nodo* &pila)
{
    int val;
    cout << "Ingrese el valor a cargar: ";
    cin >> val;

    while(val > -1)
    {
        Push(pila, val);
        cout << "Ingrese el valor a cargar: ";
        cin >> val;
    }
    cout << endl;
}

void OrdenarPila(nodo* &pila) // Creciente
{
    nodo* aux = NULL;

    int valorAux;
    int valorAux2;

    while(pila != NULL)
    {
        valorAux = Pop(pila);
        while(aux != NULL )
        {
            valorAux2 = Pop(aux);
            if(valorAux2 < valorAux)
            {
                Push(pila, valorAux2);
            }
            else 
            {
                Push(aux, valorAux2);
            }
        }
        Push(aux, valorAux);
    }
    pila = aux;
}

void MostrarPila(nodo* &p)
{
    int i = 0;
    int val;

    //nodo* aux = NULL;

    while(p != NULL)
    {
        val = Pop(p);
        cout << "Pos " << i << ": " << val << endl;
        i++;
        //Push(aux, val);
    }
    /*
    while(aux != NULL)
    {
        Push(p, Pop(aux));
    }
    cout << endl;
    */
    return;
}