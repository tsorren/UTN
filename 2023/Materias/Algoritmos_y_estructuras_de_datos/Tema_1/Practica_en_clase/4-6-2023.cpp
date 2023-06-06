#include <iostream>

using namespace std;

int main()
{
    struct
    {
        char nombre[32+1];
        int edad;

    } perro;

    cin >> perro.nombre >> perro.edad;

    cout << perro.nombre << endl << perro.edad;

    return 0;
}