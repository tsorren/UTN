import inmobiliaria.*
import operaciones.*


class Zona 
{
    var property valor
    method cambiarValor(nuevoValor) {valor = nuevoValor}
}

class Inmueble
{    
    const property metrosCuadrados
    const property cantAmbientes
    const property zona

    const property operacion    

    method valor() = zona.valor()
    method reservar(cliente) {operacion.reservar(cliente)}
    method puedeConcretar(cliente) = operacion.puedeConcretar(cliente)
    method concretarOperacion(cliente, empleado) {if(self.puedeConcretar(cliente)) operacion.concretar(cliente, self)}
}
class Casa inherits Inmueble
{
    const valor
    override method valor() = super() + valor
}

class PH inherits Inmueble
{
    override method valor() = super() + (metrosCuadrados * 14000).min(500000)
}

class Departamento inherits Inmueble
{
    override method valor() = super() + cantAmbientes * 350000
}

class Local inherits Casa
{
    var tipoLocal
    override method valor() = tipoLocal.valor(self)
    override method puedeConcretar(cliente) = operacion.habilitadoParaLocales() and super(cliente)
    method remodelar(nuevoTipo) {tipoLocal = nuevoTipo}
}

object galpon
{
    method valor(inmueble) = (inmueble.zona().valor() + inmueble.valor()) / 2
}

object aLaCalle
{
    method valor(inmueble) = inmueble.zona().valor() + inmueble.valor() + inmobiliaria.valorExtraALaCalle()
}