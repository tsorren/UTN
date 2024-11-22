/*
    22:16
    00:08
    1 hora 52 minutos
*/
object inmobiliaria
{
    const empleados = []

    var porcentajeComision = 1.0
    var property valorExtraALaCalle =  35000

    method porcentajeComision() = porcentajeComision / 100.0
    method mejorEmpleado(criterio) = empleados.max({empleado => criterio.evaluar(empleado)})

    method cambiarPorcentajeComision(nuevoValor) {porcentajeComision = nuevoValor}
    method cambiarvalorExtraALaCalle(nuevoValor) {valorExtraALaCalle = nuevoValor}
}

class Criterio
{
    const criterio
    method evaluar(empleado) = criterio.apply(empleado)
}

const segunComisiones = new Criterio(criterio = {{empleado => empleado.comisiones()}})
const segunOperacionesCerradas = new Criterio(criterio = {{empleado => empleado.cantidadOperacionesCerradas()}})
const segunReservas = new Criterio(criterio = {{empleado => empleado.cantidadReservas()}})

class Empleado
{
    var property comisiones
    const property reservas = []
    const property operacionesCerradas = []

    method cantidadOperacionesCerradas() = operacionesCerradas.size()
    method cantidadReservas() = reservas.size()

    method cobrarComisiones(cantidad) {comisiones += cantidad}
    method registrarReserva(cliente, inmueble) {reservas.add(new RegistroReserva(inmueble = inmueble, cliente = cliente, fecha = new Date()))}
    method registrarOperacion(inmueble) {operacionesCerradas.add(inmueble)}

    method zonasOperadas() = operacionesCerradas.map({o => o.zona()}).asSet()
    method operoEn(zona) = self.zonasOperadas().contains(zona)
    method operaEnZonaComun(otroEmpleado) = self.zonasOperadas().any({zona => otroEmpleado.operoEn(zona)})

    method operoReservaDe(otroEmpleado) = otroEmpleado.reservas().any({reserva => reserva.fueCerradaPor(self)})

    method tendraProblemasCon(otroEmpleado) = self.operaEnZonaComun(otroEmpleado) or self.operoReservaDe(otroEmpleado) or otroEmpleado.operoReservaDe(self)
}

class RegistroReserva
{
    const property inmueble
    const property cliente
    const property fecha

    method fueCerradaPor(empleado) = empleado.operacionesCerradas().contains(inmueble)
}