/*
    Calcular la velocidad (m/s) de los participantes de una carrera de 1500mts, dado el tiempo en segundos que le llevó a cada participante completarla y determinar el nombre del más veloz.
    Y si el tiempo fuera en minutos + segundos?   

    MRU

    x = X0 + V * (t - t0) -> x = V * t
    -> 1500 = V * t -> 1500/t = V

    Minutos y segundos -> seg = segundos + (60 * Minutos)
    
    Nombre del más veloz: Comparación entre velocidades, la mayor

    Algoritmo de comparación:
    Loop
    varialble máxima se compara con la velocidad[i], si es menor, se le asigna velocidad[i]

    MINUTOS Y SEGUNDOS:

*/

/* SOLUCION 1
#include<iostream>

using namespace std;

int main()
{
    char nombres[5][11] = {"Juancito", "Peppermint", "Puch", "Gerard", "Karl"};
    
    float tiempos[5], velocidades[5] = {0, 0, 0, 0 , 0};

    int partMasVeloz = 0;

    for(int i = 0; i < 5; i++)
    {
        int mins, segs = 0;
        
        cout << "Ingrese cuantos tiempo le llevó a " << nombres[i] << " en correr 1500 metros: " << endl;
        
        cout << "Minutos: ";
        cin >> mins;
        
        cout << "Segundos: ";
        cin >> segs;
        
        cout << endl;

        tiempos[i] = mins*60 + segs;
        velocidades[i] = 1500/tiempos[i];

        if(velocidades[partMasVeloz] < velocidades[i])
        {
            partMasVeloz = i;
        }
    }
    
    cout << "El participante más velóz fue " << nombres[partMasVeloz] << ", con una velocidad de " << velocidades[partMasVeloz] << " metros por segundo" << endl;
    

    return 0;
}

*/

// SOLUCION 2
#include<iostream>

using namespace std;

int main()
{
    char nombre[16+1];
    
    float tiempo = 0,
    float velocidad = 0;

    char nombreMasVeloz[16+1];
    float mayorVel = 0;

    int mins, segs = 0;

    int i, n;

    cout << "Ingrese la cantidad de participantes: ";
    cin >> n;

    for(i = 0; i < 5; i++)
    {
        cout << "Ingrese el nombre del Participante " << i + 1 << " : ";
        cin >> nombre;
        cout << "Ingrese cuantos segundos le llevó a " << nombre << " en correr 1500 metros: ";

        cout << "Minutos: ";
        cin >> mins;
        
        cout << "Segundos: ";
        cin >> segs;

        tiempo = mins*60 + segs;
        velocidad = 1500/tiempo;

        if(mayorVel < velocidad)
        {
            mayorVel = velocidad;
            strcpy(nombreMasVeloz, nombre);
        }
        cout << endl;

    }
    
    cout << "El participante más velóz fue " << nombreMasVeloz; // << ", con una velocidad de " << mayorVel << " metros por segundo" << endl;
    
    return 0;
}