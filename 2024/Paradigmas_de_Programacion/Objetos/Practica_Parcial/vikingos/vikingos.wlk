/*
    19:09
    20:34

    1 hora 25 minutos
*/
import profesiones.*
import expediciones.*

class Vikingo
{
    var property profesion
    var property clase

    // Valores numéricos:
    var property cantHijos
    var property hectareas
    var property vidasCobradas
    var property cantArmas
    var property botin

    
    method esProductivo() = clase.esProductivo(self)
    method estaArmado() = cantArmas > 0

    method cobrarVida() {vidasCobradas += 1}
    method recibirArmas(cantidad) {cantArmas += cantidad}
    method recibirHectareas(cantidad) {hectareas += cantidad}
    method recibirHijos(cantidad) {cantHijos += cantidad}
    method recibirBotin(cantidad) {botin += cantidad}

    method cambiarClase(nuevaClase) {clase = nuevaClase}
    method ascenderClase() {clase.ascenderClase(self)}

    method intentarSubir(expedicion) {expedicion.subir(self)}
}
object jarl
{
    method esProductivo(vikingo) = vikingo.profesion().esProductivo(vikingo) and not vikingo.estaArmado()
    method ascenderClase(vikingo) 
    {
        vikingo.profesion().premioAscenso(vikingo)
        vikingo.cambiarClase(karl)
    }
}

object karl 
{
    method esProductivo(vikingo) = vikingo.profesion().esProductivo(vikingo)
    method ascenderClase(vikingo) {vikingo.cambiarClase(thrall)}
}

object thrall
{
    method ascenderClase(vikingo) {}
}
