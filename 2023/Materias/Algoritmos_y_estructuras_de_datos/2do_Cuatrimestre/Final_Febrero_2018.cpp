#include <iostream>
using namespace std;
/*
    FIFO Pila
    LIFO Cola
*/

/*
1. (1 puntos)
    Codifique la declaración todas estructuras de datos y
    las constantes que correspondan para la resolución correcta del problema, e inicialícelas adecuadamente.
*/

#define N 100

struct Nodo
{
    char info;
    Nodo* sgte;
}; Nodo* pila = NULL;

char cola[N];
int cInicio = 0;
int cFin = 0;
FILE* f = fopen("caracteres.dat", "rb");

/*
2. (2 puntos)
    Codifique o diagrame las funciones pop y push
    para implementar una pila con asignación dinámica en memoria.
*/

char pop(Nodo* &pila)
{
    Nodo* p = pila;
    char val = pila->info;

    pila = pila->sgte;

    delete p;
    return val;
}

void push(Nodo* &pila, char val)
{
    Nodo* p = new Nodo();
    p->info = val;
    p->sgte = pila;
    pila = p;
    return;
}

/*
3. (2 puntos) 
    Codifique o diagrame la función que recibe un vector de caracteres,
    un carácter a cargar en el mismo y un valor donde debe ser insertado.
    agregarA_FIFO(vector, carácter,índice)
*/

void agregarA_FIFO(char cola[], char val, int& fin) // TODO
{
    cola[fin] = val; // Quitar cInicio??
    fin++;
    return;
}

/*
4. (2 puntos)
    Codifique o diagrame la función que recibe el vector de caracteres,
    el tope de donde tomar el carácter -el mismo debe ser actualizado- y
    retorna el carácter que estaba en el tope.
    suprimirDe_FIFO(vector, índice)
*/
char suprimirDe_FIFO(char cola[], int& tope)
{
    char val = cola[tope];
    tope++;
    return val;
}

/*
5. (1 puntos) 
    Codifique o diagrame la función ingresarCaracteres
    que toma los caracteres desde un archivo y los almacene en las estructuras LIFO y FIFO,
    según la implementación y uno por vez.
*/
void ingresarCaracteres(FILE* f, Nodo* pila, char cola[], int &cI, int &cF)
{
    char reg;
    int regSize = sizeof(char);
    while(fread(&reg, regSize, 1, f) && cF < N)
    {
        if(reg != ' ' && reg != ',') // ESTO VA?
        {
            push(pila, reg);
            agregarA_FIFO(cola, reg, cF);
        }
    }
    return;
}
/*6. (2 puntos)
    Codifique o diagrame la función esPalíndromo
    que reciba las estructuras adecuadas y determine
    si el conjunto de caracteres del flujo forman palíndromos.
*/
bool esPalindromo(Nodo* pila, char cola[], int &cI, int &cF)
{
    while(pila != NULL && cI < cF)
    {
        if(pop(pila) != suprimirDe_FIFO(cola, cI))
            return false;
    }
    return true;
}

