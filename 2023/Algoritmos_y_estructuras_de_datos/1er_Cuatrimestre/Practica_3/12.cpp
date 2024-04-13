/*
    Un negocio de ropa, vende sus artículos en distintos talles. Para realizar la facturación 
    dispone de los siguientes archivos: 
    Un archivo ‘Articulos.dat’, con los precios de cada artículo y talle que vende, con el 
    siguiente diseño de registro: 
    a. código de articulo (1..100) 
    b. talle (1..5) 
    c. precio (real) 

    También se dispone de un conjunto de ventas a facturar, que se ingresan por teclado con 
    los siguientes datos:
    código de artículo
    talle
    unidades (1 digito)
    Las ventas finalizan con un código de articulo negativo. 

    Desarrollar un algoritmo que: 
    a. informe el precio de la venta, considerando un descuento del 10% si las unidades 
    vendidas son superiores a tres, mas el 21% del IVA. 

    b. al final del proceso emita el siguiente listado, ordenado por articulo y talle ascendente: 
    Codigo de Articulo 999 // Articulo
    Talle Unidades Vendidas  // Ventas Por talle
    Total unidades vendidas artículo 9999999  //Ventas por articulo
    Total general de unidades vendidas 9999999 // Ventas totales
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

struct articulo
{
    int codigo;
    int talle;
    float precio;
};

struct venta
{
    int codigo;
    int talle;
    int unidades;
};

void CargarArchivo(FILE*, int);

int CalcularTamaño(FILE*, int);
void LeerArchivo(FILE*, articulo[], int);
void LeerArchivo(FILE*, venta[], int);


void CrearListadoPrecios(float[][5], articulo[], int);
venta IngresarVenta();
float CalcularPrecioVenta(venta);
void ProcesarVentas(articulo[], int, FILE*);

void OrdenarVentas(FILE*, venta[], int);
void CorteDeControl(venta[], int);

int main()
{
    FILE* artFile = fopen("archivos/ej12_articulos.dat", "rb+");
    FILE* venFile = fopen("archivos/ej12_ventas.dat", "wb+");
    
    //CargarArchivo(artFile, sizeof(articulo));
    int artTamaño = CalcularTamaño(artFile, sizeof(articulo));
         
    articulo articulos[artTamaño];
    LeerArchivo(artFile, articulos, artTamaño);
    
    ProcesarVentas(articulos, artTamaño, venFile);
    int venTamaño = CalcularTamaño(venFile, sizeof(venta));
    
    venta ventas[venTamaño];
    LeerArchivo(venFile, ventas, venTamaño);
    OrdenarVentas(venFile, ventas, venTamaño);
    CorteDeControl(ventas, venTamaño);
    
    fclose(artFile);
    fclose(venFile);

    return 0;
}

void CargarArchivo(FILE* f, int size)
{
    articulo art {1, 1, 0};
    float incremento;

    fseek(f, 0, SEEK_SET);
    
    cout << "Codigo: " << art.codigo << endl;
    cout << "  Talle: " << art.talle << endl;
    cout << "    Precio: ";
    cin>> art.precio;
    
    fwrite(&art, size, 1, f);   
    incremento = art.precio * 0.15;
    art.talle++;


    while(art.precio >= 0)
    {
        if(art.talle == 6)
        {
            art.codigo ++;
            art.talle = 1;
            cout << endl << "Codigo: " << art.codigo << endl;
        }
        cout << "  Talle: " << art.talle << endl;
        cout << "    Precio: ";
        

        if(art.talle == 1)
        {
            cin>> art.precio;
            incremento = art.precio * 0.15;
        }
        else 
        {
            art.precio += incremento;
            cout << art.precio << endl;
        }
        cout << endl;

        fwrite(&art, size, 1, f);        
        art.talle++;
    }

    return;
}

int CalcularTamaño(FILE* f, int size)
{
    fseek(f, 0, SEEK_END);
    int registros = ftell(f)/size;
    fseek(f, 0, SEEK_SET);

    return registros;
}

void LeerArchivo(FILE* f, articulo a[], int aTam)
{
    fseek(f, 0, SEEK_SET);
    fread(a, sizeof(articulo), aTam, f);
    fseek(f, 0, SEEK_SET);

    return;
}

void LeerArchivo(FILE* f, venta v[], int vTam)
{
    fseek(f, 0, SEEK_SET);
    fread(v, sizeof(venta), vTam, f);
    fseek(f, 0, SEEK_SET);

    return;
}

void CrearListadoPrecios(float precios[][5], articulo art[], int artTam)
{
    int codigo, talle;
    for(int i = 0; i < artTam; i++)
    {
        codigo = art[i].codigo;
        talle = art[i].talle;
        precios[codigo - 1][talle - 1] = art[i].precio;
    }
    return;
}

venta IngresarVenta()
{
    venta vActual = {0, 0, 0};
    cout << "NUEVA VENTA: " << endl;
    cout << "    Codigo de articulo: ";
    cin >> vActual.codigo;

    if(vActual.codigo >= 0)
    {
        cout << "    Talle: ";
        cin >> vActual.talle;

        cout << "    Unidades: ";
        cin >> vActual.unidades;
    }

    return vActual;
}

float CalcularPrecioVenta(venta v, float listadoPrecios[][5])
{
    float precio;
    int cod, talle, unid;
    cod = v.codigo;
    talle = v.talle;
    unid = v.unidades;

    precio = unid * listadoPrecios[cod - 1][talle - 1];

    if(unid > 3)
    {
        precio *= 0.9;
    }
    precio *= 1.21;

    return precio;
}

void ProcesarVentas(articulo art[], int artTam, FILE* venFile)
{
    venta vActual = IngresarVenta();
    int vSize = sizeof(venta);
    float precioVenta = 0;

    float listadoPrecios[100][5] = {0};
    CrearListadoPrecios(listadoPrecios, art, artTam);

    fseek(venFile, 0, SEEK_SET);


    while(vActual.codigo >= 0)
    {
        precioVenta = CalcularPrecioVenta(vActual, listadoPrecios);
        cout << "Precio de la venta: " << precioVenta << endl << endl;

        fwrite(&vActual, vSize, 1, venFile);

        vActual = IngresarVenta();
    }
    return;
}

void OrdenarVentas(FILE* f, venta v[], int vTam)
{
    fseek(f, 0, SEEK_SET);

    int i, j;
    venta aux;

    for(i = 1; i < vTam; i++)
    {
        for(j = 1; j <= vTam - i; j++)
        {
            if((v[j-1].codigo > v[j].codigo) ||
                (v[j-1].codigo == v[j].codigo && v[j-1].talle > v[j].talle))
            {
                aux = v[j-1];
                v[j-1] = v[j];
                v[j] = aux;
            }
        }
    }

    fwrite(v, sizeof(venta), vTam, f);
    return;
}
/*
    Codigo de Articulo 999 // Articulo
    Talle Unidades Vendidas  // Ventas Por talle
    Total unidades vendidas artículo 9999999  //Ventas por articulo
    Total general de unidades vendidas 9999999 // Ventas totales
*/
void CorteDeControl(venta v[], int vTam)
{
    int i = 0;
    int ventasTotales = 0, ventasTalle, ventasArticulo;

    venta vActual = v[i];

    cout << endl << "RESUMEN DE VENTAS:" << endl;

    while(i < vTam)
    {
        vActual = v[i];
        ventasArticulo = 0;
        ventasTalle = 0;
        cout << "    Codigo de Articulo: " << vActual.codigo << endl;
        while(i < vTam && vActual.codigo == v[i].codigo)
        {
            while(i < vTam && vActual.talle == v[i].talle)
            {
                ventasTalle += v[i].unidades;
                i++;
            }
            cout << "        Ventas de Talle " << vActual.talle << ": " << ventasTalle << endl;
            ventasArticulo += ventasTalle;
            vActual.talle = v[i].talle;
        }
        cout << "      Unidades vendidas: " << ventasArticulo << endl << endl;
        ventasTotales += ventasArticulo;
        vActual.codigo = v[i].codigo;
    }
    cout << "  VENTAS TOTALES: " << ventasTotales << endl;
    return;
}