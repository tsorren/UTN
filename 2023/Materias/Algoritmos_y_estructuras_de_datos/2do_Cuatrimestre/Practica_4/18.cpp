/*
    Dadas  dos  listas  LISTA  y  LISTB  (nodo  =  registro  +  puntero),  desarrollar  y  codificar  un 
    procedimiento que genere una única lista LISTC a partir de ellas. (Primero los nodos de LISTA 
    y luego los de LISTB).
*/
#include <iostream>

using namespace std;

struct nodo
{
    int val;
    nodo* sgte;
};

int Pop(nodo* &);
nodo* InsertaAlFinal(nodo* &, int);

nodo* CargarLista();
nodo* UnirListas(nodo*, nodo*);
void MostrarLista(nodo*);

int main()
{
    nodo* listaA = NULL;
    nodo* listaB = NULL;
    nodo* listaC = NULL;

    listaA = CargarLista();
    listaB = CargarLista();
    listaC = UnirListas(listaA, listaB);
    MostrarLista(listaC);
    return 0;
}

int Pop(nodo* &lista)
{
    int val;
    nodo* n = lista;
    val = n->val;
    lista = n->sgte;

    delete n;
    return val;
}

nodo* CargarLista()
{
    int val;
    nodo* lista = NULL;

    cout << "CARGANDO NUEVA LISTA:" << endl;

    cout << "    Valor a cargar: ";
    cin >> val;
    while(val > -1)
    {
        InsertaAlFinal(lista, val);   
        cout << "    Valor a cargar: ";
        cin >> val;
    }
    cout << endl;
    return lista;
}

nodo* InsertaAlFinal(nodo* &lista, int val)
{
    nodo* n = new nodo();
    n->val = val;
    n->sgte = NULL;

    if(lista == NULL)
        lista = n;
    else
    {
        nodo* q = lista;
        while(q->sgte != NULL)
            q = q->sgte;
        
        q->sgte = n;
    }
    return n;
}

nodo* UnirListas(nodo* a, nodo* b)
{
    nodo* c = NULL;
    while(a != NULL)
        InsertaAlFinal(c, Pop(a));

    while(b != NULL)    
        InsertaAlFinal(c, Pop(b));
    return c;
}

void MostrarLista(nodo* lista)
{
    nodo* aux = lista;
    cout << "LISTA:" << endl;
    while(aux != NULL)
    {
        cout << aux->val << endl;
        aux = aux->sgte;
    }
    cout << endl;
}