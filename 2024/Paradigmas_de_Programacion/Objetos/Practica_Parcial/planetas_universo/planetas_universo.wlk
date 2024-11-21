// 22:35 - 00:22 -> 2 horas

class Persona
{
    var property edad 
    var property monedas = 20
    var property planetaHogar
    var property region

    var property profesionActual = ningunaProfesion

    const property profesionesDisponibles = [ningunaProfesion]

    var property experienciaProductor = 0
    var property experienciaConstruccion = 0

    method recursos() = profesionActual.recursos(self) 
    method esDestacada() = profesionActual.esDestacada(self)

    method ganarMonedas(cantidad) {monedas = monedas + cantidad}
    method perderMonedas(cantidad) {monedas = monedas - cantidad}

    method trabajarEn(planeta, duracion) = profesionActual.trabajarEn(self, planeta, duracion)

    method mudarseDePlaneta(nuevoPlaneta) {planetaHogar = nuevoPlaneta}
    
    method aprenderProduccion(duracion) 
    {
        
        if(experienciaProductor < 100 and experienciaProductor + duracion >= 100)
        {
            const productor = new Productor()
            profesionesDisponibles.add(productor)
        }
        experienciaProductor = experienciaProductor + duracion
    } 
    method aprenderConstruccion(duracion)
    {
        if(experienciaConstruccion < 100 and experienciaConstruccion + duracion >= 100)
        {
            const constr = new Constructor()
            profesionesDisponibles.add(constr)
        }
        experienciaConstruccion = experienciaConstruccion + duracion
    }

    method cambiarProfesionActual(profesion) {if(profesionesDisponibles.contains(profesion)) profesionActual = profesion}
    method cambiarRegion(nuevaRegion) {region = nuevaRegion}

}

object ningunaProfesion
{
    method recursos(persona) = persona.monedas()
    method trabajarEn(persona, planeta, duracion) {}
    method esDestacada(persona) = persona.recursos() > 30 or persona.edad().between(18, 65) 
}

class Productor
{
    const tecnicas = ["cultivo"]
    
    method cuantasTecnicasConoce() = tecnicas.size()
    method recursos(persona) = persona.monedas() * self.cuantasTecnicasConoce() 
    method esDestacada(persona) = persona.recursos() > 30 or persona.edad().between(18, 65)  or self.cuantasTecnicasConoce() > 5

    method realizarTecnica(persona, tecnica, duracion) 
    {
        if(tecnicas.contains(tecnica)) {persona.ganarMonedas(duracion * 3)}
        else {persona.perderMonedas(1)}
    }

    method aprenderTecnica(tecnica) {if(not tecnicas.contains(tecnica)) tecnicas.add(tecnica)}

    method trabajarEn(persona, planeta, duracion) {if(planeta == persona.planetaHogar()) self.realizarTecnica(persona, tecnicas.last(), duracion)}
}

class Constructor
{
    var construccionesRealizadas = 0
    
    method inteligencia(persona) = (persona.experienciaConstruccion() / 100).truncate(0)
    method recursos(persona) = persona.monedas() + construccionesRealizadas * 10
    method esDestacada(persona) = construccionesRealizadas > 5

    method trabajarEn(persona, planeta, duracion) 
    {
        planeta.nuevaConstruccion(persona.region().tipoConstruccion(persona, self, duracion))
        construccionesRealizadas = construccionesRealizadas + 1
    }
}

object montania
{
    method tipoConstruccion(persona, constr, duracion) = new Muralla(longitud = duracion / 2)
}

object costa
{
    method tipoConstruccion(persona, constr, duracion) = new Museo(superficie = duracion, nivel = 1)
}

object llanura
{
    method tipoConstruccion(persona, constr, duracion)
    {
        if(constr.esDestacada(persona)) return new Muralla(longitud = duracion / 2)
        else return new Museo(superficie = duracion, nivel = constr.recursos(persona) / 100)
    }
}

object volcanica
{
    method tipoConstruccion(persona, constr, duracion)
    {
        return new Museo(superficie = duracion * constr.inteligencia(persona) / 2, nivel = constr.inteligencia(persona) / 2)
    }
}


class Construccion
{
    method tamanio()
    method factor()
    method valor() = self.tamanio() * self.factor()
}
class Muralla inherits Construccion
{
    const longitud
    override method tamanio() = longitud
    override method factor() = 10
}
class Museo inherits Construccion
{
    const superficie
    const nivel
    override method tamanio() = superficie 
    override method factor() = nivel.limitBetween(1, 5)
}
class Planeta
{
    const property habitantes = #{}
    const property construcciones = #{}

    method habitanteMasRico() = habitantes.max({hab => hab.recursos()})
    method delegacionDiplomatica() = habitantes.filter({hab => hab.esDestacada() or hab == self.habitanteMasRico()})

    method valorDeConstrucciones() = construcciones.sum({construccion => construccion.valor()})
    method esValioso() = self.valorDeConstrucciones() > 100

    method nuevaConstruccion(construccion) {construcciones.add(construccion)}
    method nuevoHabitante(habitante) {habitantes.add(habitante)}

    method invadir(otroPlaneta, duracion) {otroPlaneta.delegacionDiplomatica().trabajarEn(self, duracion)}
}