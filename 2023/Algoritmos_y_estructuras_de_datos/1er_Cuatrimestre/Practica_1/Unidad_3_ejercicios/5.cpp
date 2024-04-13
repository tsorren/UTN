/*
    Escriba un programa que reciba un numero que represente el radio de un círculo e imprima
    el diámetro, circunferencia y área

    recibir numero real
    imprimir: 
        Diametro: 2n
        Circunferencia: 2n * pi
        Área: pi * n * n
*/

#include<iostream>

using namespace std;

int main()
{
    const float PI = 3.14159265;

    float radio = 0;

    cout << "Ingrese el radio del circulo: ";
    cin >> radio;

    float diametro = 2 * radio;
    float circunferencia = diametro * PI;
    float area = radio * radio * PI;

    cout << "Diametro: " << diametro << endl;
    cout << "Circunferencia: " << circunferencia << endl;
    cout << "Area: " << area << endl;
    
    return 0;
}
