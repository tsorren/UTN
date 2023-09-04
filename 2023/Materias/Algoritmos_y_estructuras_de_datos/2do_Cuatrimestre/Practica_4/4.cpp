/*
    Ejercicio Nro. 4:
    Dada una pila y dos valores X e Y,
    desarrollar un procedimiento que reemplace cada valor igual a X
    que se encuentre en la pila por el valor Y
    retornando la pila modificada.
    En caso de no haber ningún valor igual a X retornar la pila sin cambio.
    (Definir parámetros y codificar).
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
void Reemplazar(nodo* &, int, int);
void MostrarPila(nodo* &);

int main()
{
    nodo* pila = NULL;
    int x, y;

    CargarPila(pila);

    cout << "Ingrese el valor que a reemplazar: ";
    cin >> x;
    cout << "Ingrese el valor que reemplazará los otros: ";
    cin >> y;

    MostrarPila(pila);

    Reemplazar(pila, x, y);

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

void CargarPila(nodo* &p)
{
    int input;
    cout << "Ingrese el valor a cargar: ";
    cin >> input;
    while(input > -1)
    {
        Push(p, input);

        cout << "Ingrese el valor a cargar: ";
        cin >> input;
    }
    cout << endl;
    return;
}

void Reemplazar(nodo* &p, int valReemplazar, int valFinal)
{
    nodo* aux = NULL;
    int valActual;


    while(p != NULL)
    {
        valActual = Pop(p);
        if(valActual == valReemplazar)            
            Push(aux, valFinal);
        else
            Push(aux, valActual);
        
    }

    while(aux != NULL)
    {
        valActual = Pop(aux);
        Push(p, valActual);
    }
}

void MostrarPila(nodo* &p)
{
    nodo* aux = NULL;
    int i = 0;
    int vActual;

    while(p != NULL)
    {
        vActual = Pop(p);
        cout << "Pos " << i << ": " << vActual << endl;
        Push(aux, vActual);
        i++;
    }

    while(aux != NULL)
    {
        vActual = Pop(aux);
        Push(p, vActual);
    }
    cout << endl;
}