#include<iostream>
#include<cstring>

using namespace std;

int main()
{
    char nombre[16] = "";
    int fecha_de_nacimiento = 0;
    
    float edad = 0;
    int año = 0;
    int mes = 0;
    int dia = 0;

    float mayorEdad = 0;
    char nombreMayor[16] = "";

    float menorEdad = 0;
    char nombreMenor[16] = "";

    bool primeraIteracion = true;

    cout << "Ingrese su nombre: ";
    cin >> nombre;
    while(strcmp(nombre, "FIN") != 0)
    {
        cout << "Ingrese su fecha de nacimiento: ";
        cin >> fecha_de_nacimiento;

        año = 2023-fecha_de_nacimiento/10000;
        mes = (fecha_de_nacimiento%10000) / 100;
        dia = (fecha_de_nacimiento%10000) % 100;

        edad = año + mes / 12.0 + dia / 365.0;
    
        if (edad > mayorEdad)
        {
            mayorEdad = edad;
            strcpy(nombreMayor, nombre);
        }
        
        if (edad < menorEdad || primeraIteracion)
        {
            menorEdad = edad;
            strcpy(nombreMenor, nombre);
            primeraIteracion = false;
        }

        
        cout << endl << "Ingrese su nombre: ";
        cin >> nombre;
    }

    cout << endl << "Persona de mayor edad: ";
    for(int i = 0; nombreMayor[i] != '\0'; i++)
    {
        cout << nombreMayor[i]; 
    }
    
    cout << endl << "Persona de menor edad: ";
    for(int i = 0; nombreMenor[i] != '\0'; i++)
    {
        cout << nombreMenor[i]; 
    }
    return 0;
    
}