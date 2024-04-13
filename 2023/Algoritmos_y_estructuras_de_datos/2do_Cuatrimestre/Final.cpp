// No tener en cuenta division por tipo, solo positivo y negativo
#include <iostream>
#include <cstring>
using namespace std;
struct regArch
{
    int DNI;
    char apellidoYNombre[20+1];
    char domicilio[16+1];
    int fechaDeNacimiento;
    char centroDeTesteo[16+1];
    char obraSocial[16+1];
    int cantDosis;
    int fechaContacto;
    bool resultado;
};

struct regPaciente
{
    int DNI;
    char apellidoYNombre[20+1];
    int fechaDeNacimiento;
    char domicilio[16+1];
};

struct nodoPaciente
{
    regPaciente info;
    nodoPaciente* sgte;
};

struct regResultados
{
    nodoPaciente* pacientes = NULL;
    int cantidadDePacientes = 0;
};

struct regLista
{
    char obraSocial[16+1];
    regResultados resultados[2];
};

struct nodoLista
{
    regLista info;
    nodoLista* sgte;
};

FILE* f = fopen("hisopados.dat", "rb"); // Desordenado y repetidos
nodoLista* listaPrincipal = NULL;

nodoLista* InsertarSinRepetir(nodoLista*&, char[]);
nodoPaciente* InsertarSinRepetir(nodoPaciente*&, regPaciente);
void CargarEstructura(FILE* f, nodoLista* &listaP)
{
    fseek(f, 0, SEEK_SET);
    regArch actual;
    regPaciente paciente;
    int regArchSize = sizeof(regArch);
    nodoLista* nodoObraSocial = NULL;
    while(fread(&actual, regArchSize, 1, f))
    {
        paciente.DNI = actual.DNI;
        strcpy(paciente.apellidoYNombre, actual.apellidoYNombre);
        paciente.fechaDeNacimiento = actual.fechaDeNacimiento;
        strcpy(paciente.domicilio, actual.domicilio);

        nodoObraSocial = InsertarSinRepetir(listaP, actual.obraSocial);
        if(actual.resultado)
        {
            InsertarSinRepetir(nodoObraSocial->info.resultados[0].pacientes, paciente);
            nodoObraSocial->info.resultados[0].cantidadDePacientes++;
        }
        else
        {            
            InsertarSinRepetir(nodoObraSocial->info.resultados[1].pacientes, paciente);
            nodoObraSocial->info.resultados[1].cantidadDePacientes++;
        }
    }
}

void ImprimirListado(nodoLista* listaP)
{
    nodoLista* aux = listaP;
    nodoPaciente* pacientes = NULL;
    int total, pos, neg;
    while(aux != NULL)
    {
        pos = aux->info.resultados[0].cantidadDePacientes;
        neg = aux->info.resultados[0].cantidadDePacientes;
        total = pos + neg;
        cout << aux->info.obraSocial << ": " << total << endl;

        cout << "Positivos: " << pos << endl;
        pacientes = aux->info.resultados[0].pacientes;
        while(pacientes != NULL)
        {
            cout << "    DNI: " << pacientes->info.DNI << endl;
            cout << "    Nombre:" << pacientes->info.apellidoYNombre << endl;
            cout << "    Nacimiento: " << pacientes->info.fechaDeNacimiento << endl;
            cout << "    Domicilio: " << pacientes->info.domicilio << endl;
            cout << endl; 
            pacientes = pacientes->sgte;
        }

        cout << "Negativos: " << neg << endl;
        pacientes = aux->info.resultados[1].pacientes;
        while(pacientes != NULL)
        {
            cout << "    DNI: " << pacientes->info.DNI << endl;
            cout << "    Nombre:" << pacientes->info.apellidoYNombre << endl;
            cout << "    Nacimiento: " << pacientes->info.fechaDeNacimiento << endl;
            cout << "    Domicilio: " << pacientes->info.domicilio << endl;
            cout << endl; 
            pacientes = pacientes->sgte;
        }
        aux = aux->sgte;
   }
   return;
}
