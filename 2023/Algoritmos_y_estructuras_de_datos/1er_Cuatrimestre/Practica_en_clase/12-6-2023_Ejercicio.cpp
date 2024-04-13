/*¨
Dado un vector de ventas historico(N) con :idProducto, cantidadVendida
ordenado por idProducto, y otro con las novedades(M): idProducto,
cantidadVendida. Generar
un tercer vector resultante con los datos actualizados


Tipo de ordenamiento: A decision del programador -> Decreciente
*/

#include <iostream>

using namespace std;

struct producto
{
    int idProducto;
    int cantidadVendida;
};

void CargaDeVector(producto[], int);
void MostrarVector(producto[], int);
void BurbujeoDecreciente(producto[], int);
void Apareo(producto[], producto[], int, int, producto[], int, int &);

int main()
{
    const int N = 6;
    const int M = 8;
    int H;

    producto ventasHistoricas[N]; // Vector ordenado decrecientemente
    producto ventasNovedades[M];  // Vector desordenado
    producto ventasActualizadas[N + M];

    cout << "Carga de Ventas Historicas: " << endl;
    CargaDeVector(ventasHistoricas, N);

    cout << "Carga de Ventas Novedades: " << endl;
    CargaDeVector(ventasNovedades, M);

    BurbujeoDecreciente(ventasNovedades, M);

    Apareo(ventasHistoricas, ventasNovedades, N, M, ventasActualizadas, N+M, H);

    cout << "Ventas Actualizadas: " << endl;
    MostrarVector(ventasActualizadas, H);

    return 0;
}

void CargaDeVector(producto vector[], int N)
{
    cout << "Cantidad de productos a cargar: " << N << endl
         << endl;
    int i;
    for (i = 0; i < N; i++)
    {
        cout << i + 1 << "°:" << endl << "ID del producto: ";
        cin >> vector[i].idProducto;
        cout << "Cantidad vendida: ";
        cin >> vector[i].cantidadVendida;
    }
    cout << endl;
}

void MostrarVector(producto vector[], int N)
{
    int i;

    for (i = 0; i < N; i++)
    {
        cout << "Ventas del producto " << vector[i].idProducto << ": " << vector[i].cantidadVendida << endl;;
    }
    cout << endl;
}

void BurbujeoDecreciente(producto vector[], int N)
{
    int i, j;
    producto aux;
    for(i = 1; i < N; i++)
    {
        for(j = 1; j <= N-i; j++)
        {
            if(vector[j-1].idProducto < vector[j].idProducto)
            {
                aux = vector[j-1];
                vector[j-1] = vector[j];
                vector[j] = aux;
            }
        }
    }

    return;
}

void Apareo(producto vectorA[], producto vectorB[], int N, int M, producto vectorC[], int, int &H)
{
    int i = 0;
    int j = 0;
    int k = 0;

    while ((i < N) && (j < M))
    {
        if (vectorA[i].idProducto > vectorB[j].idProducto)
        {
            vectorC[k] = vectorA[i];
            i++;
        }
        else
        {
            if (vectorA[i].idProducto == vectorB[j].idProducto)
            {
                vectorC[k] = {vectorA[i].idProducto, vectorA[i].cantidadVendida + vectorB[j].cantidadVendida};
                i++;
                j++;
            }
            else
            {
                vectorC[k] = vectorB[j];
                j++;
            }
        }
        k++;
    }

    while (i < N)
    {
        vectorC[k] = vectorA[i];
        i++;
        k++;
    }

    while (j < M)
    {
        vectorC[k] = vectorB[j];
        j++;
        k++;
    }

    H = k;

    return;
}