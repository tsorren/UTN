import inmobiliaria.*

class Operacion
{
    var estado

    method factorComision()
    method comision(inmueble) = inmueble.valor() * self.factorComision()

    method cambiarEstado(nuevoEstado) {estado = nuevoEstado}
    method reservar(cliente, empleado, inmueble) {estado.reservar(cliente, empleado, inmueble)}
    method puedeConcretar(cliente) = estado.puedeConcretar(cliente)
    method concretar(cliente, empleado, inmueble) 
    {
        empleado.cobrarComision(self.comision(inmueble))
        empleado.registrarOperacion(inmueble)
    }
    method habilitadoParaLocales()
}

class Alquiler inherits Operacion
{
    const property cantMeses
    override method factorComision() = cantMeses / 50000
    override method habilitadoParaLocales() = true
}

class Venta inherits Operacion
{
    override method factorComision() = inmobiliaria.porcentajeComision()
    override method habilitadoParaLocales() = false
}

object sinReservar
{
    method reservar(cliente, empleado, inmueble) 
    {
        inmueble.operacion().cambiarEstado(new Reservada(clienteAsociado = cliente))
        empleado.registrarReserva(cliente, inmueble)
    }
    method puedeConcretar(cliente) = true
}

class Reservada
{
    const property clienteAsociado
    method reservar(cliente, empleado, inmueble) {}
    method puedeConcretar(cliente) = cliente == clienteAsociado
}


object cerrado
{
    method reservar(cliente, empleado, inmueble) {}
    method puedeConcretar(cliente) = false
}
