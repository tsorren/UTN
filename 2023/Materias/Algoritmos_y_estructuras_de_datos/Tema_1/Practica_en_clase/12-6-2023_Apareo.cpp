#include<iostream>

using namespace std;

void FuncConstante(const int[]);
void Apareo(int[], int[], int, int, int[], int, int&);
void MostrarVector(int[], int);

int main()
{
    const int N = 4;
    const int M = 5;
    
    int vectorA[N] = {2, 8, 10, 12};
    int vectorB[M] = {1, 9, 19, 23, 31};
    int vectorC[N+M];

    int tamañoLogicoH = 0;

    Apareo(vectorA, vectorB, N, M, vectorC, N+M, tamañoLogicoH);
    MostrarVector(vectorC, tamañoLogicoH);


    return 0;
}

void FuncConstante(const int arr[])
{
    // no se puede modificar el array
    return;
}

void Apareo(int A[], int B[], int N, int M, int C[], int H, int& k)
{
    int i = 0;
    int j = 0;

    while((i<N) && (j<M))
    {
        // CRITERIO DE ORDENAMIENTO: CRECIENTE, admite valores repetidos
        if(A[i] < B[j])
        {
            C[k] = A[i];
            i++;
            k++;
        }
        else
        {
            // Ya no admite valores repetidos. Se toma 1 de los 2 y se avanza EN LOS DOS
            if(A[i] == B[j])
            {
                C[k] = A[i];
                i++;
                j++;
                k++;
            }
            else
            {
                C[k] = B[j];
                j++;
                k++;
            }
        }
    }

    // Procesamiento de valores restantes
    
    while(i<N)
    {
        C[k] = A[i];
        i++;
        k++;
    }
    
    while(j<M)
    {
        C[k] = B[j];
        j++;
        k++;
    }
    
    return;
}

void MostrarVector(int vector[], int N)
{
    int i;

    for(i = 0; i < N; i++)
    {
        cout << vector[i] << endl;
    }
    cout << endl;
}

