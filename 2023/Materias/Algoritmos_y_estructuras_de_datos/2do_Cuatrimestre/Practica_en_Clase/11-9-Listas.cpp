#include <iostream>

using namespace std;

struct info
{
    int a;
};


struct nodo
{
    info info;
    nodo* sgte;
};

void CargarArchivo(FILE*);
info Pop(nodo* &);
nodo* InsertarOrdenado(nodo* &, info);
void MostrarLista(nodo*);
void MostrarListaBorrando(nodo* &);

int main()
{
    FILE* f = fopen("lista.dat", "wb+");
    nodo* lista = NULL;

    int regSize = sizeof(info);

    CargarArchivo(f);

    info vActual;
    while(fread(&vActual, regSize, 1, f))
    {
        InsertarOrdenado(lista, vActual);
    }
    MostrarLista(lista);
}

void CargarArchivo(FILE* f)
{
    info val;
    int regSize = sizeof(info);
    cout << "Valor a cargar: ";
    cin >> val.a;
    while(val.a > 0)
    {
        fwrite(&val, regSize, 1, f);
        cout << "Valor a cargar: ";
        cin >> val.a;
    }

    fseek(f, 0, SEEK_SET);
    return;
}
info Pop(nodo* &pila)
{
    info x;
    nodo* p = pila;
    x = p->info;
    pila = p->sgte;
    delete p; // Libera el espacio de la variable, deja de ser zombie

    return x;
}

nodo* InsertarOrdenado(nodo* &lista, info val)
{
    nodo* q = lista;
    nodo* n = new nodo();
    n->info = val;

    if(lista == NULL || val.a < lista->info.a) // Poner al principio
    {
        n->sgte = lista;
        lista = n;
    }
    else 
    {
        while(q->sgte != NULL && q->sgte->info.a < val.a)
        {
            q = q->sgte;
        }
        n->sgte = q->sgte;
        q->sgte = n;
    }
    return n;
    
}

void MostrarLista(nodo* lista)
{
    nodo* q = lista;
    //int i = 0;
    cout << endl <<  "LISTA:" << endl;
    while(q != NULL)
    {
        cout << q->info.a << endl;
        q = q->sgte;
    }
    cout << endl;
}

void MostrarListaBorrando(nodo* &lista)
{
    
    //int i = 0;
    cout << endl <<  "LISTA:" << endl;
    info aux;
    while(lista != NULL)
    {
        aux = Pop(lista);
        cout << aux.a << endl;
    }
    cout << endl;
}
