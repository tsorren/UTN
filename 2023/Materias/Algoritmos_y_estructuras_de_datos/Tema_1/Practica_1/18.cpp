#include <iostream>
#include <cstring>

using namespace std;

void Tendencia(int, int, char[]);

int main()
{
    int a, b;
    char texto[20] = {"text"};

    cout << "\nIngrese dos valores: ";
    cin >> a >> b;

    Tendencia(a, b, texto);
    cout << texto;

    return 0;
}
void Tendencia(int A, int B, char text[])
{
    //TODO finish function
    if ((B - A) < 0)
    {
        strcpy(text, "Decreciente");
    }
    return;
}