import vikingos.*

class Expedicion
{
    const objetivos
    const vikingos = []
    var property botinAdquirido = 0

    method cantVikingos() = vikingos.size()

    method puedeSubir(vikingo) = vikingo.esProductivo()
    method subir(vikingo) {if(self.puedeSubir(vikingo)) vikingos.add(vikingo) else self.error("El vikingo no puede subir ya que no es productivo")}

    method valeLaPena() 
    {
        const exp = self
        return objetivos.all({objetivo => objetivo.valeLaPena(exp)})
    }
    
    method cobrarVidas(cantidad) {vikingos.take(cantidad).forEach({vik => vik.cobrarVida()})}
    method repartirBotin() {vikingos.forEach({vik => vik.recibirBotin(botinAdquirido / self.cantVikingos())})}

    method realizarInvasion()
    {
        const exp = self
        objetivos.forEach({objetivo => 
            botinAdquirido += objetivo.botin(exp)
            objetivo.recibirInvasion(exp)
        })
        self.repartirBotin()
    }
}

class Objetivo
{
    method valorBase(expedicion)
    method factor(expedicion) = 1

    method valorMinimo(expedicion)

    method botin(expedicion) = self.valorBase(expedicion) * self.factor(expedicion)
    method valeLaPena(expedicion) = self.botin(expedicion) >= self.valorMinimo(expedicion)
    
    method recibirInvasion(expedicion) 
}

class Capital inherits Objetivo
{
    var property cantDefensores
    const property factorRiqueza

    method defensoresDerrotados(expedicion) = expedicion.cantVikingos().min(cantDefensores)

    override method valorBase(expedicion) = self.defensoresDerrotados(expedicion)
    override method factor(expedicion) = factorRiqueza 
    override method valorMinimo(expedicion) = expedicion.cantVikingos() * 3
    override method recibirInvasion(expedicion) 
    {
        expedicion.cobrarVidas(self.defensoresDerrotados(expedicion))
        cantDefensores = cantDefensores - self.defensoresDerrotados(expedicion)
    } 

}

class Aldea inherits Objetivo
{
    var property cantCrucifijos

    override method valorBase(expedicion) = cantCrucifijos
    override method valorMinimo(expedicion) = 15
    override method recibirInvasion(expedicion) {cantCrucifijos = 0} 
}
class AldeaAmurallada inherits Aldea
{
    const minimoDeVikingos
    override method valeLaPena(expedicion) = super(expedicion) and expedicion.cantVikingos() >= minimoDeVikingos
}