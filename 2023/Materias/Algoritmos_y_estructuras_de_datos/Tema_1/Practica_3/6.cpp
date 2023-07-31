/*
    Dado un archivo PRECIOS (desordenado) con los precios de cada articulo, donde cada 
    registro contiene: 
    a. Nro. de articulo (5 digitos) 
    b. Descripcion del articulo (19 c) 
    c. Precio por unidad (real) 
    d. Cantidad en stock (5 e) 
    e. Nro. de proveedor (4 digitos)
*/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

struct articulo
{
    int numero;
    char descripcion[19+1];
    float precio;
    int stock;
    int proveedor;
};

int main()
{
    FILE* file = fopen("archivos/ej6_PRECIOS.bin", "wb");
    
    articulo art;
    int artSize = sizeof(articulo);
    cout << "Tamaño de registro: " << artSize << endl;

    cout << "CARGA DE DATOS:" << endl << endl;

    cout << "Articulo:" << endl;
    cout << "    Nro de articulo: ";
    cin >> art.numero;

    while(art.numero > 0)
    {
        cout << "    Descripción: ";
        cin >> art.descripcion;

        cout << "    Precio: ";
        cin >> art.precio;

        cout << "    Cantidad en stock: ";
        cin >> art.stock;

        cout << "    Nro de proveedor: ";
        cin >> art.proveedor;

        fwrite(&art, artSize, 1, file);

        cout << endl << "Articulo:" << endl;
        cout << "    Nro de articulo: ";
        cin >> art.numero;
    }

    cout << "FIN DE LA CARGA DE DATOS";
    fclose(file);

    return 0;
}