/*
    Dado un numero N (<=50) y un conjunto de Nombres y Fechas de nacimientos 
    (AAAAMMDD), 
    informar el conjunto: 
    • ordenado por nombre 
    • ordenado por fecha y nombre 
    • ordenado por nombre y fecha
*/

#include <iostream>
#include <cstring>

using namespace std;

struct registro
{
    char nombre[16+1];
    char fecha[8+1];
};

void CargaDeVector(registro[], int&);

void BurbujeoNombre(registro[], const int);

void BurbujeoFechaYNombre(registro[], const int);

void BurbujeoNombreYFecha(registro[], const int);

void MostrarVector(registro[], const int);

int main()
{
    registro reg[50];
    int tamañoLogico;
    CargaDeVector(reg, tamañoLogico);

    cout << "Conjunto ordenado por nombre, alfabeticamente: " << endl;
    BurbujeoNombre(reg, tamañoLogico);
    MostrarVector(reg, tamañoLogico);

    cout << "Conjunto ordenado por Fecha y Nombre, alfabeticamente" << endl;
    BurbujeoFechaYNombre(reg, tamañoLogico);
    MostrarVector(reg, tamañoLogico);

    cout << "Conjunto ordenado por Nombre y Fecha, alfabeticamente" << endl;
    BurbujeoNombreYFecha(reg, tamañoLogico);
    MostrarVector(reg, tamañoLogico);

    return 0;
}

void CargaDeVector(registro reg[], int& tam)
{
    cout << "Ingrese el tamaño del conjunto: ";
    cin >> tam;

    for(int i = 0; i < tam; i++)
    {
        cout << "Elemento Nro " << i << ":" << endl; 
        cout << "  Ingrese el nombre: ";
        cin >> reg[i].nombre;
        cout << "  Ingrese la fecha (AAAAMMDD): ";
        cin >> reg[i].fecha;
        cout << endl;
    }
    return;
}

void BurbujeoNombre(registro reg[], int tam)
{
    int i, j;
    registro aux;


    for(i = 1; i < tam; i++)
    {
        for(j = 1; j <= tam - i; j++)
        {
            if(strcmp(reg[j-1].nombre, reg[j].nombre) == 1)
            {
                aux = reg[j-1];
                reg[j-1] = reg[j];
                reg[j] = aux;
            }
        }
    }
    return;
}

void BurbujeoFechaYNombre(registro reg[], int tam)
{
    int i, j;
    int comparacionFecha;
    registro aux;

    for(i = 1; i < tam; i++)
    {
        for(j = 1; j <= tam - i; j++)
        {
            comparacionFecha = strcmp(reg[j-1].fecha, reg[j].fecha);
            if((comparacionFecha == 1 ) || (comparacionFecha == 0 && strcmp(reg[j-1].nombre, reg[j].nombre) == 1))
            {
                aux = reg[j-1];
                reg[j-1] = reg[j];
                reg[j] = aux;
            }            
        }
    }
    return;
}

void BurbujeoNombreYFecha(registro reg[], int tam)
{
    int i, j;
    int comparacionNombre;
    registro aux;

    for(i = 1; i < tam; i++)
    {
        for(j = 1; j <= tam - i; j++)
        {
            comparacionNombre = strcmp(reg[j-1].nombre, reg[j].nombre);
            if((comparacionNombre == 1) || (comparacionNombre == 0 && strcmp(reg[j-1].fecha, reg[j].fecha) == 1))
            {
                aux = reg[j-1];
                reg[j-1] = reg[j];
                reg[j] = aux;
            }
        }
    }
    return;
}

void MostrarVector(registro reg[], int tam)
{
    for(int i = 0; i < tam; i++)
    {
        cout << "Elemento " << i << ": " << endl;
        cout << "   " << reg[i].nombre << endl << "   " << reg[i].fecha << endl;
    }
    cout << endl;
    return;
}