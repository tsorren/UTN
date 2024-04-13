/*
    Ejercicio Nro. 5:
    Definir una función INVERSA que evalúe dos conjuntos de caracteres separados
    por un punto y retorne True si los conjuntos son inversos (ej: ABcDe.eDcBA) 
    o False si no lo son.
    Los conjuntos deben ingresarse por teclado. (Definir parámetros y codificar).

    aux
    pop -> aux hasta punto
    skip punto
    check pila = aux cada pop
    return
*/

#include <iostream>

using namespace std;

struct nodo
{
    char info;
    nodo* sgte;
};

void Push(nodo* &, char);
char Pop(nodo* &);

bool SonInversos(char[]);

int main()
{
    char conjunto[64+1];

    cout << "Ingrese dos conjutos de caracteres separados por un punto: ";
    cin >> conjunto;

    bool inversos = SonInversos(conjunto);
    if(inversos)
        cout << "Los conjuntos son inversos" << endl;
    else
        cout << "Los conjuntos no son inversos" << endl;

    return 0;
}

void Push(nodo* &pila, char val)
{
    nodo* p = new nodo();
    p->info = val;
    p->sgte = pila;

    pila = p;

    return;
}

char Pop(nodo* &pila)
{
    char val;
    nodo* p = pila;

    val = p->info;
    pila = p->sgte;

    delete p;
    
    return val;
}

bool SonInversos(char conj[])
{
    nodo* pila = NULL;
    nodo* aux = NULL;
    nodo* aux2 = NULL;
    
    char cActual;

    for(int i = 0; conj[i] != '\0'; i++)
    {
        Push(pila, conj[i]);
    }

    cActual = Pop(pila);
    while(cActual != '.' && cActual != '\0')
    {
        Push(aux, cActual);
        cActual = Pop(pila);
    }

    while(Pop(aux) == Pop(pila))
    {
        if(pila == NULL && aux == NULL)
        {
            return true;
        }
    }
    return false;
}