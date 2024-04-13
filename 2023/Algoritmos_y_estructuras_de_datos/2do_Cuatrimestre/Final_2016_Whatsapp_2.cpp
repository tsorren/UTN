#include <iostream>
#include <string>

using namespace std;

struct Mensaje
{

};

struct conversacion
{
    int IdConversacion;
    string Nombre;
    bool Notificar;
    bool VistaPrevia;
};

struct nodoC
{
    conversacion info;
    nodoC* sgte;
};

struct contacto
{
    int IdUsuario;
    string Nombre;
    bool Bloqueado;
};

nodoC* listaConversaciones = NULL;
contacto usuarios[200]; // Asumo que el arreglo es ordenado previamente al llamado de la funcion NotificarMensajeRecibido

nodoC* Buscar(nodoC*, int);
int BusquedaBinaria(contacto[], int, int);

string NumeroTelefonicoDelUsuario(int);
string VistaPreviaMensaje(Mensaje);
void EmitirNotificacion(string titulo, string descripcion);

void NotificarMensajeRecibido(nodoC*, contacto[], int, int, Mensaje);

void NotificarMensajeRecibido(nodoC* listaC, contacto usuarios[], int uTam, int idConversacion, int idUsuarioEmisor, Mensaje mensaje)
{
    nodoC* nodoBuscado = Buscar(listaC, idConversacion);
    conversacion cActual = nodoBuscado->info;

    int indiceBuscado = BusquedaBinaria(usuarios, uTam, idUsuarioEmisor);

    string Titulo = "", Descripcion = "";

    if(indiceBuscado != -1)
    {        
        contacto usuarioEmisor = usuarios[indiceBuscado];
        if(!usuarioEmisor.Bloqueado && cActual.Notificar)
        {
            if(cActual.Nombre == "")
            {
                Titulo = cActual.Nombre;
                if(cActual.VistaPrevia)
                    Descripcion = usuarioEmisor.Nombre + ": " + VistaPreviaMensaje(mensaje);

                else
                    Descripcion = "Nuevo Mensaje de: " + usuarioEmisor.Nombre;
            }
            else
            {
                Titulo = usuarioEmisor.Nombre;
                if(cActual.VistaPrevia)
                    Descripcion = VistaPreviaMensaje(mensaje);

                else
                    Descripcion = "Nuevo Mensaje";
            }
            EmitirNotificacion(Titulo, Descripcion);
        }
        
    }
    else
    {
        Titulo = NumeroTelefonicoDelUsuario(idUsuarioEmisor);
        if(cActual.VistaPrevia)
            Descripcion = VistaPreviaMensaje(mensaje);
        else
            Descripcion = "Nuevo Mensaje";
        
        EmitirNotificacion(Titulo, Descripcion);
    }
    return;
}