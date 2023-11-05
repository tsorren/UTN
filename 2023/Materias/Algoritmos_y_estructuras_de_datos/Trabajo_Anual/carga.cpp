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

struct InfoMedico{
    int idMedico;
    char nombre[16+1];
    char apellido[16+1];
    int matricula;
    char especialidad[16+1];
};

struct InfoAtencion{
    int idAtencion;
    int fecha;
    int idMedico;
    int idPaciente;
    char diagnostico[64+1];
    int idMedicamento;
};

void CargaArchivoPacientes(FILE*);
void CargaArchivoMedicos(FILE*);
void CargaArchivoAtenciones(FILE*);

int main()
{
    FILE *archPacientes = fopen("archivos/PACIENTES.DAT", "rb+");
    FILE *archMedicos = fopen("archivos/MEDICOS.DAT", "rb+");
    FILE *archAtenciones = fopen("archivos/ATENCIONES.DAT", "rb+");

    CargaArchivoPacientes(archPacientes);
    CargaArchivoMedicos(archMedicos);
    CargaArchivoAtenciones(archAtenciones);
    
    return 0;
}

void CargaArchivoPacientes(FILE* f)
{
    char nombres[20][9+1] =  {
        "Luis", "Maria", "Juan", "Ana", "Carlos", "Elena", "Pedro", "Laura",
        "Miguel", "Sofia", "Javier", "Isabel", "Pablo", "Lucia", "Diego",
        "Valeria", "Alejandro", "Carmen", "Fernando", "Natalia"
    };

    char apellidos[20][10+1] = {
        "Gonzalez", "Rodriguez", "Lopez", "Martinez", "Perez", "Gomez", "Sanchez",
        "Fernandez", "Moreno", "Jimenez", "Navarro", "Ruiz", "Diaz", "Hernandez",
        "Torres", "Santos", "Vargas", "Castro", "Romero", "Alvarez"

    };

    int fechas[20] = {
        19621203, 19651014, 19680727, 19710908, 19740419, 19760630, 19780812,
        19810123, 19840304, 19870415, 19890826, 19920607, 19950318, 19971129,
        19990310, 20010121, 20040202, 20060113, 20080224, 20090406

    };

    int DNIs[20] = {
        30678945, 41782594, 23896457, 39145286, 45268971, 56781423, 12987456,
        38521497, 22095674, 47362581, 54218793, 68741235, 15982473, 32485679,
        43197568, 27659814, 59872134, 36418927, 47786315, 21054789
    };

    int telefonos[20] = {
        1101234567, 1112345678, 1123456789, 1134567890, 1145678901, 1156789012, 1167890123,
        1178901234, 1189012345, 1190123456, 1109876543, 1118765432, 1127654321, 1136543210,
        1145432109, 1154321098, 1163210987, 1172109876, 1181098765, 1190987654
    };

    InfoPaciente aux;
    fseek(f, 0, SEEK_SET);
    for(int i = 0; i < 20; i++){
        aux.idPaciente = i;
        strcpy(aux.nombre, nombres[i]);
        strcpy(aux.apellido, apellidos[i]);
        aux.fechaNacimiento = fechas[i];
        aux.dni = DNIs[i];
        aux.telefono = telefonos[i];

        fwrite(&aux, sizeof(InfoPaciente), 1, f);
    }
    fseek(f, 0, SEEK_SET);
    return;
}

void CargaArchivoMedicos(FILE* f)
{
    char nombres[20][10+1] = {
        "Lucas", "Sofia", "Mateo", "Valentina", "Gabriel", "Camila", "Renata",
        "Isabella", "Lautaro", "Martina", "Facundo", "Bianca", "Mariano",
        "Celeste", "Renzo", "Violeta", "Agustin", "Lucia", "Matias", "Olivia"};

    char apellidos[20][16+1] = {
        "Muller", "Smith", "Garcia", "Schmidt", "Brown", "Lopez", "Johnson", "Martinez",
        "Taylor", "Rodriguez", "Wilson", "Sanchez", "Williams", "Andersen", "Gonzalez",
        "Martin", "Hansen", "Lewis", "Fernandez", "Schneider"};

    int matriculas[20] = {
        62545, 67890, 54321, 98765, 72512, 78901, 65432,
        98756, 23125, 56789, 43214, 97865, 54326, 78910,
        65433, 98757, 32751, 56790, 43215, 97866};

    char especialidades[20][16+1] = {
        "Cardiologia", "Dermatologia", "Ginecologia", "Neurologia", "Oftalmologia",
        "Ortopedia", "Pediatria", "Psiquiatria", "Radiologia", "Urologia", "Endocrinologia",
        "Nefrologia", "Hematologia", "Cirugia general", "Oncologia", "Laringologia", "Reumatologia",
        "Geriatria", "Anestesiologia", "Medicina Interna"};

    InfoMedico aux;
    fseek(f, 0, SEEK_SET);
    for(int i = 0; i < 20; i++){
        aux.idMedico = i;
        strcpy(aux.nombre, nombres[i]);
        strcpy(aux.apellido, apellidos[i]);
        aux.matricula = matriculas[i];
        strcpy(aux.especialidad, especialidades[i]);

        fwrite(&aux, sizeof(InfoMedico), 1, f);
    }    
    fseek(f, 0, SEEK_SET);
    return;
}

void CargaArchivoAtenciones(FILE* f)
{
    int fechas[40] = {
        20230102, 20230105, 20230120, 20230121, 20230127, 20230128, 20230209, 20230214,
        20230304, 20230305, 20230315, 20230317, 20230403, 20230421, 20230426, 20230516,
        20230517, 20230527, 20230529, 20230603, 20230615, 20230708, 20230709, 20230710,
        20230728, 20230815, 20230827, 20230920, 20230921, 20230922, 20231009, 20231027,
        20231103, 20231104, 20231108, 20231202, 20231209, 20231215, 20231216, 20231221};

    int idMedicos[40] = {
        8, 3, 1, 12, 6, 17, 11, 0, 15, 9, 7, 14, 5, 10, 18, 2, 4, 16, 13, 19,
        1, 7, 12, 9, 3, 0, 6, 15, 10, 8, 18, 13, 11, 16, 19, 4, 2, 14, 5, 17};

    int idPacientes[40] = {
        5, 12, 9, 3, 8, 17, 0, 7, 6, 13, 18, 1, 10, 15, 4, 2, 11, 16, 14, 19,
        3, 7, 0, 18, 9, 16, 6, 14, 12, 10, 4, 5, 1, 19, 11, 8, 15, 2, 17, 13};

    char diagnosticos[40][64+1] = {
        "El paciente tenia dolor de cabeza", "El paciente presentaba dolor de estomago",
        "Se observo fiebre en el paciente", "El paciente experimento fatiga extrema",
        "El paciente tenia dificultad para respirar", "El paciente sufria de insomnio",
        "Se registraron nauseas y vomitos en el paciente", "El paciente tenia dolor en la garganta",
        "El paciente experimento mareos y vertigos", "Se diagnostico un resfriado comun",
        "El paciente presentaba debilidad muscular", "Se informo de perdida de apetito",
        "El paciente tenia dificultades para concentrarse", "Se observo hinchazon en las extremidades",
        "El paciente presentaba ansiedad", "Se registraron problemas de vision",
        "Se diagnostico una alergia estacional", "El paciente tenia dolor en las articulaciones",
        "Se detecto un caso de hipertension", "El paciente experimento sudoracion excesiva",
        "El paciente tenia problemas para conciliar el sueño", "Se observaron problemas de memoria en el paciente",
        "El paciente presentaba irritacion en la piel", "Se registraron episodios de tos persistente",
        "El paciente tenia palpitaciones cardiacas", "El paciente experimento perdida de peso inesperada",
        "El paciente tenia problemas de equilibrio", "Se diagnostico una alergia a los alimentos",
        "El paciente presentaba trastornos de la conducta alimentaria", "Se observo hiperactividad en el paciente",
        "El paciente experimento perdida de coordinacion motora", "El paciente tenia problemas de audicion",
        "Se registraron episodios de fiebre alta", "El paciente tenia problemas de concentracion",
        "Se observaron manchas en la piel del paciente", "El paciente presentaba dificultades para hablar",
        "El paciente experimento debilidad en las piernas", "Se diagnostico una infeccion respiratoria",
        "El paciente tenia dolor en el pecho", "El paciente sufria de alucinaciones"};

    int idMedicamentos[40] = {
        12, 4, 34, 28, 6, 42, 19, 9, 23, 31, 14, 5, 17, 3, 48, 10, 37, 26, 8, 41,
        15, 32, 1, 49, 7, 27, 21, 2, 45, 13, 39, 20, 30, 16, 25, 11, 33, 36, 29, 22};

    InfoAtencion aux;
    fseek(f, 0, SEEK_SET);
    for(int i = 0; i < 40; i++){
        aux.idAtencion = i;
        aux.fecha = fechas[i];
        aux.idMedico = idMedicos[i];
        aux.idPaciente = idPacientes[i];
        strcpy(aux.diagnostico, diagnosticos[i]);
        aux.idMedicamento = idMedicamentos[i];

        fwrite(&aux, sizeof(InfoAtencion), 1, f);
    }
    fseek(f, 0, SEEK_SET);
    return;
}