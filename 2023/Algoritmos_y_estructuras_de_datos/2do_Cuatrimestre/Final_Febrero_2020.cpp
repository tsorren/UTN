#include <iostream>
using namespace std;

struct coordenadas
{
    int Long; 
    int Lat;
    int Alt;
};
struct reg
{
    coordenadas InicioTramo;
    coordenadas FinTramo;
    int Ruta;
    int Tramo;
    int VelocidadKMH;
    int MinutosDeDemora;
};

//reg recorridos[N];

int BusquedaBinaria(reg vec[], int N, int ruta, int tramo)
{
    int p = 0;
    int u = N-1;
    int m;
    while(p <= u)
    {
        m = (p+u)/2;
        if(vec[m].Ruta > ruta || (vec[m].Ruta == ruta && vec[m].Tramo > tramo))
            u = m - 1;

        else if (vec[m].Ruta < ruta || (vec[m].Ruta == ruta && vec[m].Tramo < tramo))
            p = m + 1;

        else
            return m;
    }
    return -1;
}
int Distancia(int a1, int b1, int c1, int a2, int b2, int c2)
{
    return 2015;
}

//Vector, ruta, tramo, horaSalida
int CalcularTiempoDeLlegada(reg vec[], int N, int ruta, int tramo, int horaSalida)
{
    int buscado = BusquedaBinaria(vec, N, ruta, tramo);
    coordenadas I = vec[buscado].InicioTramo;
    coordenadas F = vec[buscado].FinTramo;
    int tiempoRecorrido; 
    int horaLlegada;

    tiempoRecorrido = (Distancia(I.Long, I.Lat, I.Alt, F.Long, F.Lat, F.Alt) * 60) / vec[buscado].VelocidadKMH ;
    tiempoRecorrido += vec[buscado].MinutosDeDemora;

    horaLlegada = (horaSalida + (tiempoRecorrido / 60 * 100) + (tiempoRecorrido % 60)) % 2400;
    return horaLlegada;
}

int main()
{
    reg vec[8] = {
                {{0, 0, 0}, {0, 0, 0}, 0, 0, -1, -1},
                {{0, 0, 0}, {0, 0, 0}, 1, 0, -1, -1},
                {{0, 0, 0}, {0, 0, 0}, 1, 1, 60, 10},
                {{0, 0, 0}, {0, 0, 0}, 1, 2, -1, -1},
                {{0, 0, 0}, {0, 0, 0}, 1, 3, -1, -1},
                {{0, 0, 0}, {0, 0, 0}, 1, 4, -1, -1},
                {{0, 0, 0}, {0, 0, 0}, 2, 0, -1, -1},
                {{0, 0, 0}, {0, 0, 0}, 3, 0, -1, -1},
                };
    int buscado = BusquedaBinaria(vec, 8, 1, 1);
    int horaSalida = 1400;
    int horaLlegada = CalcularTiempoDeLlegada(vec, 8, 1, 1, horaSalida);
    cout << "Hora salida: " << horaSalida / 100  << ":" << (horaSalida % 1000)%100 << endl;
    cout << "Hora salida: " << horaLlegada / 100  << ":" << (horaLlegada % 1000)%100 << endl;
    return 0;
}
/*
int CalcularTiempoDeLlegada(reg vec[], int N, int tiempoInicial)
{
    int tiempoRecorrido = 0;
    int tiempoFinal;
    coordenadas I, F;
    for(int i = 0; i < N; i++)
    {
        I = vec[i].InicioTramo;
        F = vec[i].FinTramo;
        tiempoRecorrido += Distancia(I.Long, I.Lat, I.Alt, F.Long, F.Lat, F.Alt) / vec[i].VelocidadKMH * 60;
        tiempoRecorrido += vec[i].MinutosDeDemora;
    }
    tiempoFinal = (tiempoInicial + (tiempoRecorrido / 60 * 100) + (tiempoRecorrido % 60)) % 2400;
    return tiempoFinal;
}
*/