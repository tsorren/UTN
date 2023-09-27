//1h 43m -> 2h 14m
//11:05 -> 11:35
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct electrodomestico
{
    char codigoElectrodomestico[6 + 1];
    char nombreElectrodomestico[250 + 1];
    float precioUnitario;
};

struct venta
{
    char codigoElectrodomestico[6 + 1]; 
    int diaDelMes; // valores entre 1 y 31  
    int cantidadVendida; 
    int dniCliente; 
    char nombreCliente[100+1];
};

//1) tipos de datos a utilizar (matriz y lista de clientes de cada día-electrodoméstico)
struct regNodo
{
    int dniCliente;
    char nombreCliente[100+1];
};

struct nodo
{
    regNodo info;
    nodo* sgte;
};

struct regMatriz
{
    int cantidadVendida;
    nodo* listaClientes;
};

/*
    2)
    Desarrolar int obtenerPosFilaEnMatriz(int diaDelMes)
    int obtenerPosColumnaEnMatriz(Electrodomestico electrodomesticos[], char codigoElectrodomestico[6 + 1]
*/
int BusquedaBinaria(electrodomestico[], int, char[]);
int obtenerPosFilaEnMatriz(int diaDelMes)
{
    return diaDelMes-1;
}
int obtenerPosColumnaEnMatriz(electrodomestico electrodomesticos[], char codigoElectrodomestico[])
{
    return BusquedaBinaria(electrodomesticos, 2500, codigoElectrodomestico);
}

/*
    3)
    Desarrolle el procedimiento cargarMatriz que debe cumplir con lo siguiente:
    - Recibe 3 parámetros: el archivo de ventas ya abierto, el array de electrodomésticos y la matriz (cada una de sus celdas ya se encuentra inicializada: cantidad vendida en 0 y lista de clientes en NULL).
    - Se debe leer secuencialmente el archivo de ventas.
*/
nodo* InsertarOrdenado(nodo* &, regNodo);

void cargarMatriz(FILE* f, electrodomestico vec[], regMatriz m[][2500])
{
    fseek(f, 0, SEEK_SET);
    venta reg;
    int regSize = sizeof(venta);
    while(fread(&reg, regSize, 1, f))
    {
        int x = obtenerPosFilaEnMatriz(reg.diaDelMes);
        int y = obtenerPosColumnaEnMatriz(vec, reg.codigoElectrodomestico);

        m[x][y].cantidadVendida += reg.cantidadVendida;
        
        regNodo aux;
        aux.dniCliente = reg.dniCliente;
        strcpy(aux.nombreCliente, reg.nombreCliente);

        InsertarOrdenado(m[x][y].listaClientes, aux);
    }
    return;
}

/*
    4)
    Desarrolle el procedimiento mostrarClientes
    que recibe por parámetro la matriz (luego de ser cargada en el punto 3),
    un número de fila y un número de columna, y muestra por pantalla, para esa fila-columna,
    la cantidad de ventas realizadas y todos los DNI de clientes que realizaron las compras.
    La lista de clientes NO debe ser destruida.
*/

void mostrarClientes(regMatriz m[][2500], int fila, int columna)
{
    int cant = m[fila][columna].cantidadVendida;
    nodo* aux = m[fila][columna].listaClientes;

    cout << "Matriz en [" << fila << "][" << columna << "]:" << endl;
    cout << "    Cantidad de ventas realizadas: " << cant << endl;

    cout << "    Clientes que realizaron las compras:" << endl;
    while(aux != NULL)
    {
        cout << "        DNI: " << aux->info.dniCliente << endl;
        aux = aux->sgte;
    }
    cout << endl;
    return;
}