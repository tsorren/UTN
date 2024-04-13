#include <iostream>
#include <cstring>

using namespace std;

// ESTRUCTURAS DE DATOS
struct reg
{
    int a;
};

struct nodo
{
    reg info;
    nodo* sgte;
};

struct regLP
{
    nodo* listaS;
};

struct nodoLP
{
    regLP info;
    nodoLP* sgte;
};

// PROTOTIPOS
//      VECTORES
void Agregar(reg[], int&, reg);
void Mostrar(reg[], int);
void Ordenar(reg[], int); // Burbuja
int Buscar(reg[], int, reg); // Busqueda Secuencial
int BusquedaBinaria(reg[], int, reg);

//      ARCHIVOS
reg Leer(FILE*);
void LeerN(FILE*, reg[], int);
void Grabar(FILE*, reg);
void GrabarN(FILE*, reg[], int);
void IrA(FILE*, int, int);
int CantReg(FILE*, int);
int RegActual(FILE*, int);
int BusquedaBinaria(FILE*, int, int);

//      ESTRUCTURAS ENLAZADAS
void Push(nodo*&, reg);
reg Pop(nodo*&);

void Queue(nodo*&, nodo*&, reg);
reg UnQueue(nodo*&, nodo*&);

nodo* InsertarDelante(nodo*&, reg);
nodo* InsertarEnMedio(nodo*&, reg);
nodo* InsertarAlFinal(nodo*&, reg);
nodo* InsertarOrdenado(nodo*&, reg);
nodo* InsertarSinRepetir(nodo*&, reg);
nodo* Buscar(nodo*, reg);
int EliminarNodo(nodo*&, reg);
nodo* CargarSinRepetir(nodo*&, nodo, int);
void EliminarNodos(nodo*&);
nodoLP* ListaDeLista(nodo*, regLP, reg);


int main()
{
    return 0;
}


// FUNCIONES
//      VECTORES
void Agregar(reg vec[], int& tLogico, reg val)
{
    vec[tLogico++] = val;
    return;
}

void Mostrar(reg vec[], int tLogico)
{
    int i;
    cout << "Vector:" << endl;
    for(i = 0; i < tLogico; i++)
    {
        cout << "    " << i+1 << ": " << vec[i].a << endl;
    }
    cout << endl;
    return;
}

void Ordenar(reg vec[], int tLogico) // Burbuja
{
    int i, j;
    reg aux;
    for(i = 1; i < tLogico; i++)
    {
        for(j = 1; j <= tLogico - i; j++)
        {
            if(vec[j-1].a > vec[j].a)
            {
                aux = vec[j-1];
                vec[j-1] = vec[j];
                vec[j] = aux;
            }
        }
    }
    return;
} 

int Buscar(reg vec[], int tLogico, reg buscado) // Busqueda Secuencial
{
    int i;
    for(i = 0; i < tLogico; i++)
    {
        if(vec[i].a == buscado.a)
            return i;
    }
    return -1;
}

int BusquedaBinaria(reg vec[], int tLogico, reg buscado)
{
    int p = 0;
    int u = tLogico - 1;
    int m;
    while(p <= u)
    {
        m = (p+u)/2;
        if(vec[m].a == buscado.a)
            return m;
        if(vec[m].a < buscado.a)
            p = m + 1;
        if(vec[m].a > buscado.a)
            u = m - 1;
    }
    return -1;
}

//      ARCHIVOS
reg Leer(FILE* f)
{
    reg val;
    fread(&val, sizeof(reg), 1, f);
    return val;
}

void LeerN(FILE* f, reg vec[], int N)
{
    fread(vec, sizeof(reg), N, f);
    return;
}

void Grabar(FILE* f, reg val)
{
    fwrite(&val, sizeof(reg), 1, f);
    return;
}

void GrabarN(FILE* f, reg vec[], int N)
{
    fwrite(vec, sizeof(reg), N, f);
    return;
}

void IrA(FILE* f, int indice, int tamReg)
{
    fseek(f, indice*tamReg, SEEK_SET);
    return;
}

int CantReg(FILE* f, int tamReg)
{
    int posOriginal = ftell(f);
    int cant;

    fseek(f, 0, SEEK_END);
    cant = ftell(f) / tamReg;

    fseek(f, posOriginal, SEEK_SET);
    return cant;
}

int RegActual(FILE* f, int tamReg)
{
    return ftell(f) / tamReg;
}

int BusquedaBinaria(FILE* f, int buscado, int tamReg)
{
    int p = 0;
    int u = CantReg(f, tamReg) - 1;
    int m;
    int val;
    int valSize = sizeof(int);

    while(p <= u)
    {
        m = (p+u)/2;
        IrA(f, m, valSize);
        fread(&val, valSize, 1, f);
        if(val == buscado)
            return RegActual(f, valSize) - 1;
        if(val < buscado)
            p = m + 1;
        else
            u = m - 1;
    }
    return -1;
}

//      ESTRUCTURAS ENLAZADAS
void Push(nodo* &pila, reg val)
{
    nodo* p = new nodo();
    p->info = val;
    p->sgte = pila;

    pila = p;
    return;
}
reg Pop(nodo* &pila)
{
    nodo* p = pila;
    reg val = pila->info;

    pila = pila->sgte;

    delete p;
    return val;
}

void Queue(nodo* &fte, nodo* &fin, reg val)
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
reg UnQueue(nodo* &fte, nodo* &fin)
{
    nodo* p = fte;
    reg val = fte->info;
    fte = fte->sgte;

    if(fte == NULL)
        fin = NULL;
    
    delete p;
    return val;
}

nodo* InsertarDelante(nodo* &lista, reg val)
{
    nodo* n = new nodo();
    n->info = val;
    n->sgte = lista;
    lista = n;
    return n;
}
nodo* InsertarEnMedio(nodo* &lista, reg val)
{
    nodo* aux = lista;
    nodo* n = new nodo();
    n->info = val;
    n->sgte = NULL;
    while(aux->sgte != NULL && aux->sgte->info.a < val.a)
        aux = aux->sgte;
    n->sgte = aux->sgte;
    aux->sgte = n;
    return n;
}
nodo* InsertarAlFinal(nodo* &lista, reg val)
{
    nodo* aux = lista;
    nodo* n = new nodo();
    n->info = val;
    n->sgte = NULL;
    while(aux->sgte != NULL)
        aux = aux->sgte;
    aux->sgte = n;
    return n;
}
nodo* InsertarOrdenado(nodo* &lista, reg val)
{
    nodo* n = new nodo();
    n->info = val;
    if(lista == NULL || lista->info.a > val.a)
    {
        n->sgte = lista;
        lista = n;
    }
    else
    {
        nodo* aux = lista;
        while(aux->sgte != NULL && aux->sgte->info.a > val.a)
            aux = aux->sgte;
        n->sgte = aux->sgte;
        aux->sgte = n;
    }
    return n;
}
nodo* InsertarSinRepetir(nodo* &lista, reg val)
{
    nodo* encontrado = Buscar(lista, val);
    if(encontrado == NULL)
        return InsertarOrdenado(lista, val);

    return encontrado;
}
nodo* Buscar(nodo* lista, reg val)
{
    nodo* aux = lista;
    while(aux != NULL && aux->info.a != val.a)
        aux = aux->sgte;

    return aux;
}
int EliminarNodo(nodo* &lista, reg val)
{
    nodo* aux = lista;
    while(aux != NULL && aux->sgte->info.a != val.a)
        aux = aux->sgte;
    if(aux == NULL)
        return 0;
    nodo* n = aux->sgte;
    aux->sgte = aux->sgte->sgte;
    delete n;
    return 1;
}
nodo* CargarSinRepetir(nodo* &lista, reg info, int val)
{
    nodo* n = InsertarSinRepetir(lista, info);
    n->info.a += val;

    return n;
}
void EliminarNodos(nodo* &lista)
{
    nodo* aux;
    while(lista != NULL)
    {
        aux = lista;
        lista = lista->sgte;
        delete aux;
    }
    
    return;
}
nodoLP* ListaDeLista(nodo*, regLP, reg);