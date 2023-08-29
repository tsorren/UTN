#include <iostream>

using namespace std;

struct nodo{
    int info;
    nodo *sgte;
};

void Push(nodo*&, int);
int Pop(nodo*&);
int* Dir(int);

int ConseguirTamañoPila(nodo*&);
void CargarPila(nodo* &);
char CargarEnPosicion(nodo* &, int, int);
void MostrarPila(nodo* &);

int main()
{
    nodo* p = new nodo();
    (*p).info = 0;
    p->info = 3;
    p->sgte = new nodo();

    nodo* pila = NULL; // Siempre se inicializa en NULL para saber si está vacía
    Push(pila, 10);
    Push(pila, 20);
    Push(pila, 30);
    Push(pila, 40);

    while(pila != NULL)
    {
        cout << Pop(pila) << endl;
    }
    int *ptr = Dir(10);
    cout << ptr << "  " << *ptr << endl;
    return 0;
}

void Push(nodo* &pila, int info)
{
    //armar nodo y reservar memoria
    nodo* p = new nodo();
    //guardar la info
    p->info = info;
    p->sgte = pila;
    //apuntar
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

int* Dir(int a){
    int x = a;
    int *p = &x;
    return p;
}
// NO VA
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

