/*
    Una empresa de aviación realiza 500 vuelos semanales a distintos puntos del pais y 
    requiere un programa para el otorgamiento de pasajes. Para ello dispone de un archivo de 
    registros, en el que cada registro contiene información de los vuelos que realiza y la 
    cantidad de pasajes disponibles en cada uno de ellos según se indica: 
    a. Código del vuelo (6 dígitos) 
    b. Cantidad de pasajes disponibles (3 dígitos) 
    Se dispone además de otro archivo con los datos de los potenciales compradores, en el 
    que cada registro tiene: 
    a) Codigo de vuelo solicitado 
    b) Cantidad de pasajes solicitados (3 digitos) 
    c) DNI del solicitante (8 digitos)
    d) Apellido y nombres del solicitante (30 caracteres) 

    Desarrollar estrategia, algoritmo y codificacion del programa que determine e imprima: 
    1) Para los solicitantes a los cuales se les venden pasajes, 
    
    DNI - APELLIDO Y NOMBRES – CANTIDAD DE PASAJES - CODIGO VUELO 
    99999  \XXXXXX  999   999  

    2) Al final del proceso el siguiente listado: 
    CODIGO DE VUELO - PASAJES LIBRES  - PASAJES NO VENDIDOS 
    999999    999    999 
    Se le vende al solicitante si la cantidad de pasajes que solicita esta disponible, en 
    caso contrario se computa como pasajes no vendidos.


    estructura vuelo:
    int codigoVuelo
    int pasajesDisponibles

    estructura compradores:
    int codigoVuelo
    int pasajesSolicitados
    int DNI
    char apellidoNombre[30+1]

    matriz pasajes:
    [codigoVuelo][tipoPasaje] [][0] = pasajesDisponibles [][1] = pasajesLibres [][2] = pasajesNoVendidos

*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

using namespace std;

struct vuelo
{
    int codigoVuelo;
    int pasajesDisponibles;
};

struct comprador
{
    int codigoVuelo;
    int pasajesSolicitados;
    int DNI;
    char apellidoNombre[30+1];
};


void CargaDeDatos(FILE*, vuelo[], int&);
void CargaDeDatos(FILE*, comprador[], int&);

void LecturaDeDatos(FILE*, vuelo[], int&);
void LecturaDeDatos(FILE*, comprador[], int&);

void PrepararPUP(vuelo[], int, short int [], int [][2]);

void AnalizarSolicitudes(comprador[], int, comprador[], int&, short int [], int [][2]);

void MostrarVentas(comprador[], int);

void MostrarVuelos(vuelo[], int, short int [], int [][2]);

//void CorteDeControl();

int main()
{
    short int matrizCodigos[999999] = {-1};
    int matrizPasajes[500][2] = {-1, 0};

    vuelo vuelos[500];
    int vuelosTam = 0;

    comprador compradores[500];
    int compradoresTam = 0;

    FILE* archivoVuelos = fopen("archivos/ej8_vuelos.bin", "rb+");
    FILE* archivoCompradores = fopen("archivos/ej8_compradores.bin", "rb+");

    // CargaDeDatos(archivoVuelos, vuelos, vuelosTam);
    // CargaDeDatos(archivoCompradores, compradores, compradoresTam);

    LecturaDeDatos(archivoVuelos, vuelos, vuelosTam);
    LecturaDeDatos(archivoCompradores, compradores, compradoresTam);

    
    PrepararPUP(vuelos, vuelosTam, matrizCodigos, matrizPasajes);

    comprador ventas[compradoresTam];
    int ventasTam = 0;

    AnalizarSolicitudes(compradores, compradoresTam, ventas, ventasTam, matrizCodigos, matrizPasajes);

    cout << "VENTAS REALIZADAS: " << endl;
    cout << "------------------------------------------" << endl;
    MostrarVentas(ventas, ventasTam);
    cout << "------------------------------------------" << endl << endl << endl;

    cout << "VUELOS: " << endl;
    cout << "------------------------------------------" << endl;
    MostrarVuelos(vuelos, vuelosTam, matrizCodigos, matrizPasajes);
    cout << "------------------------------------------" << endl;

    
    fclose(archivoVuelos);
    fclose(archivoCompradores);

    return 0;
}

void CargaDeDatos(FILE* f, vuelo v[], int& tam)
{
    int codigo, pasajesDisponibles;

    cout << "Elemento " << tam << ": " << endl;
    cout << "    Código de vuelo: ";
    cin >> codigo;

    while(codigo >= 0)
    {
        v[tam].codigoVuelo = codigo;

        cout << "    Pasajes disponibles: ";
        cin >> v[tam].pasajesDisponibles;
        tam++;

        cout << "Elemento " << tam << ": " << endl;
        cout << "    Código de vuelo: ";
        cin >> codigo;
    }
    fwrite(v, sizeof(vuelo), tam, f);

    return;
}

void CargaDeDatos(FILE* f, comprador c[], int& tam)
{
    int codigo;
    
    cout << "Elemento: " << tam << endl; 
    cout << "    Codigo de vuelo: ";
    cin >> codigo;

    while(codigo >= 0)
    {
        c[tam].codigoVuelo = codigo;

        cout << "    Pasajes a comprar: ";
        cin >> c[tam].pasajesSolicitados;

        cout << "    Apellido y Nombre: (sin espacios)";
        cin >> c[tam].apellidoNombre;

        cout << "    DNI: ";
        cin >> c[tam].DNI;
        tam++;

        cout << "Elemento: " << tam << endl;
        cout << "    Código de vuelo: ";
        cin >> codigo;
    }
    fwrite(c, sizeof(comprador), tam, f);

    return;
}

void LecturaDeDatos(FILE* f, vuelo v[], int& tam)
{
    fseek(f, 0, SEEK_END);
    tam = ftell(f) / sizeof(vuelo);

    fseek(f, 0, SEEK_SET);
    fread(v, sizeof(vuelo), tam, f);
    fseek(f, 0, SEEK_SET);

    return;
}

void LecturaDeDatos(FILE* f, comprador c[], int& tam)
{
    fseek(f, 0, SEEK_END);
    tam = ftell(f) / sizeof(comprador);

    fseek(f, 0, SEEK_SET);
    fread(c, sizeof(comprador), tam, f);
    fseek(f, 0, SEEK_SET);

    return;
}

void PrepararPUP(vuelo v[], int vTam, short int mCodigos[], int mPasajes[][2])
{
    int codigo;
    for(int i = 0; i < vTam; i++)
    {
        codigo = v[i].codigoVuelo;
        mCodigos[codigo] = i;
        mPasajes[i][0] = v[i].pasajesDisponibles;
    }
    return;
}

void AnalizarSolicitudes(comprador compradores[], int compradoresTam,
    comprador ventas[], int& ventasTam, short int mCodigos[], int mPasajes[][2])
{
    int codigo, pasajesSolicitados, claveMatriz, pasajesDisponibles;

    for(int i = 0; i < compradoresTam; i++)
    {
        codigo = compradores[i].codigoVuelo;
        pasajesSolicitados = compradores[i].pasajesSolicitados;
        claveMatriz = mCodigos[codigo];
        pasajesDisponibles = mPasajes[claveMatriz][0];
        if(pasajesSolicitados <= pasajesDisponibles)
        {
            ventas[ventasTam] = compradores[i];
            ventasTam++;

            mPasajes[claveMatriz][0] -= pasajesSolicitados; // Pasajes libres
        }
        else 
        {
            mPasajes[claveMatriz][1] += pasajesSolicitados; // Pasajes no vendidos
        }
        
    }
    return;
}

void MostrarVentas(comprador ventas[], int ventasTam)
{
    for(int i = 0; i < ventasTam; i++)
    {
        cout << "DNI      - APELLIDO Y NOMBRE   - CANTIDAD DE PASAJES -  CÓDIGO DE VUELO" << endl;
        cout << ventas[i].DNI << "          " << ventas[i].apellidoNombre << "             " << ventas[i].pasajesSolicitados
             << "                       " << ventas[i].codigoVuelo << endl << endl;

    }
    return;
}

void MostrarVuelos(vuelo vuelos[], int vuelosTam, short int mCodigos[], int mPasajes[][2])
{
    int codigo, indice, pasajesLibres, pasajesNoVendidos;
    for(int i = 0; i< vuelosTam; i++)
    {
        codigo = vuelos[i].codigoVuelo;
        indice = mCodigos[codigo];
        pasajesLibres = mPasajes[indice][0];
        pasajesNoVendidos = mPasajes[indice][1];

        cout << "CÓDIGO DE VUELO - PASAJES LIBRES - PASAJES NO VENDIDOS" << endl;
        cout << codigo << "                        " << pasajesLibres << "               " << pasajesNoVendidos << endl << endl;
    }
    
    return;
}
/*
    TODO 
    Crear las funciones de carga y lectura de archivo -> Facil
    Crear la funcion de mostrar ventas -> Iterar vector ventas, utilizando las dos matrices de codigos y pasajes
    Crear la funcion de mostrar vuelos -> Iterar vector vuelos, utilizando las dos matrices de codigos y pasajes
    Ver como aplicar la teoría de Corte de Control a este caso, repasar lo necesario.
*/