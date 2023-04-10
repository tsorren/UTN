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
*/

#include<iostream>

using namespace std;

int main()
{
    char nombres[5][11] = {"Juancito", "Peppermint", "Puch", "Gerard", "Karl"};
    
    float tiempos[5], velocidades[5] = {0, 0, 0, 0 , 0};

    int partMasVeloz = 0;

    for(int i = 0; i < 5; i++)
    {
        cout << "Ingrese cuantos segundos le llevó a " << nombres[i] << " en correr 1500 metros: ";
        cin >> tiempos[i];
        velocidades[i] = 1500/tiempos[i];

        if(velocidades[partMasVeloz] < velocidades[i])
        {
            partMasVeloz = i;
        }
        cout << endl;

    }
    
    cout << "El participante más velóz fue " << nombres[partMasVeloz] << ", con una velocidad de " << velocidades[partMasVeloz] << " metros por segundo" << endl;
    

    return 0;
}


