/*
    Dado un valor N (<50), y una matriz MAT[NxN] que contiene valores enteros.
    Se pide:
    a) Leerla por fila
    b) Informarla por columna
    c) Informar la sumatoria de sus elementos y el valor promedio
    d) Informar el máximo elemento y su ubicación (fila y columna)
    e) Informar el mínimo de cada fila y el máximo de cada columna
    f) Informar cuantos elementos positivos hay en la diagonal principal y cuantos
    negativos en la diagonal secundaria
*/

#include <iostream>

using namespace std;

void CargarDatos(int[][50], int &);

void LeerPorFila(int[][50], int);
void LeerPorColumna(int[][50], int);
void SumatoriaYPromedio(int[][50], int);
void MaximoElemento(int[][50], int);
void MaximosYMinimos(int[][50], int);
void SignosDeDiagonales(int[][50], int);

int main()
{
    int MAT[50][50] = {0};
    int tamañoLogico;

    CargarDatos(MAT, tamañoLogico);

    LeerPorFila(MAT, tamañoLogico);

    LeerPorColumna(MAT, tamañoLogico);

    SumatoriaYPromedio(MAT, tamañoLogico);

    MaximoElemento(MAT, tamañoLogico);

    MaximosYMinimos(MAT, tamañoLogico);

    SignosDeDiagonales(MAT, tamañoLogico);

    return 0;
}

void CargarDatos(int mat[][50], int &tam)
{
    cout << "Ingrese el tamaño de la matriz cuadrada: ";
    cin >> tam;

    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            cout << "[" << i << "]"
                 << "[" << j << "]"
                 << ": ";
            cin >> mat[i][j];
        }
    }
}

void LeerPorFila(int mat[][50], int tam)
{
    cout << endl << "La matriz posee las siguientes filas:" << endl;
    for (int i = 0; i < tam; i++)
    {
        cout << "Fila " << i << ":   ";
        for (int j = 0; j < tam; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return;
}

void LeerPorColumna(int mat[][50], int tam)
{
    cout << "La matriz posee las siguientes columnas:" << endl;
    for (int i = 0; i < tam; i++)
    {
        cout << "Columna " << i << ":   ";
        for (int j = 0; j < tam; j++)
        {
            cout << mat[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return;
}

void SumatoriaYPromedio(int mat[][50], int tam)
{
    float sum = 0;
    float prom = 0;
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
        {
            sum += mat[i][j];
        }
    }

    prom = sum / (tam * tam);
    cout << "La sumatoria de los elementos es: " << int(sum) << endl;
    cout << "El promedio de los elementos es: " << prom << endl << endl;

    return;
}
void MaximoElemento(int mat[][50], int tam)
{
    int max = 0;
    int posX = 0;
    int posY = 0;

    for(int i = 0; i < tam; i++)
    {
        for(int j = 0; j < tam; j++)
        {
            if(max < mat[i][j])
            {
                max = mat[i][j];
                posX = i;
                posY = j;
            }
        }
    }

    cout << "El maximo elemento es " << max << " y se encuentra en la posición ["
         << posX << "][" << posY << "]" << endl << endl;

    return;
}

void MaximosYMinimos(int mat[][50], int tam)
{
    int minimos[50] = {0}; // Por fila
    int maximos[50] = {0}; // Por columna
    for(int i = 0; i < tam; i++)
    {
        for(int j = 0; j < tam; j++)
        {
            if(j == 0)
            {
                minimos[i] = mat[i][j];
            }
            if(minimos[i] > mat[i][j])
            {
                minimos[i] = mat[i][j];
            }

            if(maximos[i] < mat[j][i])
            {
                maximos[i] = mat[j][i];
            }
        }
        cout << "Min Fila " << i << ": " << minimos[i] << "  -  Max Col " << i <<": " << maximos[i] << endl;
    }
    cout << endl;
    return;
}

void SignosDeDiagonales(int mat[][50], int tam)
{
    int positivosDiagP = 0;
    int negativosDiagS = 0;

    for(int i = 0; i < tam; i++)
    {
        if(mat[i][i] > 0)
        {
            positivosDiagP++;
        }
        if(mat[i][tam - (i + 1)] < 0)
        {
            negativosDiagS++;
        }
    }
    cout << "Hay " << positivosDiagP << " elementos positivos en la diagonal principal" << endl;
    cout << "Hay " << negativosDiagS << " elementos negativos en la diagonal secundaria" << endl;
    return;
}