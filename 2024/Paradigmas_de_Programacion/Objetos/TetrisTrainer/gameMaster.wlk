import wollok.game.*
import bloques.*
import piezas.*
import eventos.*
import menu.*

object mapa {

    const minX = 15
    const maxX = minX + 10

    const minY = 2
    const maxY = minY + 20

    method minX() = minX
    method maxX() = maxX
    method minY() = minY
    method maxY() = maxY

    var ultimoIdAsignado = 0
    
    method asignarIds(bloques)
    {
        bloques.forEach({bloque => 
            bloque.inicializarMapID(ultimoIdAsignado)
        })
        ultimoIdAsignado = ultimoIdAsignado + 1
    }
    
    method esEspacioLibre(nuevaPos, bloque) = game.getObjectsIn(nuevaPos).isEmpty() or (game.getObjectsIn(nuevaPos).first().mapId() == bloque.mapId())

    method esPosValida(pos) =  pos.x().between(minX, maxX - 1) and pos.y().between(minY, maxY - 1)

    method esMovimientoValido(pieza, nuevaPos, rotacion)
    {
        var pos
        
        const esValida = pieza.bloques().all({bloque =>
            pos = game.at(
                nuevaPos.x() + pieza.aplicarRotacion(rotacion, bloque.id()).x(),
                nuevaPos.y() + pieza.aplicarRotacion(rotacion, bloque.id()).y())
            self.esEspacioLibre(pos, bloque) && self.esPosValida(pos)})

        return esValida
    }
    
    
    method esLineaCompleta(linea) = linea.all({pos => not game.getObjectsIn(pos).isEmpty()})

    method chequearLinea(y)
    {
        if(y.between(minY, maxY - 1))
        {
            const linea = new Range(start = minX, end = maxX - 1).map({x => game.at(x, y)})
            if(self.esLineaCompleta(linea))
            {
                self.borrarLinea(linea, y)
                return 1
            }
            else
            {
                return 0 
            }
        }   
    }
    method borrarLinea(linea, y)
    {
        linea.forEach({pos => game.removeVisual(game.getObjectsIn(pos).first())})

        self.bajarDemasBloques(y)
        if(not garbage.isEmpty() && garbage.contains(y))
        {
            eventos.aumentarGarbageBorrada()
            garbage.remove(y)
        }
    }

    method bajarDemasBloques(linea)
    {
        game.allVisuals().forEach({visual => 
            if(visual.position().y() > linea) visual.aplicarGravedad()
        })
    }
    
    method mostrar(bloques) 
    {
        bloques.forEach({bloque => game.addVisual(bloque)})
    }

    method esconder(bloques) 
    {
        bloques.forEach({bloque => game.removeVisual(bloque)})
    }

    var garbage = []

    method generarGarbage()
    {
        var bloque
        const numeros = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
        garbage = numeros.map({y => y + minY})
        
        numeros.forEach({ y =>
            const tempGarbage = []
            const lista = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
            lista.remove(numeros.anyOne())
            lista.forEach({x => 
                bloque = new Bloque(image = "bGARBAGE.png", id = x)
                bloque.movete(game.at(minX + x, minY + y))
                tempGarbage.add(bloque)
            })
            self.asignarIds(tempGarbage)
            self.mostrar(tempGarbage)
        })
    }

}

object bagGenerator {
    var piezasDisponibles = self.nuevaBag() + self.nuevaBag()
    var piezaActual = null

    method nuevaBag() = [new PiezaI(), new PiezaJ(), new PiezaL(), new PiezaO(), new PiezaS(), new PiezaT(), new PiezaZ()].randomized()

    method siguientesPiezas() = piezasDisponibles.take(5)

    method nuevaPieza()
    {
        piezaActual = piezasDisponibles.first()
        piezasDisponibles.remove(piezaActual)
        game.addVisual(piezasDisponibles.get(4))
        
        if(piezasDisponibles.size() <= 7)
        {
            piezasDisponibles = piezasDisponibles + self.nuevaBag()
        }

        game.removeVisual(piezaActual)
        self.previewBag()
        return piezaActual
    } 

    method initBagPreview()
    {
        game.addVisual(piezasDisponibles.get(0))
        game.addVisual(piezasDisponibles.get(1))
        game.addVisual(piezasDisponibles.get(2))
        game.addVisual(piezasDisponibles.get(3))
        self.previewBag()
    }

    method previewBag() 
    {
        const indices = new Range(start = 0, end = 4)
        const piezas = self.siguientesPiezas()
        var pieza
        indices.forEach({indice => 
            pieza = piezas.get(indice)
            pieza.setPos(game.at(27, 18 - indice * 3))
        })
    }
}

object juego
{
    var targetLineasBorradas = 20
    const targetGarbageBorrada = 10
    var holdPiece = null
    var property holdDisponible = true

    var property piezaActual = null

    var bloquesPuestos = 0

    var property esDigRace = false
    method digRace(){esDigRace = true}
    method sprint(){esDigRace = false}


    method iniciarJuego()
    {
        bloquesPuestos = 0
        holdPiece = null
        holdDisponible = true
        piezaActual = bagGenerator.nuevaPieza()
        bagGenerator.initBagPreview() 
        piezaActual.crear()
        eventos.inicializar()
        if(esDigRace)
        {
            mapa.generarGarbage()
            eventos.inicializarContadorGarbage()
        }
        eventos.inicializarContadorLineas()
        
    }

    method finalizar()
    {
        interfaz.setearPantalla(estadisticas)
        var score = 0
        if(esDigRace and eventos.garbageBorrada() >= targetGarbageBorrada) {score = targetGarbageBorrada}
        if (not esDigRace and eventos.lineasBorradas() >= targetLineasBorradas) {score = targetLineasBorradas}

        score = score * 4 / bloquesPuestos * 100
        
        //console.println(score)
        //console.println(bloquesPuestos)

        estadisticas.iniciar()
        eventos.setearContadorBloques(bloquesPuestos)
        eventos.setearContadorScore(score.round())

        game.schedule(50, {game.stop()})
    }

    method targetLineasBorradas() = targetLineasBorradas
    method targetLineasBorradas(cantidad) {targetLineasBorradas = cantidad}

    method targetGarbageBorrada() = targetGarbageBorrada

    method ponerPieza()
    {
        piezaActual.poner()
        game.removeVisual(piezaActual)
        piezaActual = bagGenerator.nuevaPieza()
        piezaActual.crear()
        holdDisponible = true
        game.sound("poner.mp3").play()
        bloquesPuestos += 4
    }

    method rotarPieza(sentido) {piezaActual.rotar(sentido)}

    method aplicarGravedad() {
        if(self.puedeBajar())
            piezaActual.bajar()
        else
            game.schedule(500, {if(not self.puedeBajar()) self.ponerPieza()})
    }

    method puedeBajar() = mapa.esMovimientoValido(piezaActual, piezaActual.position().down(1), piezaActual.estadoRotacion())

    method intentarHold()
    {
        if(holdDisponible)
        {
            const piezaRetorno = self.hacerHold()  
            if(piezaRetorno == null)
            {
                piezaActual = bagGenerator.nuevaPieza()
                piezaActual.crear()
            }
            else
                piezaActual = piezaRetorno

            holdDisponible = false
        }
    }

    method moverPieza(direccion)
    {
        var nuevaPos 

        if(direccion == "izquierda") nuevaPos = piezaActual.position().left(1)
        else if(direccion == "derecha") nuevaPos = piezaActual.position().right(1)
        else if(direccion == "abajo") nuevaPos = piezaActual.position().down(1)

        piezaActual.movete(nuevaPos)
        
    }
    method hacerTransformacionHold()
    {
        mapa.esconder(piezaActual.bloques())
        holdPiece = piezaActual
        holdPiece.resetearRotacion()

        holdPiece.setPos(game.at(8, 18))

        game.addVisual(holdPiece)
    }

    method hacerHold() {
        
        if(holdPiece == null)
        {
            self.hacerTransformacionHold()
            return null
        }
        else
        {
            const aux = holdPiece
            aux.cambiarImagen(aux.imagenOriginal())
            game.removeVisual(aux)
            self.hacerTransformacionHold()
            aux.crear()
            return aux

        }
    }
}
