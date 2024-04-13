#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

struct reg
{
    int mes;
    int idVendedor;
    int cantVendida;
};

struct nodo
{
    int info;
    nodo* sgte;
};

struct regLS
{
    int idVendedor;
    int cantVendida;
};

struct nodoLS
{
    regLS info;
    nodoLS* sgte;
};

struct regLP
{
    int mes;
    nodoLS* ptrLS;
};

struct nodoLP
{
    regLP info;
    nodoLP* sgte;
};

void CargarArchivo(FILE*);

int Pop(nodo* &);
nodo* InsertarOrdenado(nodo* &, int);
nodo* Buscar(nodo*, int buscado);
nodo* InsertarSinRepetir(nodo* &, int);

nodoLS* InsertarOrdenado(nodoLS* &, regLS);

nodoLP* InsertarOrdenado(nodoLP* &, regLP);
nodoLP* Buscar(nodoLP*, regLP buscado);
nodoLP* InsertarSinRepetir(nodoLP* &, regLP);

void MostrarLista(nodo*);
void MostrarListaBorrando(nodo* &);
void MostrarListaDeListas(nodoLP*);

nodo* f();

int main()
{
    /*
    FILE* f = fopen("lista.dat", "rb+");
    nodoLP* LP = NULL;

    int regSize = sizeof(reg);
    reg auxArch;

    //CargarArchivo(f);
    
    while(fread(&auxArch, 1, regSize, f))
    {
        regLP infoLP;
        regLS infoLS;

        infoLP.mes = auxArch.mes;
        infoLP.ptrLS = NULL;

        infoLS.idVendedor = auxArch.idVendedor;
        infoLS.cantVendida = auxArch.cantVendida;

        nodoLP* NodoActualLP = InsertarSinRepetir(LP, infoLP);

        InsertarOrdenado(NodoActualLP->info.ptrLS, infoLS);
    }

    MostrarListaDeListas(LP);
    */
    nodo* l = f();
    cout << l->info;

    return 0;    
}

nodo* f()
{
    nodo* l = NULL;
    InsertarOrdenado(l, 3);
    return l;
}

void CargarArchivo(FILE* f)
{
    reg val;
    int regSize = sizeof(reg);
    cout << "Nueva venta:" << endl;
    cout << "    Mes: ";
    cin >> val.mes;
    while(val.mes > 0)
    {
        cout << "    ID Vendedor: ";
        cin >> val.idVendedor;

        cout << "    Cantidad Vendida: ";
        cin >> val.cantVendida;
        cout << endl;

        fwrite(&val, regSize, 1, f);

        cout << "Nueva venta:" << endl;
        cout << "    Mes: ";
        cin >> val.mes;
    }

    fseek(f, 0, SEEK_SET);
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

nodo* InsertarOrdenado(nodo* &lista, int val)
{
    nodo* q = lista;
    nodo* n = new nodo();
    n->info = val;

    if(lista == NULL || val < lista->info) // Poner al principio
    {
        n->sgte = lista;
        lista = n;
    }
    else 
    {
        while(q->sgte != NULL && q->sgte->info < val)
        {
            q = q->sgte;
        }
        n->sgte = q->sgte;
        q->sgte = n;
    }
    return n;
    
}

nodo* Buscar(nodo* lista, int buscado)
{
    nodo* aux = lista;
    while(aux != NULL && aux->info != buscado)
        aux = aux->sgte;

    return aux;
}

nodo* InsertarSinRepetir(nodo* &lista, int val)
{
    nodo* encontro = Buscar(lista, val);
    if(encontro == NULL)
        encontro = InsertarOrdenado(lista, val);

    return encontro;
}
//------------------------------------------------------

nodoLS* InsertarOrdenado(nodoLS* &lista, regLS val)
{
    nodoLS* q = lista;
    nodoLS* n = new nodoLS();
    n->info = val;

    if(lista == NULL || val.idVendedor < lista->info.idVendedor) // Poner al principio
    {
        n->sgte = lista;
        lista = n;
    }
    else 
    {
        while(q->sgte != NULL && q->sgte->info.idVendedor < val.idVendedor)
        {
            q = q->sgte;
        }
        n->sgte = q->sgte;
        q->sgte = n;
    }
    return n;
    
}

//------------------------------------------------------

nodoLP* InsertarOrdenado(nodoLP* &lista, regLP val)
{
    nodoLP* q = lista;
    nodoLP* n = new nodoLP();
    n->info = val;

    if(lista == NULL || val.mes < lista->info.mes) // Poner al principio
    {
        n->sgte = lista;
        lista = n;
    }
    else 
    {
        while(q->sgte != NULL && q->sgte->info.mes < val.mes)
        {
            q = q->sgte;
        }
        n->sgte = q->sgte;
        q->sgte = n;
    }
    return n;
    
}

nodoLP* Buscar(nodoLP* lista, regLP buscado)
{
    nodoLP* aux = lista;
    while(aux != NULL && aux->info.mes != buscado.mes)
        aux = aux->sgte;

    return aux;
}

nodoLP* InsertarSinRepetir(nodoLP* &lista, regLP val)
{
    nodoLP* encontro = Buscar(lista, val);
    if(encontro == NULL)
        encontro = InsertarOrdenado(lista, val);

    return encontro;
}
//------------------------------------------------------
void MostrarLista(nodo* lista)
{
    nodo* q = lista;
    //int i = 0;
    cout << endl <<  "LISTA:" << endl;
    while(q != NULL)
    {
        cout << q->info << endl;
        q = q->sgte;
    }
    cout << endl;
}

void MostrarListaBorrando(nodo* &lista)
{
    
    //int i = 0;
    cout << endl <<  "LISTA:" << endl;
    int aux;
    while(lista != NULL)
    {
        aux = Pop(lista);
        cout << aux << endl;
    }
    cout << endl;
}

void MostrarListaDeListas(nodoLP* LP)
{
    nodoLP* auxLP = LP;
    nodoLS* auxLS = NULL;
    
    cout << "--------------------------------------------------" << endl << endl;
    while(auxLP != NULL)
    {
        cout << "Ventas del mes " << auxLP->info.mes << ":" << endl;

        auxLS = auxLP->info.ptrLS;
        while(auxLS != NULL)
        {
            cout << "     ID Vendedor: " << auxLS->info.idVendedor << endl;
            cout << "          Ventas: " << auxLS->info.cantVendida << endl;
            cout << endl;
            auxLS = auxLS->sgte;
        }
        auxLP = auxLP->sgte;
        cout << "--------------------------------------------------" << endl << endl;
    }
}