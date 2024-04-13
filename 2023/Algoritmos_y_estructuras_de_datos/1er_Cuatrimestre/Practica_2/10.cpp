/*
    Genere e informe una matriz MUL[10x10] con las tablas de multiplicar. 
*/
#include <iostream>

using namespace std;



int main()
{
    int MUL[10][10];

    for(int i = 1; i <= 10; i++)
    {
        for(int j = 1; j <= 10; j++)
        {
            MUL[i-1][j] = i*j;
            cout << MUL[i-1][j] << " ";
        }
        cout << endl;
    }

    return 0;
}