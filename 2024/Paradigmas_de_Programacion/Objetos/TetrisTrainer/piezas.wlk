import wollok.game.*
import gameMaster.*
import bloques.*
import eventos.*

class Pieza
{
    var estadoRotacion = 0
    method estadoRotacion() = estadoRotacion
    method resetearRotacion() {estadoRotacion = 0}

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
        if(not mapa.esMovimientoValido(self, posInicial, estadoRotacion)) juego.finalizar()
        position = posInicial
        self.actualizarPos(estadoRotacion)
        mapa.mostrar(self.bloques())
        mapa.asignarIds(self.bloques())
    }

    method irAlPiso()
    {        
        const posiblesPosiciones = new Range(start = mapa.minY() - 2, end = position.y()).filter({posY => 
        not mapa.esMovimientoValido(self, game.at(position.x(), posY), estadoRotacion)}).map({n => n + 1})

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
        if(contador > 0)
        {
            eventos.mostrarLineasBorradas(contador)
            eventos.aumentarLineasBorradas(contador)
        }
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
        if(sentido == "derecha") {return (estadoRotacion + 1) % 4}
        else if(sentido == "opuesto") {return (estadoRotacion + 2) % 4}
        else if(sentido == "izquierda") {return (estadoRotacion + 3) % 4}
        else {return -1}
    }

    method calcularIndiceKick(estadoActual, estadoSiguiente)
    {
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
        
        var posicionesDeKick = self.matKicks().get(indice).map({vec =>
            game.at(position.x() + vec.get(0), position.y() + vec.get(1))})
            
        posicionesDeKick = posicionesDeKick.filter({
            posKick => mapa.esMovimientoValido(self, posKick, nuevoEstado)
        })
        if(not posicionesDeKick.isEmpty()) {position = posicionesDeKick.first()}

        return not posicionesDeKick.isEmpty()
    }
    
    method rotar(sentido)
    {
        const nuevoEstado = self.nuevoEstadoRotacion(sentido)
        const indice = self.calcularIndiceKick(estadoRotacion, nuevoEstado)
        
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
}

class PiezaI inherits Pieza {
    var property image = self.imagenOriginal()
    method cambiarImagen(imagen)
    {
        image = imagen
    }

    const img = "bCYAN.png"
    method imagenOriginal() = "PiezaI.png"

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

    const img = "bBLUE.png"

    method imagenOriginal() = "PiezaJ.png"

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

    const img = "bORANGE.png"
    method imagenOriginal() = "PiezaL.png"

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

    const img = "bYELLOW.png"
    method imagenOriginal() = "PiezaO.png"

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

    const img = "bGREEN.png"
    method imagenOriginal() = "PiezaS.png"

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
    method cambiarImagen(imagen) {image = imagen}

    const img = "bPURPLE.png"
    method imagenOriginal() = "PiezaT.png"

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

    const img = "bRED.png"
    method imagenOriginal() = "PiezaZ.png"

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