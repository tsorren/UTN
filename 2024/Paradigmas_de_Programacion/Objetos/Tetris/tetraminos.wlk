import wollok.game.*

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

        // console.println(nuevaPos)
        // console.println(esValida)
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
                self.borrarLinea(linea)
                self.bajarDemasBloques(y)
                return 1
            }
            else
            {
                return 0 
            }
        }   
    }
    method borrarLinea(linea)
    {
        linea.forEach({pos => game.removeVisual(game.getObjectsIn(pos).first())})
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

}

object eventos
{
    var property image = null
    var property position = game.at(mapa.minX() - 11, mapa.maxY() - 9)

    const imagenes = [null, "eSINGLE.png", "eDOUBLE.png", "eTRIPLE.png", "eQUAD.png"]

    method aplicarGravedad() {} 

    method cambiarImagen(nuevaImagen) {image = nuevaImagen}
    method mostrarLineasBorradas(cantidad)
    {
        self.cambiarImagen(imagenes.get(cantidad))
        // console.println(image)
        if(not game.hasVisual(self)) game.addVisual(self)
        game.schedule(2000, {if(game.hasVisual(self)) game.removeVisual(self)})
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
            //console.println(pieza)
        })
    }
}

object juego
{
    var holdPiece = null
    var property holdDisponible = true
    var property dasEncendido = false

    var property piezaActual = bagGenerator.nuevaPieza()

    method iniciarJuego()
    {
        piezaActual.crear()
        bagGenerator.initBagPreview()

    }

    method ponerPieza()
    {
        piezaActual.poner()
        game.removeVisual(piezaActual)
        piezaActual = bagGenerator.nuevaPieza()
        piezaActual.crear()
        holdDisponible = true
        game.sound("poner.mp3").play()
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
        var cantidadDesplazamiento = 1
        var nuevaPos 

        if(dasEncendido)
        {
            // TODO CODIFICAR DAS
            dasEncendido = false
        }

        if(direccion == "izquierda") nuevaPos = piezaActual.position().left(cantidadDesplazamiento)
        else if(direccion == "derecha") nuevaPos = piezaActual.position().right(cantidadDesplazamiento)
        else if(direccion == "abajo") nuevaPos = piezaActual.position().down(cantidadDesplazamiento)

        piezaActual.movete(nuevaPos)
        
    }
    method hacerTransformacionHold()
    {
        mapa.esconder(piezaActual.bloques())
        holdPiece = piezaActual
        holdPiece.resetearRotacion()

        //holdPiece.cambiarImagen(holdPiece.imagenHold())
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

class Bloque {
    var property position = game.center()
    var property image
    var id
    var mapId = -1

    method aplicarGravedad() {self.bajar()}

    method cambiarImagen(imagen)
    {
        image = imagen
    }

    method id() = id
    method inicializarID(identificador)
    {
        id = identificador
    }

    method mapId() = mapId
    method inicializarMapID(identificadorMapa)
    {
        mapId = identificadorMapa
    }


    method centrar() 
    {
        position = game.center()
    }

    method bajar() 
    {
        position = position.down(1)
    }


    method movete(nuevaPos) 
    {
        position = nuevaPos
    }
}
class Pieza
{
    var estadoRotacion = 0
    method estadoRotacion() = estadoRotacion
    method resetearRotacion()
    {
        estadoRotacion = 0
    }

    const posInicial = game.at((mapa.minX() + mapa.maxX()) / 2, mapa.maxY() - 2)

    var position = posInicial
    method position() = position
    method setPos(pos) {position = pos}

    method bloques() = null
    method matRot() = null
    method matKicks() = null
    method aplicarGravedad() {}

    
    method matKicksJLOSTZ() = [ // Wallkicks para las rotaciones de las piezas J, L, S, T y Z
        [[0, 0], [-1, 0], [-1, 1], [0, -2], [-1, -2]], // 0 -> R (0 a 1) - Rotaciones Normales
        [[0, 0], [1, 0], [1, -1], [0, 2], [1, 2]],     // R -> 0 (1 a 0)
        [[0, 0], [1, 0], [1, -1], [0, 2], [1, 2]],     // R -> 2 (1 a 2)
        [[0, 0], [-1, 0], [-1, 1], [0, -2], [-1, -2]], // 2 -> R (2 a 1)
        [[0, 0], [1, 0], [1, 1], [0, -2], [1, -2]],    // 2 -> L (2 a 3)
        [[0, 0], [-1, 0], [-1, -1], [0, 2], [-1, 2]],  // L -> 2 (3 a 2)
        [[0, 0], [-1, 0], [-1, -1], [0, 2], [-1, 2]],  // L -> 0 (3 a 0)
        [[0, 0], [1, 0], [1, 1], [0, -2], [1, -2]],    // 0 -> L (0 a 3)
        [[0, 0], [0, 1]],                              // 0 -> 2 (0 a 2) - Rotaciones Invertidas
        [[0, 0], [0, -1]],                             // 2 -> 0 (2 a 0)
        [[0, 0], [1, 0]],                              // R -> L (1 a 3)
        [[0, 0], [-1, 0]]]                             // L -> R (3 a 1)

    method matKicksI() = [ // Wallkicks para la pieza I
        [[0, 0], [-2, 0], [1, 0], [-2, -1], [1, 2]], // 0 -> R (0 a 1) - Rotaciones Normales
        [[0, 0], [2, 0], [-1, 0], [2, 1], [-1, -2]], // R -> 0 (1 a 0)
        [[0, 0], [-1, 0], [2, 0], [-1, 2], [2, -1]], // R -> 2 (1 a 2)
        [[0, 0], [1, 0], [-2, 0], [1, -2], [-2, 1]], // 2 -> R (2 a 1)
        [[0, 0], [2, 0], [-1, 0], [2, 1], [-1, -2]], // 2 -> L (2 a 3)
        [[0, 0], [-2, 0], [1, 0], [-2, -1], [1, 2]], // L -> 2 (3 a 2)
        [[0, 0], [1, 0], [-2, 0], [1, -2], [-2, 1]], // L -> 0 (3 a 0)
        [[0, 0], [-1, 0], [2, 0], [-1, 2], [2, -1]], // 0 -> L (0 a 3)
        [[0, 0], [0, 1]],                            // 0 -> 2 (0 a 2) - Rotaciones Invertidas
        [[0, 0], [0, -1]],                           // 2 -> 0 (2 a 0)
        [[0, 0], [1, 0]],                            // R -> L (1 a 3)
        [[0, 0], [-1, 0]]]                           // L -> R (3 a 1)
        

    method crear()
    {
        position = posInicial
        self.actualizarPos(estadoRotacion)
        mapa.mostrar(self.bloques())
        mapa.asignarIds(self.bloques())
    }

    method irAlPiso()
    {        
        const posiblesPosiciones = new Range(start = mapa.minY() - 2, end = position.y()).filter({posY => 
        not mapa.esMovimientoValido(self, game.at(position.x(), posY), estadoRotacion)}).map({n => n + 1})

        // console.println(posiblesPosiciones)
        const nuevaPos = game.at(position.x(), posiblesPosiciones.max())
        
        self.movete(nuevaPos)
    }

    method poner()
    {
        var contador = 0
        self.irAlPiso()
        self.bloques().forEach({bloque => 
            contador = contador + mapa.chequearLinea(bloque.position().y())
        })
        if(contador > 0) eventos.mostrarLineasBorradas(contador)
    }

    method actualizarPos(rotacion)
    {
        const pieza = self
        self.bloques().forEach({bloque => bloque.movete(game.at(
            position.x() + pieza.aplicarRotacion(rotacion, bloque.id()).x(),
            position.y() + pieza.aplicarRotacion(rotacion, bloque.id()).y()
        ))})
    }

    method aplicarRotacion(rotacion, id)
    {
        return game.at(self.matRot().get(rotacion).get(id).get(0), self.matRot().get(rotacion).get(id).get(1))
    }
    
    method nuevoEstadoRotacion(sentido)
    {
        if(sentido == "derecha")
        {
            return (estadoRotacion + 1) % 4
        }
        else if(sentido == "opuesto")
        {
            return (estadoRotacion + 2) % 4
        }
        else if(sentido == "izquierda")
        {
            return (estadoRotacion + 3) % 4
        }
        else
        {
            return -1
        }
    }

    method calcularIndiceKick(estadoActual, estadoSiguiente)
    {
        /*
        const indices = [
        [ -1,  0, -1,  7], // estadoActual 0: [0 -> 0], [0 -> R], [0 -> 2], [0 -> L]
        [  1, -1,  2, -1], // estadoActual R: [R -> 0], [R -> R], [R -> 2], [R -> L]
        [ -1,  3, -1,  4], // estadoActual 2: [2 -> 0], [2 -> R], [2 -> 2], [2 -> L]
        [  6, -1,  5, -1]] // estadoActual L: [L -> 0], [L -> R], [L -> 2], [L -> L]
        */
        const indices = [
        [  0,  0,  8,  7], // estadoActual 0: [0 -> 0], [0 -> R], [0 -> 2], [0 -> L]
        [  1,  0,  2, 10], // estadoActual R: [R -> 0], [R -> R], [R -> 2], [R -> L]
        [  9,  3,  0,  4], // estadoActual 2: [2 -> 0], [2 -> R], [2 -> 2], [2 -> L]
        [  6, 11,  5,  0]] // estadoActual L: [L -> 0], [L -> R], [L -> 2], [L -> L]


        return indices.get(estadoActual).get(estadoSiguiente)
    }

    method aplicarKick(nuevoEstado)
    {
        const indice = self.calcularIndiceKick(estadoRotacion, nuevoEstado)
        //console.println(indice)
        
        var posicionesDeKick = self.matKicks().get(indice).map({vec =>
            game.at(position.x() + vec.get(0), position.y() + vec.get(1))})
            
        // console.println(posicionesDeKick)
        posicionesDeKick = posicionesDeKick.filter({
                posKick => mapa.esMovimientoValido(self, posKick, nuevoEstado)})
                
        if(not posicionesDeKick.isEmpty())
        {
            // console.println(game.at(position.x() - posicionesDeKick.first().x(), position.y() - posicionesDeKick.first().y()))
            position = posicionesDeKick.first()
        }

        return not posicionesDeKick.isEmpty()
    }
    
    method rotar(sentido)
    {
        const nuevoEstado = self.nuevoEstadoRotacion(sentido)
        
        if(self.aplicarKick(nuevoEstado))
        {
            estadoRotacion = nuevoEstado
            self.actualizarPos(estadoRotacion)
        }
        
    }

    method movete(nuevaPos) 
    {
        
        if(mapa.esMovimientoValido(self, nuevaPos, estadoRotacion))
        {
            position = nuevaPos
            self.actualizarPos(estadoRotacion)
        }
    }
    
    method bajar()
    {
        position = position.down(1)
        self.actualizarPos(estadoRotacion)
    }
    
    /*
    method randomPos(bloques, matRot)
    {
        const x = 3.randomUpTo(game.width() - 3).truncate(0)
        const y = 3.randomUpTo(game.height() - 3).truncate(0)
        self.movete(game.at(x, y))
    }
    */
}

class PiezaI inherits Pieza {
    var property image = self.imagenOriginal()
    method cambiarImagen(imagen)
    {
        image = imagen
    }

    const img = "cyan.png"
    method imagenOriginal() = "PiezaI.png"
    method imagenHold() = "Hold" + self.imagenOriginal()

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    override method bloques() = bloques
    
    const matRot = [
        [[-1, 1], [0, 1], [1, 1], [2, 1]], // Estado 0
        [[1, 2], [1, 1], [1, 0], [1, -1]], // Estado 1 (derecha)
        [[-1, 0], [0, 0], [1, 0], [2, 0]], // Estado 2 (invertido)
        [[0, 2], [0, 1], [0, 0], [0, -1]]] // Estado 3 (izquierda)
    override method matRot() = matRot

    override method matKicks() = self.matKicksI()
}

class PiezaJ inherits Pieza {
    var property image = self.imagenOriginal()
    method cambiarImagen(imagen)
    {
        image = imagen
    }

    const img = "blue.png"

    method imagenOriginal() = "PiezaJ.png"
    method imagenHold() = "Hold" + self.imagenOriginal()

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    override method bloques() = bloques

    const matRot = [
        [[-1, 1], [-1, 0], [0, 0], [1, 0]],
        [[1, 1], [0, 1], [0, 0], [0, -1]],
        [[1, -1], [1, 0], [0, 0], [-1, 0]],
        [[-1, -1], [0, -1], [0, 0], [0, 1]]
    ]
    override method matRot() = matRot
    override method matKicks() = self.matKicksJLOSTZ()
}

class PiezaL inherits Pieza{
    var property image = self.imagenOriginal()
    method cambiarImagen(imagen)
    {
        image = imagen
    }

    const img = "orange.png"
    method imagenOriginal() = "PiezaL.png"
    method imagenHold() = "Hold" + self.imagenOriginal()

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    override method bloques() = bloques

    const matRot = [
        [[-1, 0], [0, 0], [1, 0], [1, 1]],
        [[0, 1], [0, 0], [0, -1], [1, -1]],
        [[1, 0], [0, 0], [-1, 0], [-1, -1]],
        [[0, -1], [0, 0], [0, 1], [-1, 1]]
    ]
    override method matRot() = matRot
    override method matKicks() = self.matKicksJLOSTZ()
}
class PiezaO inherits Pieza{
    var property image = self.imagenOriginal()
    method cambiarImagen(imagen)
    {
        image = imagen
    }

    const img = "yellow.png"
    method imagenOriginal() = "PiezaO.png"
    method imagenHold() = "Hold" + self.imagenOriginal()

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    override method bloques() = bloques

    const matRot = [
        [[-1, 1], [0, 1], [-1, 0], [0, 0]],
        [[-1, 1], [0, 1], [-1, 0], [0, 0]],
        [[-1, 1], [0, 1], [-1, 0], [0, 0]],
        [[-1, 1], [0, 1], [-1, 0], [0, 0]]
    ]
    override method matRot() = matRot
    override method matKicks() = self.matKicksJLOSTZ()
}
class PiezaS inherits Pieza{
    var property image = self.imagenOriginal()
    method cambiarImagen(imagen)
    {
        image = imagen
    }

    const img = "green.png"
    method imagenOriginal() = "PiezaS.png"
    method imagenHold() = "Hold" + self.imagenOriginal()

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    override method bloques() = bloques

    const matRot = [
        [[-1, 0], [0, 0], [0, 1], [1, 1]],
        [[0, 1], [0, 0], [1, 0], [1, -1]],
        [[1, 0], [0, 0], [0, -1], [-1, -1]],
        [[0, -1], [0, 0], [-1, 0], [-1, 1]]
    ]
    override method matRot() = matRot
    override method matKicks() = self.matKicksJLOSTZ()
}
class PiezaT inherits Pieza {
    var property image = self.imagenOriginal()
    method cambiarImagen(imagen)
    {
        image = imagen
    }

    const img = "purple.png"
    method imagenOriginal() = "PiezaT.png"
    method imagenHold() = "Hold" + self.imagenOriginal()

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    override method bloques() = bloques

    const matRot = [
        [[-1, 0], [0, 0], [0, 1], [1, 0]],
        [[0, 1], [0, 0], [1, 0], [0, -1]],
        [[-1, 0], [0, 0], [0, -1], [1, 0]],
        [[0, 1], [0, 0], [-1, 0], [0, -1]]
    ]
    override method matRot() = matRot
    override method matKicks() = self.matKicksJLOSTZ()
}

class PiezaZ inherits Pieza{
    var property image = self.imagenOriginal()
    method cambiarImagen(imagen)
    {
        image = imagen
    }

    const img = "red.png"
    method imagenOriginal() = "PiezaZ.png"
    method imagenHold() = "Hold" + self.imagenOriginal()

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    override method bloques() = bloques

    const matRot = [
        [[-1, 1], [0, 1], [0, 0], [1, 0]],
        [[1, 1], [1, 0], [0, 0], [0, -1]],
        [[-1, 0], [0, 0], [0, -1], [1, -1]],
        [[-1, -1], [-1, 0], [0, 0], [0, 1]]
    ]
    override method matRot() = matRot
    override method matKicks() = self.matKicksJLOSTZ()
}