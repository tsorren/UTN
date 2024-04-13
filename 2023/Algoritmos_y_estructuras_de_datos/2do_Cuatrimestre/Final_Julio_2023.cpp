#include <iostream>

using namespace std;

// 3.

struct nodoCola{
    char info[40+1];
    nodoCola* sgte;
};

//Colaprioridad = lista
struct infoL{
    int prioridad;
    nodoCola* fte = NULL;
    nodoCola* fin = NULL;
};

struct nodoL{
    infoL info;
    nodoL* sgte;
};

nodoL* ColaPrioridad = NULL;

// 1.

void crearColaPrioridad(nodoL*&);
/*
    Parametros: colaPrioridad de tipo nodoColaP*
    PRE: inicializar la cola prioridad en NULL
    POST: la cola prioridad contiene 5 nodos, ordenados por prioridad con una cola inicializada en NULL
    RETORNA: nada
*/

nodoL* insertarEnPrioridad(nodoL*&, int, char[]);
/*
    Parametros: colaPrioridad, int prioridad a buscar, char[] nombre a cargar
    PRE: prioridad es un entero entre el 0 y el 4, la lista 
    POST: Se inserta el nombre dentro de la cola en el nodo de la ColaPrioridad que corresponde a la prioridad del parametro
    RETORNA: retorna el puntero al nodo de la lista ColaPrioridad que contiene la cola segun prioridad
*/

char* elementoMinimo(nodoL*&);
/*
    Parametros: colaPrioridad
    PRE: colaPrioridad ordenada por prioridad y al menos una cola distinta NULL
    POST: El elemento minimo se mantiene en la cola
    RETORNA: puntero a la primer posicion de la cadena de caracteres del nombre del paciente con mayor prioridad
*/

void quitarMinimo(nodoL*&);
/*
    Parametros: colaPrioridad
    PRE: colaPrioridad ordenada por prioridad y al menos una cola distinta NULL
    POST: El elemento minimo es eliminado de la cola
    RETORNA: nada
*/

bool colaVacia(nodoL*, int);
/*
    Parametros: colaPrioridad, prioridad a buscar
    PRE: colaPrioridad ordenada por prioridad
    POST: No afecta a colaPrioridad
    RETORNA: true si fte del nodo de colaPrioridad que corresponde a prioridad es igual a NULL, false sino
*/

bool prioridadVacia(nodoL*);
/*
    Parametros: colaPrioridad
    PRE: colaPrioridad ordenada por prioridad
    POST: No afecta a colaPrioridad
    RETORNA: true si todas las colas estan vacias, false sino
*/



    
// 2.
int main(){
    
    crearColaPrioridad(ColaPrioridad);
    
    insertarEnPrioridad(ColaPrioridad, 0, "pepe");
    insertarEnPrioridad(ColaPrioridad, 1, "juan");
    insertarEnPrioridad(ColaPrioridad, 2, "carlos");
    insertarEnPrioridad(ColaPrioridad, 3, "raul");
    insertarEnPrioridad(ColaPrioridad, 4, "alberterto");
    insertarEnPrioridad(ColaPrioridad, 0, "creeper");

    while(!prioridadVacia(ColaPrioridad))
    {
        atenderPaciente(elementoMinimo(ColaPrioridad));
        quitarMinimo(ColaPrioridad);
    }

    return 0;
}