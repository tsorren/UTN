#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

// Estructuras de Datos
struct InfoPaciente{
    int idPaciente;
    char nombre[16+1];
    char apellido[16+1];
    int fechaNacimiento;
    int dni;
    int telefono;
};

struct NodoPaciente{
    InfoPaciente info;
    NodoPaciente* sgte;
};

struct InfoMedico{
    int idMedico;
    char nombre[16+1];
    char apellido[16+1];
    int matricula;
    char especialidad[16+1];
};

struct NodoMedico{
    InfoMedico info;
    NodoMedico* sgte;
};

struct InfoAtencion{
    int idAtencion;
    int fecha;
    int idMedico;
    int idPaciente;
    char diagnostico[64+1];
    int idMedicamento;
};

struct NodoAtencion{
    InfoAtencion info;
    NodoAtencion* sgte;
};

struct Medicamento{
    int idMedicamento;
    char descripcion[64+1];
    char presentacion[16+1]; // Tomamos "presentacion" del medicamento como la forma farmacéutica del mismo
};

//Prototipos
void CargaVectorMedicamentos(Medicamento[], int);

NodoPaciente* InsertarOrdenado(NodoPaciente* &, InfoPaciente);  // Orden DNI Creciente
NodoMedico* InsertarOrdenado(NodoMedico* &, InfoMedico);        // Orden Apellido Ascendiente, Nombre Ascendiente
NodoAtencion* InsertarOrdenado(NodoAtencion* &, InfoAtencion);  // Orden idAtencion Creciente

// Funcion generica que permite cargar los tres tipos de listas
template <typename nodo, typename reg>
void CargaLista(FILE*, nodo* &);

void MostrarBienvenida();

// Nos permite tranformar un entero de 8 digitos a un formato año/mes/dia
void MostrarFecha(int);

void ConsultaPacientes(NodoPaciente*, int);
void ConsultaMedicos(NodoMedico*, char[], char[]);
void ConsultaAtenciones(NodoPaciente*, NodoMedico*, NodoAtencion*, Medicamento[], int);

// Funcion principal del main
bool ElegirOpcion(NodoPaciente*, NodoMedico*, NodoAtencion*, Medicamento[], int);

int main()
{
    // Inicialización de Estructuras de Datos
    FILE *archPacientes = fopen("archivos/PACIENTES.DAT", "rb");
    FILE *archMedicos = fopen("archivos/MEDICOS.DAT", "rb");
    FILE *archAtenciones = fopen("archivos/ATENCIONES.DAT", "rb");

    NodoPaciente* ListaPacientes = NULL;
    NodoMedico* ListaMedicos = NULL;
    NodoAtencion* ListaAtenciones = NULL;
    Medicamento VectorMedicamentos[50];
    
    CargaVectorMedicamentos(VectorMedicamentos, 50);
    CargaLista<NodoPaciente, InfoPaciente>(archPacientes, ListaPacientes);
    CargaLista<NodoMedico, InfoMedico>(archMedicos, ListaMedicos);
    CargaLista<NodoAtencion, InfoAtencion>(archAtenciones, ListaAtenciones);

    fclose(archPacientes);
    fclose(archMedicos);
    fclose(archAtenciones);
    
    MostrarBienvenida(); // ARTE ASCII

    // Se repite hasta que el usuario ingrese "4", luego ElegirOpcion retorna "false" y se termina el do while
    int opcion;    
    bool loop = true;
    do{
        cout << "    -----------------------------" << endl;
        cout << "    |         OPCIONES          |" << endl;
        cout << "    |   1. Consultar Paciente   |" << endl;
        cout << "    |   2. Consultar Medicos    |" << endl;
        cout << "    |   3. Consultar Atencion   |" << endl;
        cout << "    |   4. Salir                |" << endl;
        cout << "    -----------------------------" << endl;
        cout << "    Ingrese la opcion deseada: ";

        cin >> opcion;
        loop = ElegirOpcion(ListaPacientes, ListaMedicos, ListaAtenciones, VectorMedicamentos, opcion);
    } while(loop);

    return 0;
}


void CargaVectorMedicamentos(Medicamento m[], int n)
{
    char descripciones[50][32+1] = {
        "Alivio para la fiebre", "Analgesico efectivo", "Para dolor de cabeza",
        "Antibiotico comun", "Alivio de alergias", "Tratamiento de tos",
        "Baja la presion", "Vitaminas diarias", "Antiinflamatorio fuerte",
        "Tratamiento digestivo", "Contra el insomnio", "Fortalece los huesos",
        "Mejora la digestion", "Para la gripe", "Reduce la inflamacion",
        "Antiacido suave", "Tratamiento de asma", "Ayuda a dormir",
        "Para la ansiedad", "Alivia la congestion", "Para el resfriado",
        "Suplemento vitaminico", "Alivio muscular", "Antiseptico efectivo",
        "Contra la acidez", "Fortalece el sistema", "Vitamina C pura",
        "Tratamiento de la piel", "Para la tos seca", "Antihistaminico",
        "Mejora la memoria", "Antiinflamatorio leve", "Antiacido natural",
        "Para alergias estacionales", "Reduce el estres", "Tratamiento digestivo",
        "Para la hipertension", "Mejora la vision", "Para la migraña",
        "Alivio del dolor", "Antiinflamatorio oral", "Ayuda a la concentracion",
        "Para la digestion", "Tratamiento de la piel", "Antibiotico leve",
        "Fortalece el cabello", "Mejora la circulacion", "Vitamina B completa",
        "Antibiotico fuerte", "Suplemento de calcio"};

    char presentaciones[50][16+1] = {
        "Capsula dura", "Pomada", "Inyectable", "Inhalador", "Aerosol",
        "Tableta", "Solucion oral", "Inhalador", "Capsula dura", "Crema topica",
        "Jarabe", "Inhalador", "Gel topico", "Comprimido", "Pastilla", "Locion",
        "Capsula dura", "Inhalador", "Colirio", "Pastilla", "Gotas orales",
        "Parche dermico", "Capsula blanda", "Polvo oral", "Emulsion", "Inhalador",
        "Pastilla", "Enjuague bucal", "Ampolla", "Spray nasal", "Gotas ocualres",
        "Capsula dura", "Pastilla", "Shampoo", "Granulado", "Efervescente",
        "Pasta dental", "Caramelo", "Capsula blanda", "Locion capilar",
        "Solucion otica", "Capsula blanda", "Pastilla", "Polvo", "Spray bucal",
        "Tableta", "Capsula", "Spray nasal", "Aerosol oral", "Polvo topico",};

    Medicamento aux;
    for(int i = 0; i < n; i++){
        aux.idMedicamento = i;
        strcpy(aux.descripcion, descripciones[i]);
        strcpy(aux.presentacion, presentaciones[i]);

        m[i] = aux;
    }

}

NodoPaciente* InsertarOrdenado(NodoPaciente* &lista, InfoPaciente reg) // Orden DNI Creciente
{
    NodoPaciente* n = new NodoPaciente();
    n->info = reg;
    if(lista == NULL || reg.dni < lista->info.dni){
        n->sgte = lista;
        lista = n;
    }
    else{
        NodoPaciente* aux = lista;
        while(aux->sgte != NULL && aux->sgte->info.dni < reg.dni){
            aux = aux->sgte;
        }
        n->sgte = aux->sgte;
        aux->sgte = n;
    }
    return n;
}

NodoMedico* InsertarOrdenado(NodoMedico* &lista, InfoMedico reg) // Orden Apellido Ascendiente, Nombre Ascendiente
{
    NodoMedico* n = new NodoMedico();
    n->info = reg;
    if(lista == NULL || (strcmp(reg.apellido, lista->info.apellido) < 0) || 
    (strcmp(reg.apellido, lista->info.apellido) == 0 && strcmp(reg.nombre, lista->info.nombre) < 0)){
        n->sgte = lista;
        lista = n;
    }
    else{
        NodoMedico* aux = lista;
        while(aux->sgte != NULL && ((strcmp(reg.apellido, aux->sgte->info.apellido) < 0) || 
        (strcmp(reg.apellido, aux->sgte->info.apellido) == 0 && strcmp(reg.nombre, aux->sgte->info.nombre) < 0))){
            aux = aux->sgte;
        }
        n->sgte = aux->sgte;
        aux->sgte = n;
    }
    return n;
}

NodoAtencion* InsertarOrdenado(NodoAtencion* &lista, InfoAtencion reg)  // Orden idAtencion Creciente
{
    NodoAtencion* n = new NodoAtencion();
    n->info = reg;
    if(lista == NULL || reg.idAtencion < lista->info.idAtencion){
        n->sgte = lista;
        lista = n;
    }
    else{
        NodoAtencion* aux = lista;
        while(aux->sgte != NULL && aux->sgte->info.idAtencion < reg.idAtencion){
            aux = aux->sgte;
        }
        n->sgte = aux->sgte;
        aux->sgte = n;
    }
    return n;
}

// Utilizamos Generics para el tipo de dato de la Lista y para el tipo de dato del Registro info
template <typename nodo, typename reg>
void CargaLista(FILE* f, nodo* &lista)
{
    reg aux;
    int regSize = sizeof(reg);
    fseek(f, 0, SEEK_SET);
    while(fread(&aux, regSize, 1, f)){
        InsertarOrdenado(lista, aux);
    }
    return;
}

// Se utiliza la doble contrabarra para poder mostrar "\"
void MostrarBienvenida()
{    
    cout << "  ____  _     _                       " << endl;
    cout << " / ___|(_)___| |_ ___ _ __ ___   __ _ " << endl;
    cout << " \\___ \\| / __| __/ _ \\ '_ ` _ \\ / _` |" << endl;
    cout << "  ___) | \\__ \\ ||  __/ | | | | | (_| |" << endl;
    cout << " |____/|_|___/\\__\\___|_| |_| |_|\\__,_|" << endl;

    cout << "    __  __   __     _ _           " << endl;
    cout << "   |  \\/  | /_/  __| (_) ___ ___  " << endl;
    cout << "   | |\\/| |/ _ \\/ _` | |/ __/ _ \\ " << endl;
    cout << "   | |  | |  __| (_| | | (_| (_) |" << endl;
    cout << "   |_|  |_|\\___|\\__,_|_|\\___\\___/ " << endl;

    cout << "       _  ___  ___ ____   ___  " << endl;
    cout << "      | |/ / |/ _ |___ \\ / _ \\ " << endl;
    cout << "      | ' /| | | | |__) | (_) |" << endl;
    cout << "      | . \\| | |_| / __/ \\__, |" << endl;
    cout << "      |_|\\_|_|\\___|_____|  /_/ " << endl << endl;
    return;
}


// Separa el año, mes y dia del int
void MostrarFecha(int f)
{
    cout << f/10000 << "/" << (f%10000) / 100 << "/" << (f%100) << endl;
    return;
}

// Busqueda y consulta en Listas
void ConsultaPacientes(NodoPaciente* lista, int dniBuscado)
{
    while(lista != NULL && lista->info.dni != dniBuscado){
        lista = lista->sgte;
    }
    
    if(lista == NULL){
        cout << endl << "    Este paciente no se encuentra en la base de datos" << endl << endl;
        return;
    }

    // MOSTRAR PACIENTE
    cout << endl << "--------------------------------------------------------------------------------" << endl;
    cout << "      PACIENTE: " << endl;
    cout << "          ID: " << lista->info.idPaciente << endl;
    cout << "          Nombre: " << lista->info.nombre << endl;
    cout << "          Apellido: " << lista->info.apellido << endl;
    cout << "          Fecha de Nacimiento: "; MostrarFecha(lista->info.fechaNacimiento); // Mostramos la fecha con formato año/mes/dia
    cout << "          DNI: " << lista->info.dni << endl;
    cout << "          Telefono: " << lista->info.telefono << endl; 
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl;
    
    return;
    
}



void ConsultaMedicos(NodoMedico* lista, char nombre[], char apellido[])
{
    // Aplicamos ley de De Morgan para que se recorra la lista mientras que el apellido y nombre sean distintos
    // !(apellido y nombre) -> !apellido o !nombre
    while((lista != NULL) && 
    ((strcmp(lista->info.apellido, apellido) != 0) || strcmp(lista->info.nombre, nombre) != 0)){
        lista=lista->sgte;
    }

    if(lista == NULL){
        cout << endl << "    Esta persona no se encuentra en la base de datos" << endl << endl;
        return;
    }

    // MOSTRAR MEDICO
    cout << endl << "--------------------------------------------------------------------------------" << endl;
    cout << "      MEDICO: " << endl;
    cout << "          ID: " << lista->info.idMedico << endl;
    cout << "          Apellido: " << lista->info.apellido << endl;
    cout << "          Nombre: " << lista->info.nombre << endl;
    cout << "          Matricula: " << lista->info.matricula << endl;
    cout << "          Especialidad: " << lista->info.especialidad << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl;
    
    return;
}

void ConsultaAtenciones(NodoPaciente* listaPacientes, NodoMedico* listaMedicos, 
                        NodoAtencion* listaAtenciones, Medicamento vectorMedicamentos[], int dni)
{
    // Buscamos el paciente por DNI en la listaPacientes
    while(listaPacientes != NULL && listaPacientes->info.dni != dni){
        listaPacientes = listaPacientes->sgte;
    }

    if(listaPacientes == NULL){
        cout << endl << "    Este paciente no se encuentra en la base de datos" << endl << endl;
        return;
    }

    bool encontro = false;
    NodoMedico* auxMedico;
    Medicamento auxMedicamento;

    // Mostrar todas las veces que el paciente fue atendido
    cout << endl << "--------------------------------------------------------------------------------";
    while(listaAtenciones != NULL){
        if(listaAtenciones->info.idPaciente == listaPacientes->info.idPaciente){
            if(encontro == false){
                cout << endl << "      Paciente: " << listaPacientes->info.nombre << " " << listaPacientes->info.apellido << endl;
                encontro = true;
            }

            auxMedicamento = vectorMedicamentos[listaAtenciones->info.idMedicamento]; // PUP, Medicamento recetado al paciente
            auxMedico = listaMedicos;

            // Buscamos el medico en listaMedico según el idMedico
            while(auxMedico != NULL && auxMedico->info.idMedico != listaAtenciones->info.idMedico){
                auxMedico = auxMedico->sgte;
            }

            // MOSTRAR ATENCIONES
            cout << endl;
            cout << "          ID ATENCION: " << listaAtenciones->info.idAtencion << endl;
            cout << "              Fecha: "; MostrarFecha(listaAtenciones->info.fecha);
            cout << "              Medico: " << auxMedico->info.nombre << " " << auxMedico->info.apellido << endl;
            cout << "              Diagnostico: " << listaAtenciones->info.diagnostico << endl;
            cout << "              Medicamento: " << endl;
            cout << "                  ID: " << listaAtenciones->info.idMedicamento << endl;
            cout << "                  Presentacion: " << auxMedicamento.presentacion << endl;
            cout << "                  Descripcion: " << auxMedicamento.descripcion << endl;
        }
        listaAtenciones = listaAtenciones->sgte;
    }
    if(encontro == false){
        cout << endl << "    Este paciente no tuvo ninguna atencion medica" << endl;
    }

    cout << "--------------------------------------------------------------------------------" << endl << endl;
    return;
}

bool ElegirOpcion(NodoPaciente* listaPacientes, NodoMedico* listaMedicos,
                NodoAtencion* listaAtenciones, Medicamento vectorMedicamentos[], int opcion)
{
    int DNI;
    char nombre[16+1];
    char apellido[16+1];
    switch(opcion){
            case 1: 
                cout << "    Ingrese DNI para consultar por Paciente: ";
                cin >> DNI;
                ConsultaPacientes(listaPacientes, DNI);
                return true;

            case 2: 
                cout << "    Ingrese los siguientes datos del medico:" << endl;
                cout << "        Nombre: ";
                cin >> nombre;
                cout << "        Apellido: ";
                cin >> apellido;
                ConsultaMedicos(listaMedicos, nombre, apellido);
                return true;

            case 3: 
                cout << "    Ingrese DNI para consultar su Atencion: ";
                cin >> DNI;
                ConsultaAtenciones(listaPacientes, listaMedicos, listaAtenciones, vectorMedicamentos, DNI);
                return true;

            case 4:
                return false;

            default:
                cout<<"    Ingrese un numero valido" << endl << endl;
                return true;
                
        }
}
