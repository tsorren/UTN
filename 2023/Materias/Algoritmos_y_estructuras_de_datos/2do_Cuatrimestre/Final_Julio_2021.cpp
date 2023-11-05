#include <iostream>
#include <cstring>

using namespace std;

//1.
struct infoLD
{
    int campo1;
    char campo2[20+1];
    float campo3;
    int campo4;
};

struct nodoLD
{
    infoLD info;
    nodoLD* sgte;
};

struct infoLS{
    float campo3;
    int campo4;
};

struct nodoLS{
    infoLS info;
    nodoLS* sgte;
};

struct infoLR
{
    float campo1;
    char campo2[20+1];
    nodoLS* ptrSubLista;
};

struct nodoLR
{
    infoLR info;
    nodoLR* sgte;
};

//2.
nodoLR* cargarListaDeListas(nodoLD* listaDato)
{
    nodoLR* listaR = NULL;
    nodoLR* nodoAux = NULL;
    infoLD auxLD;
    infoLS auxLS;
    infoLR auxLR;

    while(listaDato!=NULL)
    {
        auxLD = pop(listaDato);

        auxLR.campo1 = auxLD.campo1;
        strcpy(auxLR.campo2, auxLD.campo2);

        auxLS.campo3 = auxLD.campo3;
        auxLS.campo4 = auxLD.campo4; 
        nodoAux = insertarSinRepetir(listaR,auxLR);

        insertarOrdenado(nodoAux->info.ptrSubLista, auxLS);
    }
    return listaR;
}

//3.
nodoLR* listaResultado = cargarListaDeListas(listaDato);

//4.
/*
CONTEXTO:
    Dentro de un sistema de información de un hospital que abrazó las ideas de la libertad, se necesita almacenar los siguientes datos de las atenciones médicas:
    dni del paciente, nombre del paciente, fecha de atención, descripción del problema, médico asignado
    
    

ALTERNATIVA 1 (lista ordenada con repetición)
FORTALEZAS: 
    Menor complejidad a la hora de implementar algoritmos, ya que se maneja una única lista.
    En caso de que un paciente tenga muchas atenciones, no te vas a olvidar del paciente.

DEBILIDADES: 
    Mayor desarrollo de código, lectura innecesaria de datos, mayor tiempo de acceso.

ALTERNATIVA 2 (lista ordenada con sublista)
FORTALEZAS: 
    Menor tiempo de acceso, menos tráfico en el bus de datos.
    Facilidad a la hora de avanzar al siguiente paciente en la lista principal.
    
DEBILIDADES:
    El acceso a un nodo específico se vuelve más tedioso y encrucijado, ya que no abraza las ideas de la libertad.
*/