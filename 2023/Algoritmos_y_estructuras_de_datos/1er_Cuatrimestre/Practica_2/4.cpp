/*
    Dado un número N (<25), y dos vectores A y B de N elementos que contenga 
    valores reales 
    a) genere e informe un tercer vector C intercalando los valores de posición impar de A 
    y los valores de posición par de B. 
    b) genere e informe un tercer vector D donde cada elemento contenga un valor cero si 
    los elementos de una misma posición de A y B son iguales, o un valor uno si no lo 
    son. 
*/
#include <iostream>

using namespace std;

void CargaDeVector(float[], const int);

void ApareoIntercalado(const float[], const float[], const int, float[], int&);
void VectorIgualdad(const float[], const float[], const int, int[]);

void InformarVector(float[], int);
void InformarVector(int[], int);

int main()
{
    const int N = 25;
    int tamañoLogico;
    cout << "Ingrese el tamaño del Vector (<25): ";
    cin >> tamañoLogico;

    float vecA[N];
    float vecB[N];

    int tamañoLogicoApareo;
    float vecC[N+N];    //Intercalado
    int vecD[N];      //Igualdad

    CargaDeVector(vecA, tamañoLogico);
    CargaDeVector(vecB, tamañoLogico);

    ApareoIntercalado(vecA, vecB, tamañoLogico, vecC, tamañoLogicoApareo);
    cout << "Vector Intercalado:" << endl;
    InformarVector(vecC, tamañoLogicoApareo);
    
    VectorIgualdad(vecA, vecB, tamañoLogico, vecD);
    cout << "Vector Igualdad:" << endl;
    InformarVector(vecD, tamañoLogico);
    
    return 0;
}

void CargaDeVector(float vec[], const int t)
{
    for(int i = 0; i < t; i++)
    {
        cout << "Ingrese el valor para la posición " << i << ": ";
        cin >> vec[i];
    }
    cout << endl;
    return;
}

void ApareoIntercalado(const float vA[], const float vB[], const int tam, float vC[], int& tamC)
{
    int i = 1;
    int j = 0;
    int k = 0;
    while(i < tam || j < tam)
    {
        if(k % 2 == 0 && i < tam)
        {
            vC[k] = vA[i];
            i += 2;
        }
        else if(j < tam)
        {
            vC[k] = vB[j];
            j += 2;
        }
        k++;
    }
    tamC = k;
    return;
}

void InformarVector(float vec[], const int t)
{
    for(int i = 0; i < t; i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
    return;
}
void InformarVector(int vec[], const int t)
{
    for(int i = 0; i < t; i++)
    {
        cout << vec[i] << " ";
    }
    return;
}

void VectorIgualdad(const float vA[], const float vB[], const int tam, int vD[])
{
    for(int i = 0; i < tam; i++)
    {
        if(vA[i] == vB[i])
        {
            vD[i] = 0;
        }
        else
        {
            vD[i] = 1;
        }
    }
    return;
}