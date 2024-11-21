/*
empleado:
    habilidades, resolver misiones
    salud variable
    incapacitados -> salud < saludCritica

    tipoEmpleado:
        espia
        oficinista
    
    espia:
        aprender habilidades al completar misiones
        saludCritica = 15
    
    oficinista:
        gana estrella si sobrevive mision
        salud critica = 40 - 5 * estrellas

    resolver mision:
        formar equipos

    empleado jefe de otro, son asistidos
    jefe puede ser tanto espia como oficinista

    1. empleado incapacitado
    2. poder usar habilidad: 
        Tenerla y no estar incapacitado.
        Los jefes pueden si algun subordinado puede
    3. cumplir mision:
        verificar todas las habilidades
        en equipos al menos un integrante verifica todas

        empleado/equipo recibe daño segun peligrosidad, integrantes de equipo reciben 1/3 de daño total

        los que sobreviven registran que la completaron
        oficinistas consiguen estrella. con 3 estrellas puede ser espia
        espias aprenden las habilidades de la mision que no poseían
    
*/

class Empleado
{
    var salud
    var esJefe
    const habilidades = #{}
    const subordinados = #{}

    method saludCritica()
    method estaIncapacitado() = salud < self.saludCritica()
    method estaVivo() = salud > 0

    method finalizarMision(mision) {if(self.estaVivo()) self.efectoFinalizarMision(mision)}
    method efectoFinalizarMision(mision)

    method tiene(habilidad) = habilidades.contains(habilidad)

    method puedeUsar(habilidad) = 
        not self.estaIncapacitado() and 
            (habilidades.contains(habilidad)) or 
            (esJefe and subordinados.any({sub => sub.tiene(habilidad)}))

    method puedeRealizarMision(mision) = mision.habilidades().all({hab => self.puedeUsar(hab)})

    method recibirDanio(cantidad) {salud = salud - cantidad} 

    method tieneExpParaSerEspia()
}

class Espia inherits Empleado
{
    override method saludCritica() = 15
    override method efectoFinalizarMision(mision) {mision.habilidades().forEach({habilidad => habilidades.add(habilidad)})}
    override method tieneExpParaSerEspia() = true
}

class Oficinista inherits Empleado
{
    var cantidadEstrellas = 0

    override method saludCritica() = 40 - 5 * cantidadEstrellas
    override method efectoFinalizarMision(mision) {cantidadEstrellas += 1}
    override method tieneExpParaSerEspia() = cantidadEstrellas >= 3
}

class Equipo
{
    const integrantes
    method puedeRealizarMision(mision) = integrantes.any({integrante => integrante.puedeRealizarMision(mision)})
    method recibirDanio(mision) {integrantes.forEach({integ => integ.recibirDanio(mision.peligrosidad() / 3)})}
    method finalizarMision(mision) = integrantes.forEach({integ => integ.finalizarMision(mision)})

}

class Mision
{
    const property habilidades
    const property peligrosidad
    method esRealizadaPor(alguien) 
    {
        if(alguien.puedeRealizarMision(self)) 
        {
            alguien.recibirDanio(self)
            alguien.finalizarMision()
        }
    }
}