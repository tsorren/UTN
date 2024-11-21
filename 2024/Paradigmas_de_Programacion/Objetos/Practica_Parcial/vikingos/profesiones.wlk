import vikingos.*

object granjero
{
    method esProductivo(vikingo) = vikingo.hectareas() > vikingo.cantHijos() * 2 
    method premioAscenso(vikingo) 
    {
        vikingo.recibirHijos(2)
        vikingo.recibirHectareas(2)
    }
}

object soldado
{
    method esProductivo(vikingo) = vikingo.vidasCobradas() > 20 
    method premioAscenso(vikingo) {vikingo.recibirArmas(10)}
}