/*

    13:21 empezar
    14:14 break comer
    15:50 continuar
    16:56 Finalizar tests correctamente

    2 horas

*/

object hogwarts
{
    const property estudiantes = []
    
    method recibirEstudiante(estudiante) 
    {
        estudiantes.add(estudiante)
        sombreroSeleccionador.asignarCasa(estudiante)
    }
}

class Casa
{
    method estudiantes() = hogwarts.estudiantes().filter({est => est.casa() == self})

    method integrantesPuros() = self.estudiantes().filter({est => est.esAceitePuro()})
    method integrantesSucios() = self.estudiantes().filter({est => not est.esAceitePuro()})

    method esPeligrosa() = self.integrantesSucios().size() > self.integrantesPuros().size()
}

object gryffindor inherits Casa
{
    override method esPeligrosa() = false
}

object slytherin inherits Casa
{
    override method esPeligrosa() = true
}

const ravenclaw = new Casa()
const hufflepuff = new Casa()
const sinCasa = new Casa()

class Bot
{
    var property cargaElectrica
    var property esAceitePuro

    method aumentarCargaElectrica(cantidad) {cargaElectrica = cargaElectrica + cantidad} 
    method disminuirCargaElectrica(cantidad) {cargaElectrica = cargaElectrica - cantidad} 
    method cambiarAceite() {esAceitePuro = not esAceitePuro}

    method estaInactivo() = cargaElectrica <= 0

    method recibirHechizo(hechizo) {hechizo.aplicarEfectos(self)}

}
object sombreroSeleccionador inherits Bot(cargaElectrica = 10, esAceitePuro = true)
{
    var property casasDisponibles = [gryffindor, slytherin, ravenclaw, hufflepuff]

    var property siguienteCasa = casasDisponibles.first()

    method definirSiguienteCasa()
    {
        if(casasDisponibles.isEmpty())
        {
            casasDisponibles.add(gryffindor)
            casasDisponibles.add(slytherin)
            casasDisponibles.add(ravenclaw)
            casasDisponibles.add(hufflepuff)
        }
        siguienteCasa = casasDisponibles.first()
        casasDisponibles = casasDisponibles.drop(1)
        
    }


    method asignarCasa(estudiante)
    {
        self.definirSiguienteCasa()
        estudiante.asignarCasa(siguienteCasa)
    }
    override method cambiarAceite() {}
}

class Estudiante inherits Bot
{
    var property casa = sinCasa
    const property hechizos = []

    method asignarCasa(nuevaCasa) {casa = nuevaCasa}
    method cursarMateria(materia) {if(not self.sabe(materia.hechizoCorrespondiente())) hechizos.add(materia.hechizoCorrespondiente())}
    method esExperimentado() = hechizos.size() > 3 and cargaElectrica > 50
    method sabe(hechizo) = hechizos.contains(hechizo)
    method lanzarHechizo(hechizo, objetivo) {if(self.sabe(hechizo) and hechizo.verificarRequisitos(self)) objetivo.recibirHechizo(hechizo)}
    method casaPeligrosa() = casa.esPeligrosa()
}

class Profesor inherits Estudiante
{
    const property materiasDictadas = []
    override method esExperimentado() = super() and materiasDictadas.size() >= 2

    override method disminuirCargaElectrica(cantidad) {if(cargaElectrica - cantidad <= 0) cargaElectrica = cargaElectrica / 2}
    override method cursarMateria(materia) {}
    method dictarMateria(materia) {materiasDictadas.add(materia)}
}

class Materia
{
    var property hechizoCorrespondiente
}

class GrupoEstudiantes
{
    const property estudiantes = #{}

    method ingresarHogwarts() {estudiantes.forEach({est => hogwarts.recibirEstudiante(est)})}
    method cursarMateria(materia) {estudiantes.forEach({est => est.cursarMateria(materia)})}
    method nuevoEstudiante(estudiante) {estudiantes.add(estudiante)}
    method quitarEstudiante(estudiante) {estudiantes.remove(estudiante)}
}

class Hechizo
{
    const requisitos
    const efectos

    method verificarRequisitos(lanzador) = requisitos.apply(lanzador)
    method aplicarEfectos(objetivo) {efectos.apply(objetivo)}
}

const inmobilus = new Hechizo(
    requisitos = {},
    efectos = {obj => obj.disminuirCargaElectrica(50)}
)

const sectumSempra = new Hechizo(
    requisitos = {lanz => lanz.esExperimentado()},
    efectos = {obj => if(obj.esAceitePuro()) obj.cambiarAceite()}
)

const avadakedabra = new Hechizo(
    requisitos = {lanz => not lanz.esAceitePuro() or lanz.casaPeligrosa()},
    efectos = {obj => obj.disminuirCargaElectrica(obj.cargaElectrica().abs())}
)

class HechizoComun inherits Hechizo(requisitos = {lanz => lanz.cargaElectrica() > carga}, efectos = {obj => obj.disminuirCargaElectrica(carga)})
{
    const property carga
}

const vulneraSanentur = new Hechizo(
    requisitos = {lanz => lanz.esExperimentado() and lanz.esAceitePuro()},
    efectos = {obj => 
        obj.aumentarCargaElectrica(25)
        if(not obj.esAceitePuro()) obj.cambiarAceite()
    }
)