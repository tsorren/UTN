import wollok.game.*

class Bloque {
    var property position = game.origin()
    var image
    method image() = image
    var id

    method inicializarID(identificador)
    {
        id = identificador
    }

    method id() = id

    method centrar() 
    {
        position = game.center()
    }

    method bajar() 
    {
        position = position.down(1)
    }


    method movete(nuevaPos) {
        position = nuevaPos
    }
    method randomPos()
    {
        const x = 3.randomUpTo(game.width() - 3).truncate(0)
        const y = 3.randomUpTo(game.height() - 3).truncate(0)
        // otra forma de generar números aleatorios
        // const x = (0.. game.width()-1).anyOne()
        // const y = (0.. game.height()-1).anyOne()
        self.movete(game.at(x, y))
    }
}
class Pieza
{
    var estadoRotacion = 0
    method estadoRotacion() = estadoRotacion

    var position = game.center()
    method position() = position

    // Wallkicks para las rotaciones de las piezas J, L, S, T y Z
    /*
    const matKicksJLSTZ = [
        [[0, 0], [-1, 0], [-1, 1], [0, -2], [-1, -2]], // 0 -> R (0 a 1)
        [[0, 0], [1, 0], [1, -1], [0, 2], [1, 2]],     // R -> 0 (1 a 0)
        [[0, 0], [1, 0], [1, -1], [0, 2], [1, 2]],     // R -> 2 (1 a 2)
        [[0, 0], [-1, 0], [-1, 1], [0, -2], [-1, -2]], // 2 -> R (2 a 1)
        [[0, 0], [1, 0], [1, 1], [0, -2], [1, -2]],    // 2 -> L (2 a 3)
        [[0, 0], [-1, 0], [-1, -1], [0, 2], [-1, 2]],  // L -> 2 (3 a 2)
        [[0, 0], [-1, 0], [-1, -1], [0, 2], [-1, 2]],  // L -> 0 (3 a 0)
        [[0, 0], [1, 0], [1, 1], [0, -2], [1, -2]]]     // 0 -> L (0 a 3)
    */
     const matKicksJLSTZ = [
    [[0, 0], [-1, 0], [-1, 1], [0, -2], [-1, -2]], // 0 -> R (0 a 1) - Rotaciones "normales"
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
    [[0, 0], [-1, 0]]]                              // L -> R (3 a 1)

    const matKicksI = [ // Wallkicks para la pieza I
        [[0, 0], [-2, 0], [1, 0], [-2, -1], [1, 2]], // 0 -> R (0 a 1)
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
        [[0, 0], [-1, 0]]]                            // L -> R (3 a 1)
        

    method mostrar(bloques) 
    {
        bloques.forEach({bloque => game.addVisual(bloque)})
    }

    method esconder(bloques) 
    {
        bloques.forEach({bloque => game.removeVisual(bloque)})
    }

    method crear(bloques, matRot)
    {
        self.actualizarPos(bloques, matRot, estadoRotacion)
        self.mostrar(bloques)
    }

    method poner(bloques, matRot)
    {
        var nuevaPos
        var encontroPos = false

        self.esconder(bloques)
        const posiblesPosiciones = new Range(start = 1, end = position.y()).forEach(({posY => 
        if(self.esMovimientoValido(bloques, matRot, game.at(position.x(), posY), estadoRotacion) && not encontroPos)
        {
            nuevaPos = game.at(position.x(), posY)
            encontroPos = true
        }}))
        self.mostrar(bloques)
        position = nuevaPos
        self.actualizarPos(bloques, matRot, estadoRotacion)
    }

    method actualizarPos(bloques, matRot, rotacion)
    {
        const pieza = self
        bloques.forEach({bloque => bloque.movete(game.at(
            position.x() + pieza.aplicarRotacion(matRot, rotacion, bloque.id()).x(),
            position.y() + pieza.aplicarRotacion(matRot, rotacion, bloque.id()).y()
        ))})
    }

    method aplicarRotacion(matRot, rotacion, id)
    {
        return game.at(matRot.get(rotacion).get(id).get(0), matRot.get(rotacion).get(id).get(1))
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

    method aplicarKick(bloques, matRot, matKicks, nuevoEstado)
    {
        //var indice = ((estadoRotacion * 2 + (nuevoEstado - estadoRotacion + 4) % 4) % 8) - 1
        const indice = self.calcularIndiceKick(estadoRotacion, nuevoEstado)
        //console.println(indice)
        
        var posicionesDeKick = matKicks.get(indice).map({vec =>
            game.at(position.x() + vec.get(0), position.y() + vec.get(1))})
            
        // console.println(posicionesDeKick)
        posicionesDeKick = posicionesDeKick.filter({
                posKick => self.esMovimientoValido(bloques, matRot, posKick, nuevoEstado)})
                
        if(not posicionesDeKick.isEmpty())
        {
            // console.println(game.at(position.x() - posicionesDeKick.first().x(), position.y() - posicionesDeKick.first().y()))
            position = posicionesDeKick.first()
        }

        return not posicionesDeKick.isEmpty()
    }
    
    method rotar(bloques, matRot, matKicks, sentido)
    {
        const nuevoEstado = self.nuevoEstadoRotacion(sentido)
        
        self.esconder(bloques)
        if(self.aplicarKick(bloques, matRot, matKicks, nuevoEstado))
        {
            estadoRotacion = nuevoEstado
            self.actualizarPos(bloques, matRot, estadoRotacion)
        }
        self.mostrar(bloques)
        
        //estadoRotacion = nuevoEstado
        //self.actualizarPos(bloques, matRot, estadoRotacion)
    }

    method esEspacioLibre(pos)
    {
        /* TODO BORRAR
        const obj = game.getObjectsIn(pos)
        if(not obj.isEmpty())
            console.println(obj)
        */
        return game.getObjectsIn(pos).isEmpty()
    }
    method esPosValida(pos)
    {        
        const margenX = 3
        const margenY = 2
        return pos.x().between(margenX, margenX + 10) and pos.y().between(margenY, margenY + 20)
    }

    method esMovimientoValido(bloques, matRot, nuevaPos, rotacion)
    {
        const pieza = self
        
        const esValida = self.esPosValida(nuevaPos) && bloques.all({bloque => 
            pieza.esEspacioLibre(game.at(
                nuevaPos.x() + pieza.aplicarRotacion(matRot, rotacion, bloque.id()).x(),
                nuevaPos.y() + pieza.aplicarRotacion(matRot, rotacion, bloque.id()).y()
        ))})
        //
        return esValida
    }
    
    method movete(bloques, matRot, nuevaPos) 
    {
        // position = nuevaPos
        // self.actualizarPos(bloques, matRot, estadoRotacion)
        
        self.esconder(bloques)
        
        if(self.esMovimientoValido(bloques, matRot, nuevaPos, estadoRotacion))
        {
            position = nuevaPos
            self.actualizarPos(bloques, matRot, estadoRotacion)
        }
        /*
        else
        {
            self.movete(bloques, matRot, game.center())
            bloques.forEach({bloque => game.say(bloque, "No me puedo mover ahí")})
        }
        */
        self.mostrar(bloques)
    }
    
    method bajar(bloques, matRot)
    {
        self.movete(bloques, matRot, position.down((1)))
    }
    
    method randomPos(bloques, matRot)
    {
        const x = 3.randomUpTo(game.width() - 3).truncate(0)
        const y = 3.randomUpTo(game.height() - 3).truncate(0)
        self.movete(bloques, matRot, game.at(x, y))
    }
}

class PiezaI inherits Pieza {
    var img = "cyan.png"

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    method bloques() = bloques
    
    const matRot = [
        [[-1, 1], [0, 1], [1, 1], [2, 1]], // Estado 0
        [[1, 2], [1, 1], [1, 0], [1, -1]], // Estado 1 (derecha)
        [[-1, 0], [0, 0], [1, 0], [2, 0]], // Estado 2 (invertido)
        [[0, 2], [0, 1], [0, 0], [0, -1]]] // Estado 3 (izquierda)
    method matRot() = matRot

    method matKicks() = matKicksI
}

class PiezaJ inherits Pieza {
    var img = "blue.png"

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    method bloques() = bloques

    const matRot = [
        [[-1, 1], [-1, 0], [0, 0], [1, 0]],
        [[1, 1], [0, 1], [0, 0], [0, -1]],
        [[1, -1], [1, 0], [0, 0], [-1, 0]],
        [[-1, -1], [0, -1], [0, 0], [0, 1]]
    ]
    method matRot() = matRot
    method matKicks() = matKicksJLSTZ
}

class PiezaL inherits Pieza{

    var img = "orange.png"

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    method bloques() = bloques

    const matRot = [
        [[-1, 0], [0, 0], [1, 0], [1, 1]],
        [[0, 1], [0, 0], [0, -1], [1, -1]],
        [[1, 0], [0, 0], [-1, 0], [-1, -1]],
        [[0, -1], [0, 0], [0, 1], [-1, 1]]
    ]
    method matRot() = matRot
    method matKicks() = matKicksJLSTZ
}
class PiezaO inherits Pieza{

    var img = "yellow.png"

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    method bloques() = bloques

    const matRot = [
        [[-1, 1], [0, 1], [-1, 0], [0, 0]],
        [[-1, 1], [0, 1], [-1, 0], [0, 0]],
        [[-1, 1], [0, 1], [-1, 0], [0, 0]],
        [[-1, 1], [0, 1], [-1, 0], [0, 0]]
    ]
    method matRot() = matRot
    method matKicks() = matKicksJLSTZ
}
class PiezaS inherits Pieza{

    var img = "green.png"

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    method bloques() = bloques

    const matRot = [
        [[-1, 0], [0, 0], [0, 1], [1, 1]],
        [[0, 1], [0, 0], [1, 0], [1, -1]],
        [[1, 0], [0, 0], [0, -1], [-1, -1]],
        [[0, -1], [0, 0], [-1, 0], [-1, 1]]
    ]
    method matRot() = matRot
    method matKicks() = matKicksJLSTZ
}
class PiezaT inherits Pieza {

    var img = "purple.png"

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    method bloques() = bloques

    const matRot = [
        [[-1, 0], [0, 0], [0, 1], [1, 0]],
        [[0, 1], [0, 0], [1, 0], [0, -1]],
        [[-1, 0], [0, 0], [0, -1], [1, 0]],
        [[0, 1], [0, 0], [-1, 0], [0, -1]]
    ]
    method matRot() = matRot
    method matKicks() = matKicksJLSTZ
}

class PiezaZ inherits Pieza{

    var img = "red.png"

    const bloques = #{
        new Bloque(id = 0, image = img),
        new Bloque(id = 1, image = img),
        new Bloque(id = 2, image = img),
        new Bloque(id = 3, image = img)
    }
    method bloques() = bloques

    const matRot = [
        [[-1, 1], [0, 1], [0, 0], [1, 0]],
        [[1, 1], [1, 0], [0, 0], [0, -1]],
        [[-1, 0], [0, 0], [0, -1], [1, -1]],
        [[-1, -1], [-1, 0], [0, 0], [0, 1]]
    ]
    method matRot() = matRot
    method matKicks() = matKicksJLSTZ
}