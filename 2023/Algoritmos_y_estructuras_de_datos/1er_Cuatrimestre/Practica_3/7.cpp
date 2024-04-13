/*
    Desarrollar el programa que imprima el contenido del archivo ordenado por:
    1) Nro. de articulo creciente
    2) Descripcion del articulo (alfabetico creciente)
    3) Nro. de proveedor creciente y dentro del mismo por Nro. de articulo creciente
    4) Nro. de proveedor creciente y dentro del mismo por Nro. de articulo decreciente.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

struct articulo
{
    int numero;
    char descripcion[19+1];
    float precio;
    int stock;
    int proveedor; 
};

int CalcularTamaño(FILE*, int);

void ImprimirContenido(articulo[], int);

void BurbujeoArticulo(articulo[], int);
void BurbujeoDescripcion(articulo[], int);
void BurbujeoProveedorArtCreciente(articulo[], int);
void BurbujeoProveedorArtDecreciente(articulo[], int);

int main()
{
    int artSize = sizeof(articulo);
    FILE* file = fopen("archivos/ej6_PRECIOS.bin", "rb");
    const int tamañoVec = CalcularTamaño(file, artSize);

    articulo VEC[tamañoVec];
    fread(&VEC, artSize, tamañoVec, file);

    cout << "Vector original: " << endl;
    ImprimirContenido(VEC, tamañoVec);

    cout << "Vector ordenado por nro de articulo, creciente: " << endl;
    BurbujeoArticulo(VEC, tamañoVec);
    ImprimirContenido(VEC, tamañoVec);

    cout << "Vector ordenado por descripción, creciente: " << endl;
    BurbujeoDescripcion(VEC, tamañoVec);
    ImprimirContenido(VEC, tamañoVec);

    cout << "Vector ordenado por proveedor, creciente, y nro de articulo, creciente: " << endl;
    BurbujeoProveedorArtCreciente(VEC, tamañoVec);
    ImprimirContenido(VEC, tamañoVec);

    cout << "Vector ordenado por proveedor, creciente, y nro de articulo, decreciente: " << endl;
    BurbujeoProveedorArtDecreciente(VEC, tamañoVec);
    ImprimirContenido(VEC, tamañoVec);

    return 0;
}

int CalcularTamaño(FILE* f, int size)
{
    fseek(f, 0, SEEK_END);
    int desplazamiento = ftell(f);
    fseek(f, 0, SEEK_SET);

    return desplazamiento/size;

}

void ImprimirContenido(articulo vec[], int tamaño)
{
    cout << "-----------------------------------------" << endl;
    cout << "CONTENIDO DEL VECTOR: " << endl << endl;
    for(int i = 0; i < tamaño; i++)
    {
        cout << "Elemento " << i << ":" << endl;
        cout << "    Nro de artículo: " << vec[i].numero << endl;
        cout << "    Descripción: " << vec[i].descripcion << endl;
        cout << "    Precio: " << vec[i].precio << endl;
        cout << "    Cantidad en stock: " << vec[i].stock << endl;
        cout << "    Nro de proveedor: " << vec[i].proveedor << endl;
        cout << endl;

    }
    cout << "-----------------------------------------" << endl;
    return;
}

void BurbujeoArticulo(articulo vec[], int tamaño)
{
    int i, j;
    articulo aux;

    for(i = 1; i < tamaño; i++)
    {
        for(j = 1; j <= tamaño - i; j++)
        {
            if(vec[j-1].numero > vec[j].numero) // Criterio: Nro de Articulo creciente
            {
                aux = vec[j-1];
                vec[j-1] = vec[j];
                vec[j] = aux;
            }
        }
    }
    return;
}

void BurbujeoDescripcion(articulo vec[], int tamaño)
{
    int i, j;
    articulo aux;

    for(i = 1; i < tamaño; i++)
    {
        for(j = 1; j <= tamaño - i; j++)
        {
            if((strcmp(vec[j-1].descripcion, vec[j].descripcion) == 1)) // Alfabetico creciente
            {
                aux = vec[j-1];
                vec[j-1] = vec[j];
                vec[j] = aux;
            }
        }
    }
    return;
}

void BurbujeoProveedorArtCreciente(articulo vec[], int tamaño)
{
    int i, j;
    articulo aux;

    for(i = 1; i < tamaño; i++)
    {
        for(j = 1; j <= tamaño - i; j++)
        {
            if((vec[j-1].proveedor > vec[j].proveedor) || 
                ((vec[j-1].proveedor == vec[j].proveedor) && (vec[j-1].numero > vec[j].numero)))
            {
                aux = vec[j-1];
                vec[j-1] = vec[j];
                vec[j] = aux;
            }
        }
    }
    return;
}

void BurbujeoProveedorArtDecreciente(articulo vec[], int tamaño)
{
    int i, j;
    articulo aux;

    for(i = 1; i < tamaño; i++)
    {
        for(j = 1; j <= tamaño - i; j++)
        {
            if((vec[j-1].proveedor > vec[j].proveedor) || 
                (vec[j-1].proveedor == vec[j].proveedor) && (vec[j-1].numero < vec[j].numero))
            {
                aux = vec[j-1];
                vec[j-1] = vec[j];
                vec[j] = aux;
            }
        }
    }
    return;
}
