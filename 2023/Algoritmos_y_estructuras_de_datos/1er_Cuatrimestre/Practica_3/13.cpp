/*
    Una empresa que distribuye mercadería hacia distintas localidades del interior dispone de 
    dos archivos de registros: 
    Uno denominado DESTINOS con información de la distancia a cada uno de los destinos: 
    a) Nro. De destino (3 dígitos) 
    b) Distancia en kilómetros (NNN.NNN) 

    Otro denominado VIAJES con los viajes realizados por cada camión (< 200), donde cada 
    registro contiene: 
    a) Patente del camión (6 caracteres) 
    b) Nro. de destino 
    c) Nro. de chofer (1 a 150) 

    Desarrollar estrategia, algoritmo y codificación del programa que determine e imprima: 
    1) Cantidad de viajes realizados a cada destino (solo si > 0). 
    2) Nro. de chofer con menor cantidad de Km (entre los que viajaron). 
    3) Patente de los camiones que viajaron al destino 116 sin repeticiones de las mismas. // Cant viajes -> busqueda
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

struct destino
{
    int destino;
    float distancia;
};

struct viaje
{
    char patente[6+1];
    int destino;
    int chofer;
};

void CargarDestinos(FILE*);
void CargarViajes(FILE*);

int CantidadRegistros(FILE*, int);
void LeerArchivo(FILE*, destino[], int);
void LeerArchivo(FILE*, viaje[], int);

int CalcularMinimo(float[], int);
bool NoEsPatenteRepetida(char[][6+1], char[]);

void ProcesarDatos(int[], int&, char[][6+1], int&, viaje[], int, destino[]);
void MostrarCantidadViajes(int[]);
void MostrarChoferMenorDist(int);
void MostrarPatentesDestino(char[][6+1], int);

int main()
{
    FILE* destinosFile = fopen("archivos/ej13_destinos.dat", "rb+");
    FILE* viajesFile = fopen("archivos/ej13_viajes.dat", "rb+");

    //CargarDestinos(destinosFile);
    //CargarViajes(viajesFile);

    int destinosTam = CantidadRegistros(destinosFile, sizeof(destino));
    int viajesTam = CantidadRegistros(viajesFile, sizeof(viaje));

    destino destinos[destinosTam];
    LeerArchivo(destinosFile, destinos, destinosTam);

    viaje viajes[viajesTam];
    LeerArchivo(viajesFile, viajes, viajesTam);

    int viajesPorDestino[999] = {0};
    int choferDeMenorDistancia;
    char patentesDestino116[200][6+1];
    int patentesTam = 0;

    ProcesarDatos(viajesPorDestino, choferDeMenorDistancia, patentesDestino116, patentesTam, viajes, viajesTam, destinos);

    MostrarCantidadViajes(viajesPorDestino);
    MostrarChoferMenorDist(choferDeMenorDistancia);
    MostrarPatentesDestino(patentesDestino116, patentesTam);

    fclose(destinosFile);
    fclose(viajesFile);

    return 0;
}

void CargarDestinos(FILE* f)
{
    cout << "DESTINOS: " << endl;
    destino dest;
    int destSize = sizeof(destino);

    cout << "    Nro de destino: ";
    cin >> dest.destino;

    while(dest.destino >= 0)
    {
        cout << "    Distancia: ";
        cin >> dest.distancia;

        fwrite(&dest, destSize, 1, f);

        cout << endl;
        cout << "    Nro de destino: ";
        cin >> dest.destino;
    }
    fseek(f, 0, SEEK_SET);

    return;
}

void CargarViajes(FILE* f)
{
    cout << "VIAJES: " << endl;

    viaje viaj;
    int viajSize = sizeof(viaje);

    cout << "    Patente: ";
    cin >> viaj.patente;

    while(strcmp(viaj.patente, "STOP") != 0)
    {
        cout << "    Destino: ";
        cin >> viaj.destino;

        cout << "    Chofer: ";
        cin >> viaj.chofer;

        fwrite(&viaj, viajSize, 1, f);

        cout << endl;

        cout << "    Patente: ";
        cin >> viaj.patente;
    }

    fseek(f, 0, SEEK_SET);

    return;
}

int CantidadRegistros(FILE* f, int size)
{
    fseek(f, 0, SEEK_END);
    int reg = ftell(f) / size;
    fseek(f, 0, SEEK_SET);

    return reg;
}

void LeerArchivo(FILE* f, destino d[], int dTam)
{
    fseek(f, 0, SEEK_SET);
    fread(d, sizeof(destino), dTam, f);
    fseek(f, 0, SEEK_SET);

    return;
}

void LeerArchivo(FILE* f, viaje v[], int vTam)
{
    fseek(f, 0, SEEK_SET);
    fread(v, sizeof(viaje), vTam, f);
    fseek(f, 0, SEEK_SET);

    return;
}

bool NoEsPatenteRepetida(char pDest[][6+1], int pTam, char patente[])
{
    for(int i = 0; i < pTam; i++)
    {
        if(strcmp(patente, pDest[i]) == 0 )
        {
            return false;
        }
    }
    return true;
}

int CalcularMinimo(float d[], int dTam)
{
    float min = d[0];
    int indice;
    for(int i = 0; i < dTam; i++)
    {
        if(min > d[i] && d[i] > 0)
        {
            min = d[i];
            indice = i;
        }
    }
    return indice;
}

void ProcesarDatos(int viajesPorDest[], int& choferDeMenorDist, char patentesDest[][6+1], int& patentesTam, viaje v[], int vTam, destino d[])
{
    int indiceDest, indiceChof;
    float distanciaChoferes[150] = {0};


    for(int i = 0; i < vTam; i++)
    {
        indiceDest = v[i].destino;
        indiceChof = v[i].chofer - 1;

        viajesPorDest[indiceDest]++;
        distanciaChoferes[indiceChof] += d[indiceDest].distancia;

        if(indiceDest == 116 && NoEsPatenteRepetida(patentesDest, patentesTam, v[i].patente))
        {
            strcpy(patentesDest[patentesTam], v[i].patente);
            patentesTam++;
        }
    }
    choferDeMenorDist = CalcularMinimo(distanciaChoferes, 150) + 1;

    return;
}

void MostrarCantidadViajes(int c[])
{
    cout << "CANTIDAD DE VIAJES POR DESTINO:" << endl;
    for(int i = 0; i < 999; i++)
    {
        if(c[i] > 0)
        {
            cout << "    Destino " << i << ": " << c[i] << endl;
        }
    }
    cout << endl;
    return;
}

void MostrarChoferMenorDist(int chof)
{
    cout << "CÓDIGO DE CHOFER QUE MENOS DISTANCIA RECORRIÓ: " << chof << endl << endl; 
    return;
}

void MostrarPatentesDestino(char patentes[][6+1], int patentesTam)
{
    cout << "PATENTES QUE VIAJARON AL DESTINO 116: " << endl;
    for(int i = 0; i < patentesTam; i++)
    {
        cout << "    " << patentes[i] << endl;
    }
    cout << endl;
    return;
}