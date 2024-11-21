import wollok.game.*
import gameMaster.*
import piezas.*

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
