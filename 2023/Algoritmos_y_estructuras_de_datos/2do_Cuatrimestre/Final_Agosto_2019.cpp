#include <iostream>
#include <cstring>
using namespace std;

/*
3. (2 puntos)
    Declare y defina todas las estructuras de datos
    que requiere el problema.
*/

struct regArch
{
    int DNI;
    char apeNom[50+1];
    int dedo;
    int tipo;
    int subtipo;
};

struct regLS
{
    int DNI;
    char apeNom[50+1];
};

struct nodoLS
{
    regLS info;
    nodoLS* sgte;
};

struct regLP
{
    nodoLS* sublista;
    int dedo;
};

struct nodoLP
{
    regLP info;
    nodoLP* sgte;
};

nodoLP* matrizSospechosos[4][9];
FILE* antecedentesArch = fopen("antecedentes.dat", "rb");

void InicializarMatrizSospechosos(nodoLP* m[][9])
{
    for(int x = 0; x < 4; x++)
        for(int y = 0; y < 9; y++)
            m[x][y] = NULL;
    
    return;
}

/*
1. (3 puntos)
    Codifique o diagrame la función, cargarMatrizSospechosos
    que cargue los datos del archivo en una matriz
    (Tipo en las filas y Subtipo en las columnas) 
    de punteros a una lista de sospechosos,
    ordenados alfabéticamente por nombre
    en forma creciente con una sublista
    al numero de dedo con ese tipo y subtipo.
*/

void cargarMatrizSospechosos(FILE* f, nodoLP* m[][9])
{
    regArch aux;
    regLS sospechoso;
    nodoLP* nodoAux;

    int regSize = sizeof(regArch);
    int x, y;

    fseek(f, 0, SEEK_SET);
    while(fread(&aux, regSize, 1, f))
    {
        x = aux.tipo - 1;
        y = aux.subtipo;

        strcpy(sospechoso.apeNom, aux.apeNom);
        sospechoso.DNI = aux.DNI;

        nodoAux = InsertarSinRepetir(m[x][y], aux.dedo);
        InsertarOrdenado(nodoAux->info.sublista, sospechoso);
    }
}

/*
2. (3 puntos) 
    Codifique o diagrame la función emitirSospechosos
    que con las estructuras cargadas en el punto anterior y
    dado un determinado tipo y subtipo, permita determinar e imprimir
    ordenado por apellido y nombre aquellas personas
    que coincidan en tipo y subtipo y el nombre
    del dedo y mano en la que coinciden. 
*/

void emitirSospechosos(nodoLP* m[][9], int tipo, int subtipo)
{
    char dedos[5][8+1] = {"Pulgar", "Indice", "Corazón", "Anular", "Meñique"};
    nodoLP* LP = m[tipo - 1][subtipo];
    nodoLS* LS;

    int dedoActual;

    cout << "COINCIDENCIAS: " << endl;
    while(LP != NULL)
    {
        LS = LP->info.sublista;
        if(LP->info.dedo < 6)
            cout << "Mano Derecha - ";
        else
            cout << "Mano Izquierda - ";

        dedoActual = (LP->info.dedo - 1) % 1;
        cout << dedos[dedoActual] << ": " << endl;

        while(LS != NULL)
        {
            cout << "    DNI: " << LS->info.DNI << endl;
            cout << "    NOMBRE: " << LS->info.apeNom << endl << endl;
            LS = LS->sgte;
        }
        LP = LP->sgte;
    }
}
/*
4.
    Responda justificando si son verdaderas o falsas las siguientes afirmaciones.
    a. (1 Punto) 
        Las estructuras enlazadas pueden ser implementadas en vectores
        Falso. Las estructuras enlazada poseen la gran ventaja de poseer tamaño dinámico, por lo que sirven para resolver problemas
        donde no se conoce el tamaño necesario para la estructura.
        
    b. (1 Punto) 
        El análisis de caso simple (if) solo evalua expresiones booleanas
            Falso. El analisis de caso simple evalua las expresiones que recibe, y las interpreta como expresiones booleanas
*/