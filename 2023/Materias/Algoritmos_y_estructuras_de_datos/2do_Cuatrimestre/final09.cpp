#include <iostream>
#include <cstring>
using namespace std;

struct hisopados{
	int dni;
	char apynom[50];
	int fecnac;
	char dclio[50];
	int centroTest;
	char tipoT; //A P
	char os[50];
	int cantDosis;
	int fecCont;
	bool resultado;
};
struct tipoVecResultados{
	int dni;
	char apynom[50];
	int fecnac;
	char dclio[50];
};
struct nodoTVR{
	tipoVecResultados info;
	nodoTVR* sgte;
};
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct resxOS{
	int total=0;
	nodoTVR* ptr;
};
struct tinfoListado{
	char os[50];
	int total=0;
	resxOS vecR[4];
};

struct nodo{
	tinfoListado info;
	nodo* sgte;
};
nodo* insertarOrdenado(nodoTVR*& lista,tipoVecResultados info);
nodo* insertarSinRepetir(tinfoListado ve,nodo* lista);
void cargarEstructura(nodo* lista,FILE* f);
tinfoListado pop(nodo* lista);

int main() {
	
	return 0;
}
void cargarEstructura(nodo* lista,FILE* f)
{
	hisopados his;
	tinfoListado auxIL;
	tipoVecResultados auxRes;
	nodo* auxNodo;
	int i;
	while(fread(&his,sizeof(hisopados),1,f))
	{
		strcpy(auxIL.os,his.os);
		//inicializar los punteros en null
		auxNodo=insertarSinRepetir(auxIL,lista);
		auxNodo->info.total ++; //suma para el total por os
		
		strcpy(auxRes.apynom,his.apynom);
		strcpy(auxRes.dclio,his.dclio);
		auxRes.dni = his.dni;
		auxRes.fecnac = his.fecnac;
		
		if(his.resultado)
		{
			if(his.tipoT=='A')
			{
				insertarOrdenado(auxNodo->info.vecR[0].ptr,auxRes);
				auxNodo->info.vecR[2].total++;
			}
			else{
				insertarOrdenado(auxNodo->info.vecR[1].ptr,auxRes);
				auxNodo->info.vecR[1].total++;
			}
		}
		else
		{
			if(his.tipoT=='A')
			{
				insertarOrdenado(auxNodo->info.vecR[2].ptr,auxRes);
				auxNodo->info.vecR[2].total++;
			}
			else{
				insertarOrdenado(auxNodo->info.vecR[3].ptr,auxRes);
				auxNodo->info.vecR[3].total++;
			}
		}
	}
}
void imprimirListado(nodo* lista){
	nodo* aux;
	nodoTVR* auxSL;
	int totalP=0;
	int int totalP=0;
	while(lista!=NULL)
	{
		aux=pop(lista);
		cout <<"OS" << cout << aux->info.os <<
		"Total:" << aux->info.total;
		 totalP=aux->info.vecR[0].total + aux->info.vecR[1].total;
		 totalN=aux->info.vecR[2].total + aux->info.vecR[3].total;
		 cout << "Total positivos" << totalP;
		 cout << "antigenos" << info.vecR[0].total;
		while(info.vecR[0].ptr != NULL){
			auxSL=pop2(info.vecR[0].ptr);
			cout << auxSL->info.apynom 
			     << auxSL->info.dni
			     << auxSL->info.dclio
			     << auxSL->info.fecnac;
		}
		cout << "PCR" << info.vecR[1].total;
		while(info.vecR[1].ptr != NULL){
			auxSL=pop2(info.vecR[1].ptr);
			cout << auxSL->info.apynom 
			     << auxSL->info.dni
			     << auxSL->info.dclio
			     << auxSL->info.fecnac;
		}
		 cout << "Total negativos" << totalN;
		 cout << "antigenos" << info.vecR[2].total;
		while(info.vecR[2].ptr != NULL){
			auxSL=pop2(info.vecR[2].ptr);
			cout << auxSL->info.apynom 
			     << auxSL->info.dni
			     << auxSL->info.dclio
			     << auxSL->info.fecnac;
		}
		cout << "PCR" << info.vecR[3].total;
		while(info.vecR[3].ptr != NULL){
			auxSL=pop2(info.vecR[3].ptr);
			cout << auxSL->info.apynom 
			     << auxSL->info.dni
			     << auxSL->info.dclio
			     << auxSL->info.fecnac;
		}
	}
}

nodo* insertarOrdenado(nodo*& lista,tinfoListado info){
	nodo* res;
	return res;
}
nodo* insertarSinRepetir(tinfoListado ve,nodo* lista){
	nodo* res;
	return res;
}
tinfoListado pop(nodo* lista){
	tinfoListado aux;
	return aux;
}

