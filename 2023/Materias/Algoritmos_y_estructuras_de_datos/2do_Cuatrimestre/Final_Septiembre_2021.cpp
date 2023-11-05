#include <iostream>
#include <cstring>
using namespace std;

struct reg{
    char localidad[20+1];
    int numLista,votosValidos;
};

struct localidades{
    char localidad[20+1];
};

void burbuja(FILE*,reg[]);
void funcion (reg[],int [][5],localidades[]);


struct voto
{
    int cant;
    int lista;
    float porcentaje;
};
void BurbujaVotos(voto[], int);
void Funcion(FILE*, int[][5], localidades[]);

int main (){

    FILE* F=fopen("archivos.dat","rb");

    reg arch[20];

    localidades vec[4] = {{"Pinamar"},{"Carilo"},{"Ostende"},{"Valeria del Mar"}};

    int matriz[4][5] = {{0}}; //inicializar matriz en 0

    burbuja(F,arch);
    
    return 0;
}

void burbuja(FILE* F,reg arch[]){
    int i=0,j;
    reg aux;
    while(fread(&aux,sizeof(reg),1,F)){
        arch[i] = aux;
        i++;
    }

    fseek(F,0,SEEK_SET);

    for(i=1;i<20;i++){
        for(j=1;j<=20-i;j++){
            if(arch[j-1].numLista > arch[j].numLista){
                aux = arch[j-1];
                arch[j-1] = arch[j];
                arch[j] = aux;
            }
        }
    }
    return;
}

void funcion(reg arch[],int matriz[][5],localidades vec[]){
    int i,j;
    float total=0;
    //rellenar matriz
    for(i=0;i<5;i++){
        if(strcmp(arch[i].localidad,vec[0].localidad)==0){
            matriz[0][i] += arch[i].votosValidos;
            total+=arch[i].votosValidos;
        }
        else if(strcmp(arch[i].localidad,vec[1].localidad)==0){
            matriz[1][i] += arch[i].votosValidos;
            total+=arch[i].votosValidos;
        }
        else if(strcmp(arch[i].localidad,vec[2].localidad)==0){
            matriz[2][i] += arch[i].votosValidos;
            total+=arch[i].votosValidos;
        }
        else if(strcmp(arch[i].localidad,vec[3].localidad)==0){
            matriz[3][i] += arch[i].votosValidos;
            total+=arch[i].votosValidos;
        }
    }

    //imprimir matriz
    cout<<"\nImprimiendo matriz...\n";
    for(i=0;i<4;i++){
        for(j=0;j<5;j++){
            cout<<matriz[i][j]<<"  ";
        }
        cout<<endl;
    }
    
    //mostrar subtotales de las listas
    i=0;
    float subtotal;
    while(i<5){ // Usar "for" si sos persona normal
        cout<<"\nLista "<<i+1<<": ";   
        subtotal=0;
        for(j=0;j<4;j++){
            subtotal += matriz[j][i];
        }
        cout<<"\nTotal de votos: "<<subtotal;
        cout<<"\nPorcentaje sobre el total: "<<(subtotal/total)*100<<"%";
        i++;
    }
    
    return;
}

//d) a) te ahorras el vector de localidades
//b) propondria una lista por ser dinamica y brinda la posibilidad de recorrerla
//c)





/*
	Si una lista obtiene un porcentaje mayor al 50% de los votos o 
si la diferencia entre primero y segundo es igual o mayor al 10% 
esta será la lista que representará al partido.
	Si ninguna lista cumple lo anterior se deben indicar que dos 
listas (las que obtienen las dos primeras minorías) deben pasar a una 
segunda vuelta. 
*/

// OTRA RESOLUCIÓN

struct voto
{
    int cant;
    int lista;
    float porcentaje;
};

void BurbujaVotos(voto[], int);

FILE* F=fopen("archivos.dat","rb");
localidades vec[4] = {{"Pinamar"},{"Carilo"},{"Ostende"},{"Valeria del Mar"}};
int matriz[4][5] = {{0}}; //inicializar matriz en 0

void Funcion(FILE* f, int m[][5], localidades l[])
{
    fseek(f, 0, SEEK_SET);
    reg aux;
    int iLista;
    int total = 0;
    voto votos[5] = {{0, 0, 0.0}, {0, 1, 0.0}, {0, 2, 0.0}, {0, 3, 0.0}, {0, 4, 0.0}};
    while(fread(&aux, sizeof(reg), 1, f))
    {
        iLista = aux.numLista - 1;
        if(strcmp(aux.localidad, l[0].localidad) == 0)
            m[0][iLista] += aux.votosValidos;
        else if(strcmp(aux.localidad, l[1].localidad) == 0)
            m[1][iLista] += aux.votosValidos;
        else if(strcmp(aux.localidad, l[2].localidad) == 0)
            m[2][iLista] += aux.votosValidos;
        else if(strcmp(aux.localidad, l[3].localidad) == 0)
            m[3][iLista] += aux.votosValidos;
        votos[iLista].cant += aux.votosValidos;
        total += aux.votosValidos;
    }

    for(int i = 0; i < 5; i++)
    {
        votos[i].porcentaje = ((1.0*total) / votos[i].cant) / 100;
        cout << "Lista " << i+1 << ": " << votos[i].cant << " - " << votos[i].porcentaje << endl;
    }

    BurbujaVotos(votos, 5);
    if(votos[0].porcentaje > 50.0 || (votos[0].porcentaje - votos[1].porcentaje) > 10.0)
        cout << "Ganador: " << votos[0].lista << endl;

    else
        cout << "Segunda vuelta entre " << votos[0].lista << " y " << votos[1].lista << endl;
    
    return;
}
