/*
    Dada una pila y un valor X colocar el valor x en la tercera  posicion se la pila, retornando 
    un  parámetro  con  valor  'S'  o  'N'  según  haya  sido  exitoso  o  no  el  requerimiento.  (Definir 
    parámetros y codificar).
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
// int ConseguirTamañoPila(nodo* &);

char CargarEnPosicion(nodo* &, int, int);

void MostrarPila(nodo* &);


int main()
{
    nodo* pila = NULL;
    int pilaTam = 0;

    CargarPila(pila);

    //pilaTam = ConseguirTamañoPila(pila);
    cout << "Tamaño: " << pilaTam << endl << endl;

    int val;
    cout << "Ingrese el valor a cargar en la tercera posición: ";
    cin >> val;

    char resultado = CargarEnPosicion(pila, val, 3);
    cout << endl << "Resultado: " << resultado << endl;

    MostrarPila(pila);

    return 0;
}

void Push(nodo* &pila, int info)
{
    nodo* p = new nodo();

    p->info = info;
    p->sgte = pila;

    pila = p;

    return;
}

int Pop(nodo* &pila)
{
    int x;
    nodo* p = pila;

    x = p->info;
    pila = p->sgte;
    
    delete p; // Libera el espacio de la variable, deja de ser zombie

    return x;
}

void CargarPila(nodo* &pila)
{
    int val = 0;
    cout << "Valor: ";
    cin >> val;
    while(val > -1)
    {
        Push(pila, val);
        cout << "Valor: ";
        cin >> val;
    }
    return;
}
// NO VA
/*
int ConseguirTamañoPila(nodo* &pila)
{
    int i = 0;
    nodo* ptr = pila;
    while(ptr != NULL)
    {
        i++;
        ptr = ptr->sgte;
    }
    return i;
}
*/

char CargarEnPosicion(nodo* &pila, int val, int pos)
{
    nodo* aux = NULL;

    for(int i = 0; i < pos; i++)
    {
        Push(aux, Pop(pila));
        if(pila == NULL)
            return 'N';
    }
    Push(aux, val);


    while(aux != NULL)
    {
        Push(pila, Pop(aux));
    }

    return 'S';
}
void MostrarPila(nodo* &pila)
{
    int i = 0;
    int val;
    while(pila != NULL)
    {
        val = Pop(pila);
        cout << i << ": " << val << endl;
        i++;
    }
}

