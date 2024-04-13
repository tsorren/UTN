#include <iostream>
using namespace std;

//declarar el tipo numerado utilizando typedef para generR un sinonimo
typedef enum { 
BuenosAires, CABA, Catamarca, Chaco, Chubut, Cordoba, Corrientes, EntreRios, Formosa, Jujuy, LaPampa, 
Rioja, Mendoza, Misiones, Neuquen, RioNegro, Salta, SanJuan, SanLuis, SantaCruz, SantaFe, SgoEStero, 
TdelFuego, Tucuman} Provincia; 


//declaro las structs para el aarchivo y la matriz

struct archVotos{
	Provincia provincia;
	int partido;
	int localidad;
	int padron;
	int blancos;
	int impugnados;
	int listas[5];
	};

struct matrizVotos{
	int padron;
	int blancos;
	int impugnados;
	int listas[5];
	};

struct formulas{
	int listas;
	char nombrespresidenteyvice [30+1];
};

struct vformulas{
	int listas;
	char nombrespresidenteyvice [30+1];
	int totalvotos;
};


//declaro las estructuras de datos a utilizar

//declaramos la matriz
matrizVotos matriz[24][10][20];
vformulas votos[5];
FILE* f=fopen("voto.dat", "rb+");
FILE* g=fopen("candidatos.dat", "rb+");


//declaracion y definicion de las funciones
void cargarcandidatos(FILE* g, vformulas votos[5]);	//funcion que carga el vector de candidatos

void cargarvotos(FILE* f, matrizVotos matriz[][10][20], vformulas votos[5]){
	int i;	//primera dimension matriz
	int j;	//segunda dimension matriz
	int k;	//tercera dimension matriz
	int l;	//para recorrer bucle for
	archVotos r; //declaro variable de tipo archivo
	
	while(fread(&r, sizeof(r), 1, f)){ //leo el archivo
		i= r.provincia;
		j= r.partido;
		k= r.localidad;
		
		matriz[i][j][k].padron=r.padron;
		matriz[i][j][k].impugnados=r.impugnados;
		matriz[i][j][k].blancos=r.blancos;
		
		for(l=0; l < 5; l++){
			matriz[i][j][k].listas[l]=r.listas[l];	//lo que hacemos es cargar en la matriz
			votos[l].totalvotos+=r.listas[l]; 
		}
	}
}

void OrdenarVector(vformulas[], int);

int Presidente(vformulas votos[], int n){
	OrdenarVector(votos, n);	//la damos como funcion hecha
	int i;
	int totalvotos=0;
	
	for(i=0;i<5;i++)
		totalvotos+=votos[i].totalvotos;
	
	float porcentaje;
	porcentaje=1.0 * totalvotos/votos[0].totalvotos;
	
	if(porcentaje >= 0.45 || (porcentaje >= 0.4 && porcentaje - (1.0*totalvotos/votos[1].totalvotos)) >= 0.1)
	    return(votos[0].listas); // Se declara ganador de las elecciones presidenciales
	
    return -1; // Hay segunda vuelta
}
int Gobernador(matrizVotos mVotos[][10][20], Provincia prov)
{
    int votosProv[5] = {0};
    int maxVotos, listaGanadora;
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            for(int k = 0; k < 5; k++)
                votosProv[k] += mVotos[prov][i][k].listas[k];
        }
    }
    maxVotos = votosProv[0];
    listaGanadora = 0;
    for(int i = 1; i < 5; i++)
    {
        if(votosProv[i] > maxVotos)
        {
            maxVotos = votosProv[i];
            listaGanadora = i;
        }
    }
    return listaGanadora;

}