
#include <iostream>

using namespace std;


// 1.
struct participante{
    int ID_Participante;
    int horaPartida; 
    int horaLLegada;
    int categoría;
};
// Se utiliza struct para crear un registro que almacene los datos a ingresar de cada participante

participante participantes[CANTIDAD_INSCRIPTOS];
// Se crea un vector de tipo participante de tamaño CANTIDAD_INSCRIPTOS, valor dado al inicio de la ejecución del programa

int tiemposMinimos[3][2];

// 2.
void OrdenarVector(participante[], int);
// OrdenarVector posee dos parametros, participante[] (vector de tipo participante que almacena registros) y int (tamaño del vector).
// La función es de tipo void ya que el cambio que genera es dentro del vector que recibe como argumento, ya que lo ordena. Por lo que no hay necesidad de retornar otra cosa.
// El tipo de ordenamiento ascendiente de dos campos: ID_Participante y categoría

// 3.
int main(){
    int input;
    cin >> input;

    const int CANTIDAD_INSCRIPTOS = input;

    participante participantes[CANTIDAD_INSCRIPTOS];
    IngresarParticipantes(participantes, CANTIDAD_INSCRIPTOS);
    OrdenarVector(participantes, CANTIDAD_INSCRIPTOS);
    DeterminarPodio(participantes, CANTIDAD_INSCRIPTOS);

    return 0;
}

// 4.
void DeterminarPodio(participante p[], int pTam){
    int tiemposMinimos[3][2] = {999999,0};
    int tActual;
    int idActual;
    int indicePUP;
    int i = 0;
    
    while(i < pTam)
    {
        if(p[i].categoría == 1)
        {
            idActual = p[i].ID_Participante;
            if((idActual == p[i+1].ID_Participante && p[i+1].categoría == 2) && (idActual == p[i+2].ID_Participante && p[i+2].categoría == 3))
            {
                for(int j = 0; j < 3; j++)
                {
                    tActual = p[i+j].horaLLegada - p[i+j].horaPartida;
                    if(tActual < tiemposMinimos[j][0])
                    {
                        tiemposMinimos[j][0] = tActual;
                        tiemposMinimos[j][1] = idActual; 
                    }
                }                
            }
        }
        i++;
    }

}

// Está mal porque son 3 ganadores por etapa, no 1