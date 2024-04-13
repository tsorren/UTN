/*
    Se dispone un archivo binario de inscripción de alumnos a exámenes finales 
    MAESTROFINALES.DAT y otro con las inscripciones del día de hoy DIAFINALES.DAT, 
    ambos ordenados ascendente por código de materia y con el siguiente diseño: 
    a. Nro de legajo (8 dígitos) 
    b. Código de materia (6 dígitos) 
    c. ApellidoNombre(25caract) 
    Se pide desarrollar un programa que genere un nuevo archivo de inscripciones a finales 
    FINALESACT.DAT resultante del apareo de los dos archivos anteriores, con el mismo orden 
    y diseño.
*/
#include <iostream>

using namespace std;

struct structInscripcion
{
    int legajo;
    int codigo;
    char apellidoNombre[25+1];
};

void CargarArchivos(FILE*);

int CalcularTamaño(FILE*, int);
void Apareo(structInscripcion[], structInscripcion[], int, int, structInscripcion[], int&);

void LeerArchivo(FILE*);

int main()
{
    FILE* maestro = fopen("archivos/ej5_MAESTROFINALES.DAT", "rb+");
    FILE* dia = fopen("archivos/ej5_DIAFINALES.DAT", "rb+");
    FILE* apareo = fopen("archivos/ej5_FINALESACT.DAT", "wb+");

    //CargarArchivos(maestro);
    //CargarArchivos(dia);

    const int structSize = sizeof(structInscripcion);

    const int maestroSize = CalcularTamaño(maestro, structSize);
    const int diaSize = CalcularTamaño(dia, structSize);;
    const int apareoSize = maestroSize + diaSize;
    int apareoTamLogico = 0;

    structInscripcion mVec[maestroSize];
    structInscripcion dVec[diaSize];
    structInscripcion aVec[apareoSize];

    fread(&mVec, structSize, maestroSize, maestro);
    fread(&dVec, structSize, diaSize, dia);

    Apareo(mVec, dVec, maestroSize, diaSize, aVec, apareoTamLogico);
    
    fwrite(&aVec, structSize, apareoTamLogico, apareo);

    LeerArchivo(apareo);

    fclose(maestro);
    fclose(dia);
    fclose(apareo);

    return 0;
}

void CargarArchivos(FILE* file)
{
    int i = 0;

    structInscripcion inscr;
    int inscrSize = sizeof(structInscripcion);


    cout << "Registro Nro " << i << endl;

    cout << "    Nro de legajo: ";
    cin >> inscr.legajo;
        

    while(inscr.legajo != -1)
    {
        cout << "    Codigo de materia: ";
        cin >> inscr.codigo; 

        cout << "    Apellido y Nombre (sin espacio): ";
        cin >> inscr.apellidoNombre;

        fwrite(&inscr, inscrSize, 1, file);
        i++;
        
        cout << endl << "Registro Nro " << i << endl;

        cout << "    Nro de legajo: ";
        cin >> inscr.legajo;        
    }
    cout << endl;

    fseek(file, 0, SEEK_SET);

    return;
}

int CalcularTamaño(FILE* file, int size)
{
    fseek(file, 0, SEEK_END);
    int desplazamiento = ftell(file);

    fseek(file, 0, SEEK_SET);

    return desplazamiento/size;
}

void Apareo(structInscripcion mVec[], structInscripcion dVec[], int mSize, int dSize, structInscripcion aVec[], int& tamLogico)
{
    int i = 0;
    int j = 0;
    tamLogico = 0;

    while((i < mSize) && (j < dSize))
    {
        if(mVec[i].codigo < dVec[j].codigo)
        {
            aVec[tamLogico] = mVec[i];
            i++;
        }
        else
        {
            aVec[tamLogico] = dVec[j];
            j++;
        }
        tamLogico++;
    }

    while(i < mSize)
    {
        aVec[tamLogico] = mVec[i];
        i++;
        tamLogico++;
    }

    while(j < dSize)
    {
        aVec[tamLogico] = dVec[j];
        j++;
        tamLogico++;
    }

    return;
}

void LeerArchivo(FILE* file)
{
    structInscripcion curr;
    int s = sizeof(structInscripcion);
    int i = 0;

    fseek(file, 0, SEEK_SET);
    fread(&curr, s, 1, file);

    while(!feof(file))
    {
        cout << "Pos " << i << ": " << endl;
        cout << "    Legajo: " << curr.legajo << endl;
        cout << "    Codigo de Materia: " << curr.codigo << endl;
        cout << "    Apellido y Nombre: " << curr.apellidoNombre << endl << endl; 
        
        fread(&curr, s, 1, file);
        i++;
    }
    return;
}