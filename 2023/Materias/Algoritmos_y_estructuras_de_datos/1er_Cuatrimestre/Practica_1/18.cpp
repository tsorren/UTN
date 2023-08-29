/*
Desarrollar la función
string Tendencia(int A, int B)que dados dos valores A y B, retorne una cadena de
acuerdo al siguiente cuadro:

    B - A < 0  Decreciente
    B-A < 5% de A Leve ascenso
    B - A < 2% de A Estable
    Resto En ascenso

*/

#include <iostream>
#include <cstring>

using namespace std;

void Tendencia(int, int, char[]);

int main()
{
    int a, b;
    char texto[20+1];

    cout << "Ingrese dos valores: " << endl;
    cin >> a;
    cin >> b;

    Tendencia(a, b, texto);
    cout << texto;

    return 0;
}
// Pasa el vector de caracteres como argumento, 
//luego strcpy le asigna el texto deseado según la condición que se cumpla
void Tendencia(int A, int B, char text[])
{
    if ((B - A) < 0)
    {
        strcpy(text, "Decreciente");
    }

    else if ((B - A) < (A/100)*2)
    {
        strcpy(text, "Estable");
    }
    
    else if ((B - A) < (A/100)*5)
    {
        strcpy(text, "Leve Ascenso");
    }
    else
    {
        strcpy(text, "En ascenso");
    }

    return;
}