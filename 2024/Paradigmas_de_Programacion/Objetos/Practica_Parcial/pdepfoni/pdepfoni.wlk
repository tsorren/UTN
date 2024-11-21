/*
    18:21
    20:39

    2 horas 18 minutos
*/

object empresaTelefonica
{
    var property precioMB = 0.01
    var property precioSegundo = 0.05
    var property precioFijo = 1.0

    method consumoInternet(cantidad) = precioMB * cantidad
    method consumoLlamada(segundos) = precioFijo + precioSegundo * segundos
}

class Consumo
{
    const property fecha
    const property costo
    const property detalle
}

class Linea
{
    const property nroTel
    const property packs = []
    
    var property tipoLinea = new Comun()

    const property consumos = []
    
    method cambiarTipoLinea(nuevoTipo) {tipoLinea = nuevoTipo}
    method agregarPack(nuevoPack) {packs.add(nuevoPack)}

    method packPuedeSatisfacerConsumo(pack, deInternet, cantidad) = pack.deInternet() == deInternet and pack.verificarRequisitos(cantidad)

    method consumir(deInternet, cantidad) 
    {
        const paquetesDisponibles = packs.filter({p => self.packPuedeSatisfacerConsumo(p, deInternet, cantidad)})

        if(not paquetesDisponibles.isEmpty()) 
        {
            paquetesDisponibles.last().consumir(self, cantidad)
            self.registrarConsumo(paquetesDisponibles.last().ultimoConsumo())
        }
        else if(tipoLinea.esEspecial()) 
        {
            var costoConsumo
            if(deInternet) costoConsumo = empresaTelefonica.consumoInternet(cantidad)
            else  costoConsumo = empresaTelefonica.consumoLlamada(cantidad)
            tipoLinea.registrarConsumoEspecial()
            self.registrarConsumo(new Consumo(
                fecha = new Date(),
                costo = costoConsumo,
                detalle = "Consumo " + tipoLinea.toString())
            )
        }
        else {throw new DomainException(message = "La linea no tiene los suficientes packs para realizar el consumo")}
    }
    
    method consumirInternet(mb) {self.consumir(true, mb)} 
    method consumirLlamada(segundos) {self.consumir(false, segundos)} 

    method registrarConsumo(nuevoConsumo) {consumos.add(nuevoConsumo)}

    method deuda() = tipoLinea.deuda()

    method consumosEntre(inicio, fin) = consumos.filter({c => c.fecha().between(inicio, fin)})

    method gastoDeConsumos(listaConsumos) = listaConsumos.sum({c => c.costo()})

    method gastoMensual() = self.gastoDeConsumos(self.consumosEntre(new Date().minusDays(30), new Date()))
    method gastoPromedioEntre(inicio, fin) = self.gastoDeConsumos(self.consumosEntre(inicio, fin)) / self.consumosEntre(inicio, fin).size()

    method limpiarPacks() {packs.find({p => p.consumido()}).forEach({p => packs.remove(p)})}

}

class Pack
{
    var property consumoDisponible
    var property ultimoConsumo = new Consumo(fecha = new Date(), costo = 0, detalle = "")
    method consumido() = consumoDisponible <= 0

    method deInternet() = false

    method verificarRequisitos(cantidad) = not self.consumido()

    method costoConsumo(cantidad)
    method disminuirConsumoDisponible(cantidad) {consumoDisponible = consumoDisponible - cantidad}
    method consumir(linea, cantidad) 
    {
        ultimoConsumo = new Consumo(fecha = new Date(), costo = self.costoConsumo(cantidad), detalle = self.toString())
    }
}

class MBsLibres inherits Pack
{
    override method deInternet() = true
    override method verificarRequisitos(cantidad) = super(cantidad) and consumoDisponible >= cantidad
    
    override method costoConsumo(cantidad) = cantidad * empresaTelefonica.precioMB()
    override method consumir(linea, cantidad) 
    {
        if(self.verificarRequisitos(cantidad))
        {
            super(linea, cantidad)
            self.disminuirConsumoDisponible(cantidad)
        }
    }
}

class CreditoDisponible inherits Pack
{
    override method deInternet() = false
    override method verificarRequisitos(cantidad) = super(cantidad) and consumoDisponible >= self.costoConsumo(cantidad)
    override method costoConsumo(cantidad) = empresaTelefonica.precioFijo() + cantidad * empresaTelefonica.precioSegundo()
    override method consumir(linea, cantidad) 
    {
        super(linea, cantidad)
        self.disminuirConsumoDisponible(self.costoConsumo(cantidad))
    }
}

class LlamadasGratis inherits CreditoDisponible
{
    override method verificarRequisitos(cantidad) = true
    override method costoConsumo(cantidad) = 0
}

class InternetIlimitadoLosFindes inherits MBsLibres
{
    method esFinde() 
    {
        const hoy = new Date()
        return hoy.dayOfWeek() == calendar.saturday() or hoy.dayOfWeek() == calendar.sunday()
    }
    override method verificarRequisitos(cantidad) = super(cantidad) or self.esFinde()

    override method costoConsumo(cantidad) = if(self.esFinde()) 0 else super(cantidad)
}

class MBsLibresPlusPlus inherits MBsLibres
{
    override method verificarRequisitos(cantidad) = super(cantidad) or cantidad.between(0, 0.1)
    override method costoConsumo(cantidad) = if(cantidad.between(0, 0.1)) 0 else super(cantidad)
}

class Comun 
{
    var property deuda = 0
    method esEspecial() = false
    method registrarConsumoEspecial(costoConsumo) {}
}

class Black inherits Comun
{
    override method esEspecial() = true
    override method registrarConsumoEspecial(costoConsumo) {deuda = deuda + costoConsumo}
}

class Platinum inherits Comun
{
    override method esEspecial() = true
}