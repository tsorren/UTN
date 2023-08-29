/*
    Una fábrica de calzados elabora 7 modelos en 5 colores diferentes. Esta fábrica tiene 
    registradas las ventas realizadas por cada modelo y por cada color en un archivo de ventas, 
    conteniendo : 
    a. Nro. modelo (1..7)
    b. Color (‘A’..’E’) // Azul, Marrón, Blanco, Negro, Escarlata ('A', 'M', 'B', 'N', 'E')
    c. Cantidad vendida (3 dig.). 
    Se pide emitir un listado que informe los totales de cada uno de los modelos y por cada  // Corte de control
    uno de los colores, como asi también los totales por cada modelo, los totales por cada 
    color y el total general
*/

#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

using namespace std;

struct venta
{
    int modelo;
    char color;
    int cantVendida;
};

void CargarArchivo(FILE*, int);

int CalcularTamaño(FILE*, int);

void LeerArchivo(FILE*, venta[], int, int);
void Burbujeo(venta[], int);

int ConseguirIndiceColor(char);
char ConseguirColor(int);

void InformarTotalesModeloColor(venta[], int, int [][5]);
void InformarTotalesModelo(int [][5]);
void InformarTotalesColor(int [][5]);
void InformarTotal(int [][5]);

int main()
{
    FILE* ventasFile = fopen("archivos/ej11_ventas.dat", "rb+");
    int ventaSize = sizeof(venta);

    // CargarArchivo(ventasFile, ventaSize);

    int ventasTam = CalcularTamaño(ventasFile, ventaSize);
    venta ventas[ventasTam];

    LeerArchivo(ventasFile, ventas, ventasTam, ventaSize);
    Burbujeo(ventas, ventasTam);

    int cantidades[7][5] = {0};

    InformarTotalesModeloColor(ventas, ventasTam, cantidades);
    InformarTotalesModelo(cantidades);
    InformarTotalesColor(cantidades);
    InformarTotal(cantidades);

    fclose(ventasFile);
    
    return 0;
}

void CargarArchivo(FILE* f, int size)
{
    venta vActual;

    fseek(f, 0, SEEK_SET);

    cout << "CARGA DE ARCHIVO:" << endl;
    for(vActual.modelo = 1; vActual.modelo < 8; vActual.modelo++)
    {
        cout << "  Modelo: " << vActual.modelo << endl;
        for(int i = 0; i < 5; i++)
        {
            vActual.color = ConseguirColor(i);
            cout << "    Color: " << vActual.color << endl;
            cout << "      Cantidad Vendida: ";
            cin >> vActual.cantVendida;
            cout << endl;
            fwrite(&vActual, size, 1, f);
        }
        cout << endl;
    }
    fseek(f, 0, SEEK_SET);
}

int CalcularTamaño(FILE* f, int size)
{
    fseek(f, 0, SEEK_END);
    int registros = ftell(f)/size;
    fseek(f, 0, SEEK_SET);

    return registros;
}

void LeerArchivo(FILE* f, venta v[], int vTam, int size)
{
    fseek(f, 0, SEEK_SET);
    fread(v, size, vTam, f);
    fseek(f, 0, SEEK_SET);

    return;
}

void Burbujeo(venta v[], int vTam)
{
    int i, j;
    venta aux;

    for(i = 1; i < vTam; i++)
    {
        for(j = 1; j <= vTam - i; j++)
        {
            if((v[j-1].modelo > v[j].modelo) ||
                (v[j-1].modelo == v[j].modelo && v[j-1].color > v[j].color))
            {
                aux = v[j-1];
                v[j-1] = v[j];
                v[j] = aux;
            }
        }
    }

    return;
}

char ConseguirColor(int i)
{
    switch(i)    // Azul, Marrón, Blanco, Negro, Escarlata ('A', 'M', 'B', 'N', 'E')
    {
        case 0:
            return 'A';

        case 1:
            return 'M';

        case 2:
            return 'B';
        
        case 3:
            return 'N';
        
        case 4:
            return 'E';
            
        default:            
            return ' ';
    }
}

int ConseguirIndiceColor(char c)
{
    switch(c)    // Azul, Marrón, Blanco, Negro, Escarlata ('A', 'M', 'B', 'N', 'E')
    {
        case 'A':
            return 0;

        case 'M':
            return 1;

        case 'B':
            return 2;
        
        case 'N':
            return 3;
        
        case 'E':
            return 4;
            
        default:            
            return -1;
    }
}

void InformarTotalesModeloColor(venta v[], int vTam, int cantidades[][5]) // Corte de control
{
    int i = 0;
    int modeloActual;
    char colorActual;
    int indiceModelo;
    int indiceColor;
    cout << "VENTAS POR MODELO Y COLOR:" << endl;
    while(i < vTam)
    {
        modeloActual = v[i].modelo;
        indiceModelo = modeloActual - 1;
        cout << "  Modelo " << modeloActual << ":" << endl;
        while(i < vTam && modeloActual == v[i].modelo)
        {
            colorActual = v[i].color;
            indiceColor = ConseguirIndiceColor(colorActual);
            while(i < vTam && colorActual == v[i].color)
            {
                cantidades[indiceModelo][indiceColor] += v[i].cantVendida;
                i++;
            }
            cout << "    Color " << colorActual << ": " << cantidades[indiceModelo][indiceColor] << endl;
        }
        cout << endl << endl;
    }
    return;
}

void InformarTotalesModelo(int cantidades[][5])
{
    int cantModelo;
    cout << endl << "VENTAS POR MODELO:" << endl;
    for(int i = 0; i < 7; i++)
    {
        cantModelo = 0;
        for(int j = 0; j < 5; j++)
        {
            cantModelo += cantidades[i][j];
        }
        cout << "  Modelo " << i + 1 << ": " << cantModelo << endl << endl;
    }
    return;
}

void InformarTotalesColor(int cantidades[][5])
{
    int i = 0;
    char colorActual;

    int cantColor;
    cout << endl << "VENTAS POR COLOR:" << endl;
    for(int i = 0; i < 5; i++)
    {
        cantColor = 0;
        colorActual = ConseguirColor(i);
        for(int j = 0; j < 7; j++)
        {
            cantColor += cantidades[j][i];
        }
        cout << "  Color \'" << colorActual << "\': " << cantColor << endl << endl;
    }
    return;
}

void InformarTotal(int cantidades[][5])
{
    int cantTotal = 0;
    cout << "VENTAS TOTALES: ";
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            cantTotal += cantidades[i][j];
        }
    }
    cout << cantTotal << endl;
    return;
}