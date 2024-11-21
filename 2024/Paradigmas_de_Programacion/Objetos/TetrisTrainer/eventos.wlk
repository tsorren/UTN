import wollok.game.*
import gameMaster.*
import numeros.*

class EventoBorrarLineas
{
    const lineasBorradas

    var property position = game.at(mapa.minX() - 11, mapa.maxY() - 11)
    var property image = null

    const imagenes = [null, "eSINGLE.png", "eDOUBLE.png", "eTRIPLE.png", "eQUAD.png"]

    method aplicarGravedad() {} 

    method spawn()
    {
        image = imagenes.get(lineasBorradas)
        game.addVisual(self)
        game.schedule(2500, {
            game.removeVisual(self)
            eventos.quitarEvento(self)
        })
    }
}

object eventos
{
    const eventosActuales = []
    method aplicarGravedad() {} 

    method quitarEvento(evento) = eventosActuales.remove(evento)

    method mostrarLineasBorradas(cantidad)
    {
        if(not eventosActuales.isEmpty()) eventosActuales.forEach({evento => if(game.hasVisual(evento)) game.removeVisual(evento)}) 
        const nuevoEvento = new EventoBorrarLineas(lineasBorradas = cantidad)
        eventosActuales.add(nuevoEvento)
        nuevoEvento.spawn()
    }
    
    const contadorLineas = new Contador(dX = -2, dY = -13, digitos = 2, target = juego.targetLineasBorradas())
    const contadorGarbage = new Contador(dX = -2, dY = -15, digitos = 2, target = juego.targetGarbageBorrada())
    
    const contadorBloques = new Contador(dX = 10, dY = -7, digitos = 4, target = 10000)
    const contadorScore = new Contador(dX = 9, dY = -10, digitos = 3, target = 10000)

    method inicializar()
    {
        eventosActuales.clear()
        contadorLineas.setearCondicion(not juego.esDigRace())
        contadorGarbage.setearCondicion(juego.esDigRace())
    }


    method inicializarContadorLineas() {contadorLineas.inicializar()}
    method inicializarContadorGarbage() {contadorGarbage.inicializar()}

    method aumentarLineasBorradas(cantidad) {contadorLineas.aumentar(cantidad)}
    method aumentarGarbageBorrada() {contadorGarbage.aumentar(1)}

    method setearContadorBloques(cantidad) {
        contadorBloques.inicializar()
        contadorBloques.aumentar(cantidad)
    }
    method setearContadorScore(cantidad) {
        contadorScore.inicializar()
        contadorScore.aumentar(cantidad)
    }
    method garbageBorrada() = contadorGarbage.contador()
    method lineasBorradas() = contadorLineas.contador()
}

class Contador
{
    const dX
    const dY
    var property position = game.at(mapa.minX() + dX, mapa.maxY() + dY)

    var property contador = 0

    const digitos
    const target
    const numeros = []

    var esCondicion = false
    method setearCondicion(valor) {esCondicion = valor}

    /*
    method preparar()
    {
        numeros.forEach({num => 
            if(game.hasVisual(num))
                game.removeVisual(num)
        })
    }
    */

    method inicializar()
    {
        contador = 0
        numeros.clear()
        digitos.times({num =>
            const numero = new Numero(position = position.down(2).left(num - 1))
            numeros.add(numero)
            game.addVisual(numero)
        })
        
    }

    method aumentar(cantidad) 
    {
        contador += cantidad
        self.actualizarNumeros(numeros, cantidad)
        if(esCondicion and contador >= target) juego.finalizar()
    }

    method actualizarNumeros(nums, cantidad)
    {
        nums.first().aumentar(cantidad)
        if(nums.size() > 1 && nums.first().huboCarry())
        {
            self.actualizarNumeros(nums.drop(1), nums.first().cuantoCarry())
        }
        
    }
    method aplicarGravedad() {}
}
